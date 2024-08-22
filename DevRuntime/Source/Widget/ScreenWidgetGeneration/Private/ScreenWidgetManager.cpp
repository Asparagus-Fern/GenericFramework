// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidgetManager.h"

#include "ScreenWidgetManagerSetting.h"
#include "Blueprint/WidgetTree.h"
#include "BPFunctions/BPFunctions_Widget.h"
#include "DataAsset/GameMenuSetting.h"
#include "Group/CommonButtonGroup.h"
#include "Manager/ManagerGlobal.h"
#include "StaticFunctions/StaticFunctions_Object.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "UserWidget/GameHUD.h"
#include "UserWidget/Menu/MenuContainer.h"
#include "UserWidget/Menu/MenuStyle.h"
#include "UWidget/GameplayTagSlot.h"

#define LOCTEXT_NAMESPACE "UScreenWidgetManager"

UScreenWidgetManager::UScreenWidgetManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickable = true;
}

/* ==================== IProcedureBaseInterface ==================== */

void UScreenWidgetManager::NativeOnRefresh()
{
	Super::NativeOnRefresh();

	if (!bProcessingMenuSelection && !TargetMenuSelection.IsEmpty())
	{
		bProcessingMenuSelection = true;

		for (const auto& MenuStyle : GetMenuStyles())
		{
			MenuStyle->CommonButton->SetIsInteractionEnabled(false);
		}

		HandleMenuResponseStateChanged();
	}
}

/* ==================== IProcedureInterface ==================== */

void UScreenWidgetManager::NativeOnActived()
{
	Super::NativeOnActived();

	UInteractableUserWidgetBase::AddInteractableWidget.AddUObject(this, &UScreenWidgetManager::AddInteractableWidget);
	UInteractableUserWidgetBase::RemoveInteractableWidget.AddUObject(this, &UScreenWidgetManager::RemoveInteractableWidget);

	UGameplayTagSlot::OnGameplayTagSlotBuild.AddUObject(this, &UScreenWidgetManager::RegisterSlot);
	UGameplayTagSlot::OnGameplayTagSlotDestroy.AddUObject(this, &UScreenWidgetManager::UnRegisterSlot);

	if (UScreenWidgetManagerSetting::Get()->AutoCreateGameHUD)
	{
		PreHUDCreated.Broadcast();
		CreateGameHUDs();
		PostHUDCreated.Broadcast();
	}

	if (UScreenWidgetManagerSetting::Get()->AutoCreateMenu)
	{
		if (!UScreenWidgetManagerSetting::Get()->DefaultGameMenuSetting.IsNull())
		{
			UGameMenuSetting* DefaultGameMenuSetting = FStaticFunctions_Object::LoadObject<UGameMenuSetting>(UScreenWidgetManagerSetting::Get()->DefaultGameMenuSetting);
			if (IsValid(DefaultGameMenuSetting))
			{
				SwitchGameMenu(DefaultGameMenuSetting);
			}
		}
	}
}

void UScreenWidgetManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	/* 清除菜单 */
	SwitchGameMenu(nullptr);

	/* 清除插槽 */
	ClearupSlots();

	/* 清除HUD */
	PreHUDDestroyed.Broadcast();
	ClearupGameHUDs();
	PostHUDDestroyed.Broadcast();

	/* 清除绑定的代理 */
	UGameplayTagSlot::OnGameplayTagSlotBuild.RemoveAll(this);
	UGameplayTagSlot::OnGameplayTagSlotDestroy.RemoveAll(this);

	UInteractableUserWidgetBase::AddInteractableWidget.RemoveAll(this);
	UInteractableUserWidgetBase::RemoveInteractableWidget.RemoveAll(this);
}

/* ==================== Interactable Widget Group ==================== */

void UScreenWidgetManager::AddInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName)
{
	if (!InteractableWidgetGroups.Contains(GroupName))
	{
		UCommonButtonGroup* NewGroup = NewObject<UCommonButtonGroup>(this);
		InteractableWidgetGroups.FindOrAdd(GroupName, NewGroup);
	}

	if (IsValid(InteractableWidget->CommonButton))
	{
		InteractableWidgetGroups.FindRef(GroupName)->AddWidget(InteractableWidget->CommonButton);
	}
}

void UScreenWidgetManager::RemoveInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName)
{
	UCommonButtonGroup* Group = InteractableWidgetGroups.FindRef(GroupName);
	if (IsValid(Group))
	{
		if (IsValid(InteractableWidget->CommonButton))
		{
			Group->RemoveWidget(InteractableWidget->CommonButton);
		}

		if (Group->GetButtonCount() == 0)
		{
			InteractableWidgetGroups.Remove(GroupName);
		}
	}
}

void UScreenWidgetManager::ClearupInteractableWidgetGroup(const FString& GroupName, const bool DeselectAll)
{
	if (InteractableWidgetGroups.Contains(GroupName))
	{
		UCommonButtonGroup* RemoveGroup = InteractableWidgetGroups.FindAndRemoveChecked(GroupName);
		if (DeselectAll)
		{
			RemoveGroup->DeselectAll();
		}
	}
}

bool UScreenWidgetManager::FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group) const
{
	if (InteractableWidgetGroups.Contains(GroupName))
	{
		Group = InteractableWidgetGroups.FindRef(GroupName);
		return true;
	}

	return false;
}

/* ==================== Game HUD ==================== */

void UScreenWidgetManager::CreateGameHUDs()
{
	for (const auto GameHUDClass : UScreenWidgetManagerSetting::Get()->GameHUDClasses)
	{
		if (GameHUDClass.IsNull())
			continue;

		TArray<TSubclassOf<UGameHUD>> GameHUDClasses;
		for (const auto& GameHUD : GameHUDs)
		{
			GameHUDClasses.Add(GameHUD->GetClass());
		}

		if (GameHUDClasses.Contains(GameHUDClass))
			continue;

		TSubclassOf<UGameHUD> LoadHUDClass = FStaticFunctions_Object::LoadClass<UGameHUD>(GameHUDClass);
		if (IsValid(LoadHUDClass))
		{
			UGameHUD* NewHUD = CreateWidget<UGameHUD>(GetWorld(), LoadHUDClass);
			CreateGameHUD(NewHUD);
		}
	}
}

void UScreenWidgetManager::CreateGameHUD(UGameHUD* GameHUD)
{
	if (!GameHUDs.Contains(GameHUD))
	{
		GameHUDs.Add(GameHUD);
		GameHUD->AddToViewport(GameHUD->ViewportZOrder);

		ActiveWidget(GameHUD);
		OnHUDCreated.Broadcast(GameHUD);
	}
}

void UScreenWidgetManager::ClearupGameHUDs()
{
	TArray<UGameHUD*> TempGameHUDs = GameHUDs;
	for (const auto& GameHUD : TempGameHUDs)
	{
		RemoveGameHUD(GameHUD);
	}
}

void UScreenWidgetManager::RemoveGameHUD(UGameHUD* GameHUD)
{
	if (GameHUDs.Contains(GameHUD))
	{
		GameHUDs.Remove(GameHUD);
		InactiveWidget(GameHUD, true);

		OnHUDDestroyed.Broadcast(GameHUD);
	}
}

void UScreenWidgetManager::RemoveGameHUD(const FGameplayTag InTag)
{
	TArray<UGameHUD*> TempGameHUDs = GameHUDs;
	for (const auto& GameHUD : TempGameHUDs)
	{
		if (GameHUD->SelfTag == InTag)
		{
			RemoveGameHUD(GameHUD);
		}
	}
}

TArray<UGameHUD*> UScreenWidgetManager::GetGameHUDByTag(const FGameplayTag InTag)
{
	TArray<UGameHUD*> Result;
	for (auto& HUD : GameHUDs)
	{
		if (HUD->SelfTag == InTag)
		{
			Result.Add(HUD);
		}
	}
	return Result;
}

void UScreenWidgetManager::SetGameHUDVisibility(const bool IsVisisble)
{
	for (const auto& GameHUD : GameHUDs)
	{
		SetGameHUDVisibility(GameHUD, IsVisisble);
	}
}

void UScreenWidgetManager::SetGameHUDVisibility(UGameHUD* GameHUD, const bool IsVisisble)
{
	GameHUD->PlayAnimationEvent(IsVisisble);
	GameHUD->SetIsActived(IsVisisble);
}

void UScreenWidgetManager::SetGameHUDVisibility(const FGameplayTag InTag, const bool IsVisisble)
{
	for (const auto& GameHUD : GetGameHUDByTag(InTag))
	{
		SetGameHUDVisibility(GameHUD, IsVisisble);
	}
}

void UScreenWidgetManager::AddTemporaryGameHUD(UUserWidgetBase* InWidget)
{
	TArray<TSubclassOf<UGameHUD>> GameHUDClasses;
	for (const auto& GameHUD : GameHUDs)
	{
		GameHUDClasses.Add(GameHUD->GetClass());
	}

	/* 确保已经创建的HUD不会被二次创建 */
	for (auto& TemporaryHUDClass : InWidget->TemporaryHUDs)
	{
		if (!GameHUDClasses.Contains(TemporaryHUDClass))
		{
			UGameHUD* NewTemporaryHUD = CreateWidget<UGameHUD>(GetWorld(), TemporaryHUDClass);
			CreateGameHUD(NewTemporaryHUD);
		}
	}
}

void UScreenWidgetManager::RemoveTemporaryGameHUD(UUserWidgetBase* InWidget)
{
	/* 项目设置里的HUD类 */
	TArray<TSubclassOf<UGameHUD>> SettingGameHUDClasses;
	for (auto& GameHUDClass : UScreenWidgetManagerSetting::Get()->GameHUDClasses)
	{
		if (!GameHUDClass.IsNull())
		{
			SettingGameHUDClasses.Add(GameHUDClass.Get());
		}
	}

	/* 获取当前所有HUD的类集合 */
	TSet<TSubclassOf<UGameHUD>> GameHUDClasses;
	for (const auto& GameHUD : GameHUDs)
	{
		/* 不移除项目设置的HUD */
		if (!SettingGameHUDClasses.Contains(GameHUD->GetClass()))
		{
			GameHUDClasses.Add(GameHUD->GetClass());
		}
	}

	/* 获取当前激活的所有Widget的临时HUD类集合，不包括InWidget */
	TSet<TSubclassOf<UGameHUD>> ActivedWidgetTemporaryHUDClasses;
	for (const auto& ActivedWidget : ActivedWidgets)
	{
		if (ActivedWidget == InWidget)
		{
			continue;
		}

		for (auto& TemporaryHUDClass : ActivedWidget->TemporaryHUDs)
		{
			ActivedWidgetTemporaryHUDClasses.Add(TemporaryHUDClass);
		}
	}

	/* 获取两个集合交集 */
	TSet<TSubclassOf<UGameHUD>> Intersect = GameHUDClasses.Intersect(ActivedWidgetTemporaryHUDClasses);
	for (auto& TemporaryHUDClass : InWidget->TemporaryHUDs)
	{
		/* 如果交集不包括InWidget的临时的HUD类，表示该Widget的HUD并没有被其他Widget使用，移除该临时HUD */
		if (!Intersect.Contains(TemporaryHUDClass))
		{
			TArray<UGameHUD*> TempGameHUDs = GameHUDs;
			for (const auto& TempGameHUD : TempGameHUDs)
			{
				if (TempGameHUD->GetClass() == TemporaryHUDClass)
				{
					RemoveGameHUD(TempGameHUD);
				}
			}
		}
	}
}

/* ==================== UGameplayTagSlot ==================== */

void UScreenWidgetManager::RegisterSlot(UGameplayTagSlot* InSlot)
{
	if (!IsValid(InSlot) || !InSlot->SlotTag.IsValid() || Slots.Contains(InSlot))
	{
		LOG(Debug_UI, Warning, TEXT("Fail To RegisterSlot"))
		return;
	}

	Slots.Add(InSlot);
	InSlot->ClearChildren();
}

void UScreenWidgetManager::UnRegisterSlot(UGameplayTagSlot* InSlot)
{
	if (!IsValid(InSlot) || !InSlot->SlotTag.IsValid() || !Slots.Contains(InSlot))
	{
		LOG(Debug_UI, Warning, TEXT("Fail To UnRegisterSlot"))
		return;
	}

	Slots.Remove(InSlot);
}

UGameplayTagSlot* UScreenWidgetManager::GetSlot(const FGameplayTag InSlotTag) const
{
	if (!InSlotTag.IsValid())
	{
		LOG(Debug_UI, Error, TEXT("InSlotTag Is NULL"))
		return nullptr;
	}

	for (const auto& Slot : Slots)
	{
		if (Slot->SlotTag == InSlotTag)
		{
			return Slot;
		}
	}

	return nullptr;
}

void UScreenWidgetManager::ClearupSlots()
{
	TArray<UUserWidgetBase*> TempActivedWidgets = ActivedWidgets;
	for (const auto& TempActivedWidget : TempActivedWidgets)
	{
		InactiveWidget(TempActivedWidget, true);
	}

	Slots.Reset();
}

/* ==================== User Widget Base ==================== */

UUserWidgetBase* UScreenWidgetManager::OpenUserWidget(const TSubclassOf<UUserWidgetBase> InWidgetClass, const FOnWidgetActiveStateChanged OnFinish)
{
	UUserWidgetBase* NewWidget = CreateWidget<UUserWidgetBase>(GetWorld(), InWidgetClass);
	OpenUserWidget(NewWidget, OnFinish);
	return NewWidget;
}

void UScreenWidgetManager::OpenUserWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget) || !InWidget->SlotTag.IsValid())
	{
		LOG(Debug_UI, Warning, TEXT("Fail To Open User Widget"))
		return;
	}

	const UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag);
	if (IsValid(Slot))
	{
		/* 当前插槽是否已有其他Widget */
		UUserWidgetBase* RemoveWidget = nullptr;
		for (const auto& ActivedWidget : ActivedWidgets)
		{
			if (ActivedWidget->SlotTag == InWidget->SlotTag)
			{
				RemoveWidget = ActivedWidget;
			}
		}

		if (IsValid(RemoveWidget))
		{
			InactiveWidget
			(
				RemoveWidget,
				FOnWidgetActiveStateChanged::CreateLambda([this, &InWidget, &OnFinish](UUserWidgetBase*)
					{
						ActiveWidget(InWidget, OnFinish);
					}
				)
			);
		}
		else
		{
			ActiveWidget(InWidget, OnFinish);
		}
	}
}

void UScreenWidgetManager::CloseUserWidget(UUserWidgetBase* InWidget, const FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget))
	{
		LOG(Debug_UI, Error, TEXT("InWidget Is NULL"))
		return;
	}

	InactiveWidget(InWidget, OnFinish);
}

void UScreenWidgetManager::CloseUserWidget(const FGameplayTag InSlotTag, const FOnWidgetActiveStateChanged OnFinish)
{
	if (!InSlotTag.IsValid())
	{
		LOG(Debug_UI, Error, TEXT("SlotTag Is NULL"))
		return;
	}

	for (const auto& ActivedWidget : ActivedWidgets)
	{
		if (ActivedWidget->SlotTag == InSlotTag)
		{
			CloseUserWidget(ActivedWidget, OnFinish);
		}
	}
}

void UScreenWidgetManager::ActiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget) || ActivedWidgets.Contains(InWidget))
	{
		LOG(Debug_UI, Error, TEXT("InWidget Is NULL"))
		OnFinish.ExecuteIfBound(InWidget);
		return;
	}

	AddTemporaryGameHUD(InWidget);

	if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
	{
		Slot->AddChild(InWidget);
	}

	InWidget->NativeOnCreate();
	ActivedWidgets.Add(InWidget);

	if (IWidgetAnimationInterface::Execute_HasAnimationEvent(InWidget, true))
	{
		IWidgetAnimationInterface::Execute_PlayAnimationEvent(InWidget, true);

		/* 在动画结束之后广播完成 */
		if (IWidgetAnimationInterface::Execute_GetAnimationDuration(InWidget, true) > 0.f)
		{
			FTimerHandle TimerHandle;
			WidgetTimerHandles.Add(InWidget, TimerHandle);

			auto OnActiveStateChangedFinish = [this, &InWidget, &OnFinish]()
			{
				WidgetTimerHandles.Remove(InWidget);
				OnFinish.ExecuteIfBound(InWidget);
			};

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda(OnActiveStateChangedFinish), IWidgetAnimationInterface::Execute_GetAnimationDuration(InWidget, true), false);
			return;
		}
	}

	OnFinish.ExecuteIfBound(InWidget);
	OnWidgetOpen.Broadcast(InWidget);
}

void UScreenWidgetManager::ActiveWidget(UUserWidgetBase* InWidget, const bool bIsInstant, const FOnWidgetActiveStateChanged OnFinish)
{
	if (bIsInstant)
	{
		if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
		{
			Slot->AddChild(InWidget);
		}

		InWidget->NativeOnCreate();
		ActivedWidgets.Add(InWidget);
		OnFinish.ExecuteIfBound(InWidget);
	}
	else
	{
		ActiveWidget(InWidget, OnFinish);
	}
}

void UScreenWidgetManager::InactiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget) || !ActivedWidgets.Contains(InWidget))
	{
		LOG(Debug_UI, Error, TEXT("InWidget Is NULL"))
		OnFinish.ExecuteIfBound(InWidget);
		return;
	}

	InWidget->NativeOnDestroy();

	if (IWidgetAnimationInterface::Execute_HasAnimationEvent(InWidget, false))
	{
		IWidgetAnimationInterface::Execute_PlayAnimationEvent(InWidget, false);

		/* 在动画结束之后清除 */
		if (IWidgetAnimationInterface::Execute_GetAnimationDuration(InWidget, false) > 0.f)
		{
			FTimerHandle TimerHandle;
			WidgetTimerHandles.Add(InWidget, TimerHandle);

			auto OnActiveStateChangedFinish = [this, &InWidget, &OnFinish]()
			{
				if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
				{
					Slot->RemoveChild(InWidget);
				}

				ActivedWidgets.Remove(InWidget);
				WidgetTimerHandles.Remove(InWidget);
				OnWidgetClose.Broadcast(InWidget);
				OnFinish.ExecuteIfBound(InWidget);

				RemoveTemporaryGameHUD(InWidget);

				InWidget->MarkAsGarbage();
			};

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda(OnActiveStateChangedFinish), IWidgetAnimationInterface::Execute_GetAnimationDuration(InWidget, true), false);
			return;
		}
	}

	ActivedWidgets.Remove(InWidget);
	OnFinish.ExecuteIfBound(InWidget);
}

void UScreenWidgetManager::InactiveWidget(UUserWidgetBase* InWidget, const bool bIsInstant, const FOnWidgetActiveStateChanged OnFinish)
{
	if (bIsInstant)
	{
		if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
		{
			Slot->RemoveChild(InWidget);
		}

		InWidget->NativeOnDestroy();
		ActivedWidgets.Remove(InWidget);
		OnFinish.ExecuteIfBound(InWidget);
		InWidget->MarkAsGarbage();
	}
	else
	{
		InactiveWidget(InWidget, OnFinish);
	}
}

/* ==================== Game Menu ==================== */

void UScreenWidgetManager::SwitchGameMenu(UGameMenuSetting* InGameMenuSetting)
{
	if (IsValid(GameMenu))
	{
		// MenuGenerateInfos.Reset();
		// CurrentActiveMenuTag = FGameplayTag::EmptyTag;
		// LastActiveMenuTag = FGameplayTag::EmptyTag;
		//
		// MenuSelectionChangedHandle.Reset();
		// TargetMenuSelection.Reset();
		// UpdateMenuSelectionHandle.Invalidate();
		// TargetMenuSelectionIndex = 0;
	}

	/* Generate Root Menu */
	GameMenu = InGameMenuSetting;
	if (IsValid(GameMenu))
	{
		GenerateMenu(GameMenu->GetRootMenuTag());
	}
}

void UScreenWidgetManager::SelectMenu(const FGameplayTag InMenuTag)
{
	if (FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(InMenuTag))
	{
		const UMenuStyle* MenuStyle = MenuGenerateInfo->GetMenuStyle(InMenuTag);
		if (IsValid(MenuStyle->CommonButton))
		{
			if (MenuGenerateInfo->MenuContainer->bIsManagedByGroup)
			{
				MenuGenerateInfo->MenuContainer->CommonButtonGroup->SelectButtonAtIndex(MenuGenerateInfo->MenuContainer->CommonButtonGroup->FindButtonIndex(MenuStyle->CommonButton));
			}
			else
			{
				MenuStyle->CommonButton->SetSelectedInternal(true);
			}
		}
	}
}

void UScreenWidgetManager::DeselectMenu(const FGameplayTag InMenuTag)
{
	if (FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(InMenuTag))
	{
		const UMenuStyle* MenuStyle = MenuGenerateInfo->GetMenuStyle(InMenuTag);
		if (IsValid(MenuStyle) && IsValid(MenuStyle->CommonButton))
		{
			MenuStyle->CommonButton->SetSelectedInternal(false);
		}
	}
}

TArray<UMenuStyle*> UScreenWidgetManager::GetMenuStyles()
{
	TArray<UMenuStyle*> MenuStyles;

	for (auto& MenuGenerateInfo : MenuGenerateInfos)
	{
		MenuStyles.Append(MenuGenerateInfo.MenuStyles);
	}

	return MenuStyles;
}

void UScreenWidgetManager::GenerateMenu(const FGameplayTag InMenuTag)
{
	if (InMenuTag.IsValid())
	{
		GenerateMenu(GameMenu->GetChildMenuTags(InMenuTag));
	}
	else
	{
		LOG(Debug_UI, Error, TEXT("Fail To Generate Menu"))
	}
}

void UScreenWidgetManager::GenerateMenu(TArray<FGameplayTag> InMenuTags)
{
	/* 筛选有效的MenuInfo */
	TArray<FMenuInfo> ValidMenuInfos;
	for (auto& InMenuTag : InMenuTags)
	{
		if (!InMenuTag.IsValid())
		{
			LOG(Debug_UI, Error, TEXT("Menu Is InValid"))
			continue;
		}

		FMenuInfo MenuInfo;
		if (GameMenu->GetMenuInfo(InMenuTag, MenuInfo))
		{
			if (!MenuInfo.Container || !MenuInfo.Style)
			{
				LOG(Debug_UI, Error, TEXT("Menu Container/Style Is InValid"))
				continue;
			}

			ValidMenuInfos.Add(MenuInfo);
		}
		else
		{
			LOG(Debug_UI, Error, TEXT("Fail To GetMenuInfo"))
		}
	}

	/* 参与构建菜单的容器 */
	TArray<UMenuContainer*> MenuContainers;

	/* 构建菜单 */
	for (auto& MenuInfo : ValidMenuInfos)
	{
		/* 查找MenuGenerateInfo是否存在 */
		FMenuGenerateInfo* FoundMenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuInfo.Container);

		/* 不存在则创建新的MenuGenerateInfo */
		if (!FoundMenuGenerateInfo)
		{
			/* 创建菜单容器 */
			UMenuContainer* MenuContainer = CreateWidget<UMenuContainer>(GetWorld(), MenuInfo.Container);
			FMenuGenerateInfo NewMenuGenerateInfo = FMenuGenerateInfo(MenuContainer);
			MenuGenerateInfos.Add(NewMenuGenerateInfo);

			OpenUserWidget(MenuContainer);
		}

		/* 再次查找 */
		FoundMenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuInfo.Container);
		if (FoundMenuGenerateInfo)
		{
			MenuContainers.Add(FoundMenuGenerateInfo->MenuContainer);

			/* 创建菜单样式 */
			UMenuStyle* MenuStyle = CreateWidget<UMenuStyle>(GetWorld(), MenuInfo.Style);
			MenuStyle->MenuContainer = FoundMenuGenerateInfo->MenuContainer;

			/* 接管菜单的响应处理 */
			if (UScreenWidgetManagerSetting::Get()->ProcessingMenuSelection)
			{
				MenuStyle->OnResponseStateChanged.BindUObject(this, &UScreenWidgetManager::OnMenuResponseStateChanged);
			}

			/* 构建菜单样式 */
			MenuStyle->NativePreConstructMenuStyle(MenuInfo);

			/* 构建菜单容器 */
			const int32 Index = FoundMenuGenerateInfo->MenuContainer->GetCommonButtonGroup()->GetButtonCount();
			FoundMenuGenerateInfo->MenuStyles.Add(MenuStyle);
			FoundMenuGenerateInfo->MenuContainer->NativeConstructMenuContainer(MenuStyle, Index);

			ActiveWidget(MenuStyle);
			MenuStyle->NativeConstructMenuStyle(MenuInfo);

			/* 当前正在执行菜单的事件 */
			if (bProcessingMenuSelection)
			{
				MenuStyle->CommonButton->SetIsInteractionEnabled(false);
			}
		}
	}

	/* 构建菜单容器完成后 */
	for (auto& MenuContainer : MenuContainers)
	{
		MenuContainer->NativePostConstructMenuContainer();
	}

	/* 是否默认选中 */
	for (auto& MenuInfo : ValidMenuInfos)
	{
		if (!MenuInfo.bHidden && MenuInfo.bIsEnable && MenuInfo.bSelectable && MenuInfo.bIsSelected)
		{
			SelectMenu(MenuInfo.MenuTag);
		}
	}
}

void UScreenWidgetManager::DestroyMenu(FGameplayTag InMenuTag)
{
	DestroyMenu(GameMenu->GetChildMenuTags(InMenuTag));
}

void UScreenWidgetManager::DestroyMenu(TArray<FGameplayTag> InMenuTags)
{
	const auto OnMenuInactived = FOnWidgetActiveStateChanged::CreateLambda([this](UUserWidgetBase* InWidget)
		{
			UMenuStyle* MenuStyle = Cast<UMenuStyle>(InWidget);
			FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuStyle);
			MenuGenerateInfo->ClearupGarbageMenuStyle();
		}
	);

	for (auto& MenuTag : InMenuTags)
	{
		if (FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuTag))
		{
			UMenuStyle* MenuStyle = MenuGenerateInfo->GetMenuStyle(MenuTag);
			MenuGenerateInfo->MarkMenuStyleAsGarbage(MenuStyle);
			InactiveWidget(MenuStyle, OnMenuInactived);
		}
	}
}

FReply UScreenWidgetManager::OnMenuResponseStateChanged(UInteractableUserWidgetBase* InteractableWidget, bool TargetEventState)
{
	if (UMenuStyle* TargetMenuStyle = Cast<UMenuStyle>(InteractableWidget))
	{
		const FMenuInfo MenuInfo = TargetMenuStyle->GetMenuInfo();
		PRINT(Log, TEXT("MenuInfo : %s,Seletion : %d"), *MenuInfo.MenuMainName.ToString(), TargetEventState)

		if (const FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(TargetMenuStyle->GetMenuContainer()))
		{
			if (!MenuGenerateInfo->MenuContainer->bIsManagedByGroup)
			{
				return FReply::Unhandled();
			}

			TargetMenuSelection.FindOrAdd(TargetMenuStyle, TargetEventState);

			/* 查找该菜单的子菜单信息 */
			TArray<FMenuGenerateInfo*> ChildMenuGenerateInfos;
			for (auto& MenuTag : GameMenu->GetChildMenuTags(TargetMenuStyle->GetMenuTag()))
			{
				if (FMenuGenerateInfo* ChildMenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuTag))
				{
					ChildMenuGenerateInfos.AddUnique(ChildMenuGenerateInfo);
				}
			}

			/* 取消选中子菜单 */
			for (const auto& ChildMenuGenerateInfo : ChildMenuGenerateInfos)
			{
				ChildMenuGenerateInfo->MenuContainer->CommonButtonGroup->SetSelectionRequired(false);
				ChildMenuGenerateInfo->MenuContainer->CommonButtonGroup->DeselectAll();
			}

			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}

void UScreenWidgetManager::HandleMenuResponseStateChanged()
{
	TArray<UMenuStyle*> MenuStyles;
	TargetMenuSelection.GetKeys(MenuStyles);

	/* 在每次菜单事件完成之后，移除子菜单或生成子菜单，如果存在的话 */
	if (ProcessingIndex > 0)
	{
		const UMenuStyle* PreviousMenuStyle = MenuStyles[ProcessingIndex - 1];
		if (const bool PreviousEventState = TargetMenuSelection.FindRef(PreviousMenuStyle))
		{
			GenerateMenu(PreviousMenuStyle->GetMenuTag());
		}
		else
		{
			DestroyMenu(PreviousMenuStyle->GetMenuTag());
		}
	}

	/* 执行当前菜单的事件 */
	if (MenuStyles.IsValidIndex(ProcessingIndex))
	{
		UMenuStyle* TargetMenuStyle = MenuStyles[ProcessingIndex];
		const FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(TargetMenuStyle);
		const bool TargetEventState = TargetMenuSelection.FindRef(TargetMenuStyle);

		if (!TargetMenuStyle->GetResponseEvents(TargetEventState).IsEmpty())
		{
			TargetMenuStyle->HandleButtonResponseEvent(TargetMenuStyle->GetResponseEvents(TargetEventState), TargetEventState, FSimpleDelegate::CreateUObject(this, &UScreenWidgetManager::HandleMenuResponseStateChanged));
		}

		ProcessingIndex++;
		HandleMenuResponseStateChanged();
	}
	/* 所有菜单都已经触发 */
	else
	{
		for (const auto& MenuStyle : GetMenuStyles())
		{
			MenuStyle->CommonButton->SetIsInteractionEnabled(true);
		}

		TargetMenuSelection.Reset();
		bProcessingMenuSelection = false;
		ProcessingIndex = 0;
	}
}

#undef LOCTEXT_NAMESPACE
