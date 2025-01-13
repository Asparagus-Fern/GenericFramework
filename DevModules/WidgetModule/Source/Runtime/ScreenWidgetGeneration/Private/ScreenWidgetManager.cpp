// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidgetManager.h"

#include "ScreenWidgetManagerSetting.h"
#include "Blueprint/WidgetTree.h"
#include "BPFunctions/BPFunctions_Object.h"
#include "BPFunctions/BPFunctions_Widget.h"
#include "DataAsset/GameMenuSetting.h"
#include "Group/CommonButtonGroup.h"
#include "Input/InputManager.h"
#include "Kismet/GameplayStatics.h"
#include "Shortcut/ShortcutWidgetHandle.h"
#include "UWidget/Override/GameplayTagSlot.h"

#define LOCTEXT_NAMESPACE "ScreenWidgetManager"


/* ==================== UScreenWidgetManager ==================== */

UScreenWidgetManager::FOnMenuSelectionChanged UScreenWidgetManager::OnMenuSelectionChanged;

/* ==================== IProcedureBaseInterface ==================== */

bool UScreenWidgetManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UScreenWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UScreenWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UScreenWidgetManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UScreenWidgetManager::Tick(float DeltaTime)
{
	FTickableInternalManager::Tick(DeltaTime);

	/* 处理按钮事件 */
	if (!bProcessingMenuSelection && !TargetMenuSelection.IsEmpty())
	{
		bProcessingMenuSelection = true;
		HandleMenuResponseStateChanged();
	}

	/* 清理生成的菜单信息 */
	if (bClearupMenuGenerateInfos)
	{
		bClearupMenuGenerateInfos = false;

		TArray<FMenuGenerateInfo> TempMenuGenerateInfos = MenuGenerateInfos;
		for (auto& TempMenuGenerateInfo : TempMenuGenerateInfos)
		{
			if (!TempMenuGenerateInfo.GetIsValid())
			{
				MenuGenerateInfos.Remove(TempMenuGenerateInfo);
			}
		}
	}
}

void UScreenWidgetManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);
}

void UScreenWidgetManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

void UScreenWidgetManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);
}

/* ==================== User Widget Base ==================== */

/*UUserWidgetBase* UScreenWidgetManager::GetContainerWidget(const FWidgetContainer& WidgetContainer)
{
	if (WidgetContainer.bInstance && IsValid(WidgetContainer.Widget))
	{
		return DuplicateObject<UUserWidgetBase>(WidgetContainer.Widget, GetWorld());
	}
	else if (!WidgetContainer.bInstance && IsValid(WidgetContainer.WidgetClass))
	{
		return CreateWidget<UUserWidgetBase>(GetWorld(), WidgetContainer.WidgetClass);
	}

	return nullptr;
}


void UScreenWidgetManager::MoveUserWidget(FGameplayTag OriginSlotTag, FGameplayTag TargetSlotTag, FOnWidgetActiveStateChanged OnFinish)
{
	DEnsureLOG(DLogUI, OriginSlotTag.IsValid() && TargetSlotTag.IsValid())

	const UUserWidgetBase* MoveWidget = GetSlotWidget(OriginSlotTag);
	DEnsureLOG(DLogUI, IsValid(MoveWidget))

	const UGameplayTagSlot* OriginWidgetSlot = GetSlot(OriginSlotTag);
	const UGameplayTagSlot* TargetWidgetSlot = GetSlot(TargetSlotTag);
	DEnsureLOG(DLogUI, IsValid(OriginWidgetSlot) && IsValid(TargetWidgetSlot))

	UUserWidgetBase* CopyWidget = DuplicateObject(MoveWidget, MoveWidget->GetOuter(), MoveWidget->GetFName());
	CopyWidget->SlotTag = TargetWidgetSlot->SlotTag;
	CopyWidget->SetOwningPlayer(TargetWidgetSlot->GetOwningPlayer());

	CloseUserWidget(OriginWidgetSlot->SlotTag);
	OpenUserWidget(CopyWidget);
	return;

	/*
	/* Widget进入 #2#
	auto OnWidgetMoveIn = [this, &MoveWidget, &OnFinish]()
	{
		if (const FWidgetAnimationTimerHandle* Found = WidgetAnimationTimerHandles.FindByKey(MoveWidget))
		{
			Found->OnFinish.ExecuteIfBound(Found->Widget);
			WidgetAnimationTimerHandles.Remove(*Found);
		}
		else
		{
			OnFinish.ExecuteIfBound(MoveWidget);
		}
	};

	/* Widget移出 #2#
	auto OnWidgetMoveOut = [this, &MoveWidget, &TargetWidgetSlot, &OnFinish, &OnWidgetMoveIn]()
	{
		TargetWidgetSlot->AddChild(MoveWidget);
		// MoveWidget->RemoveFromParent();
		// MoveWidget->AddToViewport();
		// MoveWidget->TakeWidget()->SlatePrepass();

		const FTimerHandle TimerHandle = PlayWidgetAnimation(MoveWidget, true, FTimerDelegate::CreateLambda(OnWidgetMoveIn));
		if (TimerHandle.IsValid())
		{
			WidgetAnimationTimerHandles.Add(FWidgetAnimationTimerHandle(TimerHandle, MoveWidget, OnFinish));
			return;
		}

		OnWidgetMoveIn();
	};

	/* 如果有动画的话 #2#
	const FTimerHandle TimerHandle = PlayWidgetAnimation(MoveWidget, false, FTimerDelegate::CreateLambda(OnWidgetMoveOut));
	if (TimerHandle.IsValid())
	{
		return;
	}

	OnWidgetMoveOut();#1#
}*/

/* ==================== Game Menu ==================== */

void UScreenWidgetManager::SwitchGameMenu(UGameMenuSetting* InGameMenuSetting)
{
	/*if (GameMenu == InGameMenuSetting)
	{
		DLOG(DLogUI, Warning, TEXT("Can not Switch The Same Game Menu Setting"))
		return;
	}

	/* 销毁菜单 #1#
	if (IsValid(GameMenu))
	{
		TArray<FMenuGenerateInfo> TempMenuGenerateInfos = MenuGenerateInfos;
		if (TempMenuGenerateInfos.IsValidIndex(0))
		{
			/* 当存在选中菜单时，退出所有的选中菜单再进行销毁 #1#
			if (IsValid(TempMenuGenerateInfos[0].ActivedMenuStyle))
			{
				DeselectMenu(TempMenuGenerateInfos[0].ActivedMenuStyle->GetMenuTag());

				bSwitchingGameMenu = true;
				WaitingGameMenu = InGameMenuSetting;
				return;
			}
		}

		/* 不存在选中菜单时，直接进行销毁 #1#
		DestroyMenu(GameMenu->GetRootMenuTag());
	}

	/* 生成新的菜单 #1#
	GameMenu = InGameMenuSetting;
	if (IsValid(GameMenu))
	{
		GenerateMenu(GameMenu->GetRootMenuTag());
	}*/
}

void UScreenWidgetManager::SelectMenu(const FGameplayTag InMenuTag)
{
	/*FMenuContainerInfo MenuContainerInfo;

	if (GameMenu->GetMenuContainerInfo(InMenuTag, MenuContainerInfo))
	{
		if (FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuContainerInfo))
		{
			const UMenuStyle* MenuStyle = MenuGenerateInfo->GetMenuStyle(InMenuTag);

			if (IsValid(MenuStyle) && IsValid(MenuStyle->ActiveCommonButton) && ActivedWidgets.Contains(MenuGenerateInfo->MenuContainer) && ActivedWidgets.Contains(MenuStyle))
			{
				if (MenuGenerateInfo->MenuContainer->bIsManagedByGroup)
				{
					MenuGenerateInfo->MenuContainer->CommonButtonGroup->SelectButtonAtIndex(MenuGenerateInfo->MenuContainer->CommonButtonGroup->FindButtonIndex(MenuStyle->ActiveCommonButton));
				}
				else
				{
					MenuStyle->ActiveCommonButton->SetSelectedInternal(true);
				}
			}
		}
		/* 父级还未创建，递归创建父级，然后再选中自己 #1#
		else
		{
			SelectedMenuCache.Add(InMenuTag);

			FGameplayTag SelectTag = InMenuTag;
			FMenuContainerInfo SelectedContainerInfo;
			while (GameMenu->GetMenuContainerInfo(SelectTag, SelectedContainerInfo))
			{
				if (!MenuGenerateInfos.FindByKey(SelectedContainerInfo))
				{
					SelectTag = SelectedContainerInfo.OwnerTag;
					SelectedMenuCache.Add(SelectTag);
				}
				else
				{
					break;
				}
			}

			SelectMenuRecursiveHandle = OnMenuSelectionChanged.AddUObject(this, &UScreenWidgetManager::HandleSelectMenuRecursive);

			if (SelectedMenuCache.Num() > 0)
			{
				const FGameplayTag LastMenuTag = SelectedMenuCache.Last();
				SelectMenu(LastMenuTag);
			}
		}
	}*/
}

void UScreenWidgetManager::DeselectMenu(const FGameplayTag InMenuTag)
{
	/*FMenuContainerInfo MenuContainerInfo;
	GameMenu->GetMenuContainerInfo(InMenuTag, MenuContainerInfo);

	if (FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuContainerInfo))
	{
		const UMenuStyle* MenuStyle = MenuGenerateInfo->GetMenuStyle(InMenuTag);
		if (IsValid(MenuStyle) && IsValid(MenuStyle->ActiveCommonButton) && ActivedWidgets.Contains(MenuGenerateInfo->MenuContainer) && ActivedWidgets.Contains(MenuStyle))
		{
			if (MenuGenerateInfo->MenuContainer->bIsManagedByGroup)
			{
				MenuGenerateInfo->MenuContainer->CommonButtonGroup->DeselectAll();
			}
			else
			{
				MenuStyle->ActiveCommonButton->SetSelectedInternal(false);
			}
		}
	}*/
}

void UScreenWidgetManager::HandleSelectMenuRecursive(FGameplayTag MenuTag, bool IsSelected)
{
	/*if (!SelectedMenuCache.IsEmpty())
	{
		SelectedMenuCache.Remove(MenuTag);

		if (!SelectedMenuCache.IsEmpty())
		{
			const FGameplayTag LastMenuTag = SelectedMenuCache.Last();
			SelectMenu(LastMenuTag);
		}
	}
	else
	{
		OnMenuSelectionChanged.Remove(SelectMenuRecursiveHandle);
		SelectMenuRecursiveHandle.Reset();
	}*/
}

TArray<UMenuStyle*> UScreenWidgetManager::GetMenuStyles()
{
	TArray<UMenuStyle*> MenuStyles;

	/*for (auto& MenuGenerateInfo : MenuGenerateInfos)
	{
		MenuStyles.Append(MenuGenerateInfo.MenuStyles);
	}*/

	return MenuStyles;
}

void UScreenWidgetManager::GenerateMenu(const FGameplayTag InMenuTag)
{
	/*if (InMenuTag.IsValid())
	{
		GenerateMenu(GameMenu->GetDirectChildMenuTags(InMenuTag));
	}
	else
	{
		DLOG(DLogUI, Error, TEXT("Fail To Generate Menu"))
	}*/
}

void UScreenWidgetManager::GenerateMenu(TArray<FGameplayTag> InMenuTags)
{
	/*/* 筛选有效的MenuInfo #1#
	TArray<FMenuInfo> ValidMenuInfos;
	for (const auto& InMenuTag : InMenuTags)
	{
		if (GameMenu->CheckIsValidMenuTag(InMenuTag))
		{
			FMenuInfo MenuInfo;
			GameMenu->GetMenuInfo(InMenuTag, MenuInfo);
			ValidMenuInfos.Add(MenuInfo);
		}
	}

	/* 参与构建菜单的容器 #1#
	TArray<UMenuContainer*> MenuContainers;

	/* todo: CommonButtonGroup必须要有一个Widget才可以切换状态，是否可以分离开，没有样式类也可以对按钮进行切换 #1#

	/* 构建菜单 #1#
	for (auto& MenuInfo : ValidMenuInfos)
	{
		FMenuContainerInfo MenuContainerInfo;
		GameMenu->GetMenuContainerInfo(MenuInfo.MenuTag, MenuContainerInfo);

		/* 查找MenuGenerateInfo是否存在 #1#
		FMenuGenerateInfo* FoundMenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuContainerInfo);

		/* 不存在则创建新的MenuGenerateInfo #1#
		if (!FoundMenuGenerateInfo)
		{
			/* 创建菜单容器 #1#
			UMenuContainer* MenuContainer = nullptr;

			if (MenuContainerInfo.bUseContainerClass && MenuContainerInfo.ContainerClass)
			{
				MenuContainer = CreateWidget<UMenuContainer>(GetWorld(), MenuContainerInfo.ContainerClass);
			}
			else if (!MenuContainerInfo.bUseContainerClass && IsValid(MenuContainerInfo.Container))
			{
				MenuContainer = DuplicateObject<UMenuContainer>(MenuContainerInfo.Container, GetWorld());
			}

			FMenuGenerateInfo NewMenuGenerateInfo = FMenuGenerateInfo(MenuContainerInfo, MenuContainer);
			MenuGenerateInfos.Add(NewMenuGenerateInfo);

			if (IsValid(MenuContainer))
			{
				OpenUserWidget(MenuContainer);
			}
		}

		/* 再次查找 #1#
		FoundMenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuContainerInfo);
		if (FoundMenuGenerateInfo && ActivedWidgets.Contains(FoundMenuGenerateInfo->MenuContainer))
		{
			MenuContainers.Add(FoundMenuGenerateInfo->MenuContainer);

			/* 创建菜单样式 #1#
			UMenuStyle* MenuStyle = nullptr;

			if (MenuInfo.bUseStyleClass && IsValid(MenuInfo.StyleClass))
			{
				MenuStyle = CreateWidget<UMenuStyle>(GetWorld(), MenuInfo.StyleClass);
			}
			else if (!MenuInfo.bUseStyleClass && IsValid(MenuInfo.Style))
			{
				MenuStyle = DuplicateObject<UMenuStyle>(MenuInfo.Style, GetWorld());
			}

			if (IsValid(MenuStyle))
			{
				MenuStyle->MenuContainer = FoundMenuGenerateInfo->MenuContainer;

				/* 接管菜单的响应处理 #1#
				MenuStyle->OnResponseStateChanged.BindUObject(this, &UScreenWidgetManager::OnMenuResponseStateChanged);

				/* 构建菜单样式 #1#
				MenuStyle->NativePreConstructMenuStyle(MenuInfo);
			}

			/* 构建菜单容器 #1#
			if (FoundMenuGenerateInfo->MenuContainer)
			{
				const int32 Index = FoundMenuGenerateInfo->MenuContainer->GetCommonButtonGroup()->GetButtonCount();
				FoundMenuGenerateInfo->MenuStyles.Add(MenuStyle);
				FoundMenuGenerateInfo->MenuContainer->NativeConstructMenuContainer(MenuStyle, Index);
			}

			if (IsValid(MenuStyle))
			{
				ActiveWidget(MenuStyle);
				MenuStyle->NativeConstructMenuStyle(MenuInfo);
			}
		}
	}

	/* 构建菜单容器完成后 #1#
	for (auto& MenuContainer : MenuContainers)
	{
		MenuContainer->NativePostConstructMenuContainer();
	}

	/* 是否默认选中 #1#
	for (auto& MenuInfo : ValidMenuInfos)
	{
		if (!MenuInfo.bHidden && MenuInfo.bIsEnable && MenuInfo.bSelectable && MenuInfo.bIsSelected)
		{
			SelectMenu(MenuInfo.MenuTag);
		}
	}*/
}

void UScreenWidgetManager::DestroyMenu(FGameplayTag InMenuTag)
{
	/*DestroyMenu(GameMenu->GetDirectChildMenuTags(InMenuTag));*/
}

void UScreenWidgetManager::DestroyMenu(TArray<FGameplayTag> InMenuTags)
{
	/*const auto OnMenuInactived = FOnWidgetActiveStateChanged::CreateLambda([this](UUserWidgetBase* InWidget)
		{
			const UMenuStyle* MenuStyle = Cast<UMenuStyle>(InWidget);
			if (IsValid(MenuStyle))
			{
				FMenuContainerInfo MenuContainerInfo;
				GameMenu->GetMenuContainerInfo(MenuStyle->GetMenuTag(), MenuContainerInfo);

				FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuContainerInfo);
				MenuGenerateInfo->ClearupGarbageMenuStyle();

				if (!MenuGenerateInfo->GetIsValid())
					bClearupMenuGenerateInfos = true;

				if (IsValid(MenuGenerateInfo->MenuContainer))
				{
					InactiveWidget(MenuGenerateInfo->MenuContainer);
				}
			}
		}
	);

	for (const auto& MenuTag : InMenuTags)
	{
		FMenuContainerInfo MenuContainerInfo;
		GameMenu->GetMenuContainerInfo(MenuTag, MenuContainerInfo);

		if (FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuContainerInfo))
		{
			UMenuStyle* MenuStyle = MenuGenerateInfo->GetMenuStyle(MenuTag);
			if (IsValid(MenuStyle))
			{
				MenuGenerateInfo->MarkMenuStyleAsGarbage(MenuStyle);
				InactiveWidget(MenuStyle, OnMenuInactived);
			}
		}
	}*/
}

FReply UScreenWidgetManager::OnMenuResponseStateChanged(UInteractableWidgetBase* InteractableWidget, const bool TargetEventState)
{
	/*if (UMenuStyle* TargetMenuStyle = Cast<UMenuStyle>(InteractableWidget))
	{
		const FMenuInfo MenuInfo = TargetMenuStyle->GetMenuInfo();
		DPRINT(Log, TEXT("MenuInfo : %s,Seletion : %d"), *MenuInfo.MenuMainName.ToString(), TargetEventState)

		FMenuContainerInfo MenuContainerInfo;
		GameMenu->GetMenuContainerInfo(MenuInfo.MenuTag, MenuContainerInfo);

		if (const FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuContainerInfo))
		{
			if (!MenuGenerateInfo->MenuContainer->bIsManagedByGroup)
			{
				return FReply::Unhandled();
			}

			TargetMenuSelection.FindOrAdd(TargetMenuStyle, TargetEventState);

			/* 查找该菜单的子菜单信息 #1#
			TArray<FMenuGenerateInfo*> ChildMenuGenerateInfos;
			for (auto& MenuTag : GameMenu->GetDirectChildMenuTags(TargetMenuStyle->GetMenuTag()))
			{
				FMenuContainerInfo ChildMenuContainerInfo;
				GameMenu->GetMenuContainerInfo(MenuTag, ChildMenuContainerInfo);

				if (FMenuGenerateInfo* ChildMenuGenerateInfo = MenuGenerateInfos.FindByKey(ChildMenuContainerInfo))
				{
					ChildMenuGenerateInfos.AddUnique(ChildMenuGenerateInfo);
				}
			}

			/* 取消选中子菜单 #1#
			for (const auto& ChildMenuGenerateInfo : ChildMenuGenerateInfos)
			{
				ChildMenuGenerateInfo->MenuContainer->CommonButtonGroup->SetSelectionRequired(false);
				ChildMenuGenerateInfo->MenuContainer->CommonButtonGroup->DeselectAll();
			}

			return FReply::Handled();
		}
	}*/

	return FReply::Unhandled();
}

void UScreenWidgetManager::HandleMenuResponseStateChanged()
{
	/*TArray<UMenuStyle*> MenuStyles;
	TargetMenuSelection.GetKeys(MenuStyles);

	/* 在每次菜单事件完成之后，移除子菜单或生成子菜单，如果存在的话 #1#
	if (ProcessingMenuIndex > 0)
	{
		const UMenuStyle* PreviousMenuStyle = MenuStyles[ProcessingMenuIndex - 1];
		const bool PreviousEventState = TargetMenuSelection.FindRef(PreviousMenuStyle);

		if (PreviousEventState)
			GenerateMenu(PreviousMenuStyle->GetMenuTag());
		else
			DestroyMenu(PreviousMenuStyle->GetMenuTag());

		OnMenuSelectionChanged.Broadcast(PreviousMenuStyle->GetMenuTag(), PreviousEventState);
		BPDelegate_OnMenuSelectionChanged.Broadcast(PreviousMenuStyle->GetMenuTag(), PreviousEventState);
	}

	/* 执行当前菜单的事件 #1#
	if (MenuStyles.IsValidIndex(ProcessingMenuIndex))
	{
		UMenuStyle* TargetMenuStyle = MenuStyles[ProcessingMenuIndex];

		FMenuContainerInfo MenuContainerInfo;
		GameMenu->GetMenuContainerInfo(TargetMenuStyle->GetMenuTag(), MenuContainerInfo);

		FMenuGenerateInfo* MenuGenerateInfo = MenuGenerateInfos.FindByKey(MenuContainerInfo);
		const bool TargetEventState = TargetMenuSelection.FindRef(TargetMenuStyle);

		/* 标记当前激活的菜单 #1#
		if (TargetEventState)
			MenuGenerateInfo->ActivedMenuStyle = TargetMenuStyle;
		else
			MenuGenerateInfo->ActivedMenuStyle = nullptr;

		/* 执行菜单事件 #1#
		if (!TargetMenuStyle->GetResponseEvents(TargetEventState).IsEmpty())
		{
			if (UProcedureProxy* ProcedureProxy = TargetMenuStyle->HandleButtonResponseEvent(TargetMenuStyle->GetResponseEvents(TargetEventState), TargetEventState, FSimpleDelegate::CreateUObject(this, &UScreenWidgetManager::HandleMenuResponseStateChanged)))
			{
				ProcessingMenuIndex++;
				return;
			}
		}

		/* 没有菜单事件 #1#
		ProcessingMenuIndex++;
		HandleMenuResponseStateChanged();
	}
	/* 所有菜单都已经触发 #1#
	else
	{
		// for (const auto& MenuStyle : GetMenuStyles())
		// {
		// 	MenuStyle->CommonButton->SetIsInteractionEnabled(true);
		// }

		/* 当所有的事件都已退出，且存在WaitingGameMenu时，表明当前正在切换一个菜单数据，销毁并创建新的菜单数据 #1#
		if (bSwitchingGameMenu)
		{
			bSwitchingGameMenu = false;

			DestroyMenu(GameMenu->GetRootMenuTag());

			GameMenu = WaitingGameMenu;
			WaitingGameMenu = nullptr;

			if (IsValid(GameMenu))
			{
				GenerateMenu(GameMenu->GetRootMenuTag());
			}
		}

		TargetMenuSelection.Reset();
		bProcessingMenuSelection = false;
		ProcessingMenuIndex = 0;
	}*/
}

#undef LOCTEXT_NAMESPACE
