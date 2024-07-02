// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidgetManager.h"

#include "Animation/WidgetAnimationEvent.h"
#include "DataAsset/GameMenuSetting.h"
#include "Group/CommonButtonGroup.h"
#include "StaticFunctions/StaticFunctions_Object.h"
#include "UserWidget/GameHUD.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "UserWidget/Menu/MenuContainer.h"
#include "UserWidget/Menu/MenuStyle.h"
#include "Widget/TagNameSlot.h"

#define LOCTEXT_NAMESPACE "UScreenWidgetManager"

UScreenWidgetManager::UScreenWidgetManager()
{
}

FText UScreenWidgetManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Screen Widget Manager");
}

void UScreenWidgetManager::NativeOnActived()
{
	Super::NativeOnActived();
	CreateGameHUD();
}

void UScreenWidgetManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	Slots.Reset();
	SlotWidgets.Reset();
	GameMenu = nullptr;
	MenuGenerateInfos.Reset();

	if (MenuSelectionChangedHandle.IsValid())
	{
		FScreenWidgetDelegates::OnMenuSelectionChanged.Remove(MenuSelectionChangedHandle);
	}
}

void UScreenWidgetManager::RegisterSlot(UTagNameSlot* InSlot)
{
	if (!InSlot->SlotTag.IsValid() || Slots.Contains(InSlot->SlotTag))
	{
		return;
	}

	Slots.Add(InSlot->SlotTag, InSlot);
}

UTagNameSlot* UScreenWidgetManager::GetSlot(const FGameplayTag InSlotTag) const
{
	return Slots.FindRef(InSlotTag);
}

UUserWidgetBase* UScreenWidgetManager::GetSlotWidget(FGameplayTag InSlotTag) const
{
	return SlotWidgets.FindRef(InSlotTag);
}

UUserWidgetBase* UScreenWidgetManager::GetSlotUserWidgetByClass(FGameplayTag InSlotTag, TSubclassOf<UUserWidgetBase> InClass) const
{
	ensure(InClass);
	return Cast<UUserWidgetBase>(GetSlotWidget(InSlotTag));
}

void UScreenWidgetManager::CreateGameHUD()
{
	for (const auto GameHUDClass : GameHUDClasses)
	{
		if (GameHUDClass.IsNull())
			continue;

		TSubclassOf<UGameHUD> LoadHUDClass = FStaticFunctions_Object::LoadClass<UGameHUD>(GameHUDClass);
		UGameHUD* NewHUD = CreateWidget<UGameHUD>(GetWorld(), LoadHUDClass);
		NewHUD->AddToViewport(NewHUD->GetViewportZOrder());
	}

	FScreenWidgetDelegates::OnHUDCreated.Broadcast();
}

UUserWidgetBase* UScreenWidgetManager::OpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass)
{
	ensure(InWidgetClass);

	UUserWidgetBase* NewWidget = CreateWidget<UUserWidgetBase>(GetWorld(), InWidgetClass);
	NewWidget->NativeOnCreate();

	OpenUserWidget(NewWidget);
	return NewWidget;
}

void UScreenWidgetManager::OpenUserWidgets(TArray<UUserWidgetBase*> InWidgets)
{
	for (const auto& InWidget : InWidgets)
	{
		OpenUserWidget(InWidget);
	}
}

void UScreenWidgetManager::OpenUserWidget(UUserWidgetBase* InWidget)
{
	/* Make sure User Widget Is Not NULL */
	if (!IsValid(InWidget))
	{
		DEBUG(Debug_UI, Warning, TEXT("Can't Open Null UserWidget"))
		return;
	}

	const FGameplayTag SlotTag = InWidget->SlotTag;
	UTagNameSlot* Slot = GetSlot(SlotTag);
	if (IsValid(Slot))
	{
		/* Close Last Widget */
		UUserWidgetBase* OldWidget = GetSlotWidget(SlotTag);
		if (IsValid(OldWidget))
		{
			/* 如果是在同一个Slot，在上一个Widget关闭之后，再打开新的Widget */
			if (OldWidget->SlotTag == InWidget->SlotTag)
			{
				FDelegateHandle WidgetCloseHandle = FScreenWidgetDelegates::OnWidgetClose.AddLambda([&WidgetCloseHandle, this, &Slot, &SlotTag, &InWidget](UUserWidgetBase*)
					{
						FScreenWidgetDelegates::OnWidgetClose.Remove(WidgetCloseHandle);

						SlotWidgets.Add(SlotTag, InWidget);
						Slot->SetContent(InWidget);
						FScreenWidgetDelegates::OnWidgetOpen.Broadcast(InWidget);
					}
				);

				return;
			}

			CloseUserWidgetBySlotTag(OldWidget->SlotTag);
		}

		SlotWidgets.Add(SlotTag, InWidget);
		Slot->SetContent(InWidget);
		FScreenWidgetDelegates::OnWidgetOpen.Broadcast(InWidget);
	}
}

void UScreenWidgetManager::CloseUserWidget(UUserWidgetBase* InWidget)
{
	if (!IsValid(InWidget))
	{
		DEBUG(Debug_UI, Error, TEXT("InWidget Is NULL"))
		return;
	}

	CloseUserWidgetBySlotTag(InWidget->SlotTag);
}

void UScreenWidgetManager::CloseUserWidgetBySlotTag(FGameplayTag InSlotTag)
{
	UTagNameSlot* Slot = Slots.FindRef(InSlotTag);
	if (IsValid(Slot))
	{
		if (!SlotWidgets.Contains(InSlotTag))
		{
			DEBUG(Debug_UI, Log, TEXT("UserWidget Is Already Close"))
			return;
		}

		UUserWidgetBase* RemoveWidget = SlotWidgets.FindRef(InSlotTag);
		if (IsValid(RemoveWidget))
		{
			/* 无动画事件时，直接从槽内移除 */
			if (!RemoveWidget->HasAnimationEvent())
			{
				Slot->RemoveChild(RemoveWidget);
				SlotWidgets.Remove(InSlotTag);
				FScreenWidgetDelegates::OnWidgetClose.Broadcast(RemoveWidget);
			}
			else
			{
				/* 如果有动画事件，等待 UWidgetAnimationEvent::RequestAnimationFinish 后再从Slot中移除 */
				RemoveWidget->GetAnimationEvent()->GetOnAnimationFinishDelegate().AddLambda([this, &Slot, &InSlotTag, &RemoveWidget]()
					{
						Slot->RemoveChild(RemoveWidget);
						SlotWidgets.Remove(InSlotTag);
						FScreenWidgetDelegates::OnWidgetClose.Broadcast(RemoveWidget);
					}
				);
			}
		}
	}
}

void UScreenWidgetManager::SwitchGameMenu(UGameMenuSetting* InGameMenuSetting)
{
	if (!IsValid(InGameMenuSetting))
	{
		DEBUG(Debug_UI, Error, TEXT("GameMenuSetting Is NULL"))
		return;
	}

	if (GameMenu != InGameMenuSetting)
	{
		if (IsValid(GameMenu))
		{
			//todo:清除
			FScreenWidgetDelegates::OnMenuSelectionChanged.Remove(MenuSelectionChangedHandle);
			FScreenWidgetDelegates::OnMenuCleanup.Broadcast();
		}

		/* Generate Root Menu */
		GameMenu = InGameMenuSetting;
		if (const FMenuContainerInfo* MenuContainerInfo = GameMenu->GetRootContainerInfo())
		{
			MenuSelectionChangedHandle = FScreenWidgetDelegates::OnMenuSelectionChanged.AddUObject(this, &UScreenWidgetManager::OnMenuSelectionChanged);
			GenerateMenu(*MenuContainerInfo);
			FScreenWidgetDelegates::OnMenuGenerated.Broadcast();
		}
	}
}

void UScreenWidgetManager::GenerateMenu(const FMenuContainerInfo& InMenuContainerInfo)
{
	/* 如果从没生成过，创建菜单信息 */
	if (!MenuGenerateInfos.Contains(InMenuContainerInfo))
	{
		/* 创建按钮组管理状态的切换 */
		UCommonButtonGroup* CommonButtonGroup = NewObject<UCommonButtonGroup>(this);
		const FMenuGenerateInfo NewMenuGenerateInfo = FMenuGenerateInfo(CommonButtonGroup, InMenuContainerInfo);
		MenuGenerateInfos.Add(NewMenuGenerateInfo);
	}

	/* 查找有效的菜单信息 */
	if (const FMenuGenerateInfo* FoundMenuGenerateInfo = MenuGenerateInfos.FindByKey(InMenuContainerInfo))
	{
		UMenuContainer* MenuContainer = FoundMenuGenerateInfo->MenuContainerInfo.MenuContainer;
		if (IsValid(MenuContainer))
		{
			/* 先添加到屏幕，初始化容器 */
			OpenUserWidget(MenuContainer);

			/* 构建菜单样式 */
			{
				MenuContainer->PreConstructMenuStyle(FoundMenuGenerateInfo->MenuContainerInfo.MenuInfos);

				TArray<UMenuStyle*> MenuStyleArr;
				for (const auto& MenuInfo : FoundMenuGenerateInfo->MenuContainerInfo.MenuInfos)
				{
					/* MenuInfo的按钮样式将覆盖MenuContainer的按钮样式 */
					UMenuStyle* MenuStyle = nullptr;
					if (IsValid(InMenuContainerInfo.MenuStyle))
					{
						MenuStyle = CreateWidget<UMenuStyle>(GetWorld(), InMenuContainerInfo.MenuStyle);
					}
					else if (IsValid(MenuInfo.MenuStyleOverride))
					{
						MenuStyle = MenuInfo.MenuStyleOverride;
					}

					/* 只有当样式有效，才添加该按钮 */
					if (IsValid(MenuStyle))
					{
						/* Call On Create First */
						MenuStyle->NativeOnCreate();

						/* Add Button To Group */
						FoundMenuGenerateInfo->CommonButtonGroup->AddWidget(MenuStyle);

						/* Set Button Event */
						MenuStyle->SetEvents(MenuInfo.Events);

						/* Construct And Add In The Container */
						MenuContainer->ConstructMenuStyle(MenuStyle);
						MenuStyle->NativeConstructMenuStyle(MenuInfo);

						MenuStyleArr.Add(MenuStyle);
					}
				}

				MenuContainer->PostConstructMenuStyle(MenuStyleArr);
			}
		}
		else
		{
			DEBUG(Debug_UI, Error, TEXT("MenuContainer Is NULL"))
		}
	}
}

void UScreenWidgetManager::OnMenuSelectionChanged(FMenuInfo InMenuInfo, bool bSelection)
{
	DEBUG(Debug_UI, Log, TEXT("MenuInfo : %s,Seletion : %d"), *InMenuInfo.MenuMainName.ToString(), bSelection)

	if (bSelection)
	{
		if (const FMenuContainerInfo* MenuContainerInfo = GameMenu->GetContainerInfo(InMenuInfo.MenuTag))
		{
			GenerateMenu(*MenuContainerInfo);
		}
	}
	else
	{
		if (const FMenuGenerateInfo* FoundMenuGenerateInfo = MenuGenerateInfos.FindByKey(InMenuInfo.MenuTag))
		{
			FoundMenuGenerateInfo->CommonButtonGroup->DeselectAll();

			// FoundMenuGenerateInfo->CommonButtonGroup->ForEach([](UCommonButtonBase& Button, int32 Index)
			// 	{
			// 		if (UMenuStyle* MenuStyle = Cast<UMenuStyle>(&Button))
			// 		{
			// 			MenuStyle->NativeOnClose();
			// 		}
			// 	}
			// );

			if (IsValid(FoundMenuGenerateInfo->MenuContainerInfo.MenuContainer))
			{
				CloseUserWidget(FoundMenuGenerateInfo->MenuContainerInfo.MenuContainer);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
