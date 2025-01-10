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
#include "UserWidget/Base/UserWidgetBase.h"
#include "UserWidget/HUD/GameHUD.h"
#include "UserWidget/Menu/MenuContainer.h"
#include "UserWidget/Menu/MenuStyle.h"
#include "UWidget/Override/GameplayTagSlot.h"
#include "UserWidget/HUD/TemporaryHUD.h"

#define LOCTEXT_NAMESPACE "ScreenWidgetManager"

/* ==================== FWidgetAnimationTimerHandle ==================== */

FWidgetAnimationTimerHandle::FWidgetAnimationTimerHandle()
{
}

FWidgetAnimationTimerHandle::FWidgetAnimationTimerHandle(FTimerHandle InTimerHandle, UUserWidgetBase* InWidget, const FOnWidgetActiveStateChanged& Finish)
	: TimerHandle(InTimerHandle),
	  Widget(InWidget),
	  OnFinish(Finish)
{
}

bool FWidgetAnimationTimerHandle::operator==(const FWidgetAnimationTimerHandle& Other) const
{
	return Widget == Other.Widget;
}

bool FWidgetAnimationTimerHandle::operator==(const UUserWidgetBase* OtherWidget) const
{
	return Widget == OtherWidget;
}

/* ==================== UScreenWidgetManager ==================== */

UScreenWidgetManager::FScreenWidgetDelegate UScreenWidgetManager::PreHUDCreated;
UScreenWidgetManager::FHUDDelegate UScreenWidgetManager::OnHUDCreated;
UScreenWidgetManager::FScreenWidgetDelegate UScreenWidgetManager::PostHUDCreated;

UScreenWidgetManager::FScreenWidgetDelegate UScreenWidgetManager::PreHUDDestroyed;
UScreenWidgetManager::FHUDDelegate UScreenWidgetManager::OnHUDDestroyed;
UScreenWidgetManager::FScreenWidgetDelegate UScreenWidgetManager::PostHUDDestroyed;

UScreenWidgetManager::FSlotDelegate UScreenWidgetManager::OnSlotRegister;
UScreenWidgetManager::FSlotDelegate UScreenWidgetManager::OnSlotUnRegister;
UScreenWidgetManager::FScreenWidgetDelegate UScreenWidgetManager::OnSlslotClearup;

UScreenWidgetManager::FUserWidgetBaseDelegate UScreenWidgetManager::OnWidgetOpen;
UScreenWidgetManager::FUserWidgetBaseDelegate UScreenWidgetManager::OnWidgetClose;

UScreenWidgetManager::FOnHUDActiveStateChanged UScreenWidgetManager::OnHUDActiveStateChanged;

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

	UGameplayTagSlot::OnGameplayTagSlotBuild.AddUObject(this, &UScreenWidgetManager::RegisterSlot);
	UGameplayTagSlot::OnGameplayTagSlotDestroy.AddUObject(this, &UScreenWidgetManager::UnRegisterSlot);
}

void UScreenWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UGameplayTagSlot::OnGameplayTagSlotBuild.RemoveAll(this);
	UGameplayTagSlot::OnGameplayTagSlotDestroy.RemoveAll(this);
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

	if (UScreenWidgetManagerSetting::Get()->AutoCreateGameHUD)
	{
		PreHUDCreated.Broadcast();
		CreateGameHUDs(UScreenWidgetManagerSetting::Get()->GameHUDClasses, true);

		bIsHUDCreated = true;
		PostHUDCreated.Broadcast();
	}
}

void UScreenWidgetManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

void UScreenWidgetManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);

	/* 清除插槽 */
	ClearupSlots();

	/* 清除HUD */
	PreHUDDestroyed.Broadcast();
	ClearupGameHUDs();
	PostHUDDestroyed.Broadcast();
}

/* ==================== Game HUD ==================== */

void UScreenWidgetManager::CreateGameHUDs(TArray<TSoftClassPtr<UGameHUD>> InGameHUDClasses, const bool bAddToViewport)
{
	TArray<TSubclassOf<UGameHUD>> GameHUDClasses;
	for (const auto& GameHUD : GameHUDs)
	{
		GameHUDClasses.Add(GameHUD->GetClass());
	}

	for (const auto& GameHUDClass : InGameHUDClasses)
	{
		if (GameHUDClass.IsNull())
			continue;

		TSubclassOf<UGameHUD> LoadHUDClass = UBPFunctions_Object::LoadClass<UGameHUD>(GameHUDClass);

		/* 以创建的HUD不再创建 */
		if (GameHUDClasses.Contains(LoadHUDClass))
			continue;

		if (IsValid(LoadHUDClass))
		{
			UGameHUD* NewHUD = CreateWidget<UGameHUD>(GetWorld(), LoadHUDClass);
			CreateGameHUD(NewHUD, bAddToViewport);
		}
	}
}

void UScreenWidgetManager::CreateGameHUDs(TArray<TSubclassOf<UGameHUD>> InGameHUDClasses, const bool bAddToViewport)
{
	TArray<TSubclassOf<UGameHUD>> GameHUDClasses;
	for (const auto& GameHUD : GameHUDs)
	{
		GameHUDClasses.Add(GameHUD->GetClass());
	}

	for (const auto& GameHUDClass : InGameHUDClasses)
	{
		/* 以创建的HUD不再创建 */
		if (GameHUDClasses.Contains(GameHUDClass))
			continue;

		if (IsValid(GameHUDClass))
		{
			UGameHUD* NewHUD = CreateWidget<UGameHUD>(GetWorld(), GameHUDClass);
			CreateGameHUD(NewHUD, bAddToViewport);
		}
	}
}

void UScreenWidgetManager::CreateGameHUDs(TArray<UGameHUD*> InGameHUDs, const bool bAddToViewport)
{
	for (const auto& GameHUD : InGameHUDs)
	{
		CreateGameHUD(GameHUD, bAddToViewport);
	}
}

void UScreenWidgetManager::CreateGameHUD(UGameHUD* GameHUD, bool bAddToViewport)
{
	if (!GameHUDs.Contains(GameHUD))
	{
		GameHUDs.Add(GameHUD);
		ActiveWidget(GameHUD);

		if (bAddToViewport)
		{
			GameHUD->AddToViewport(GameHUD->ViewportZOrder);
		}

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

void UScreenWidgetManager::SetGameHUDActiveState(const bool IsActived)
{
	for (const auto& GameHUD : GameHUDs)
	{
		SetGameHUDActiveState(GameHUD, IsActived);
	}
}

void UScreenWidgetManager::SetGameHUDActiveState(UGameHUD* GameHUD, const bool IsActived)
{
	GameHUD->SetIsActived(IsActived);

	OnHUDActiveStateChanged.Broadcast(GameHUD, IsActived);
}

void UScreenWidgetManager::SetGameHUDActiveState(const FGameplayTag InTag, const bool IsActived)
{
	for (const auto& GameHUD : GetGameHUDByTag(InTag))
	{
		SetGameHUDActiveState(GameHUD, IsActived);
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
			CreateGameHUD(NewTemporaryHUD, false);
		}
		else
		{
			for (const auto& GameHUD : GameHUDs)
			{
				if (GameHUD.GetClass() == TemporaryHUDClass)
				{
					ActiveWidget(GameHUD);
				}
			}
		}
	}
}

void UScreenWidgetManager::RemoveTemporaryGameHUD(UUserWidgetBase* InWidget)
{
	/* 获取当前激活的所有Widget的临时HUD类集合，不包括InWidget */
	TArray<TSubclassOf<UGameHUD>> ActivedWidgetTemporaryHUDClasses;
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

	/* 需要移除的HUD */
	TArray<TSubclassOf<UGameHUD>> RemoveHUDClasses;
	for (auto& TemporaryHUDClass : InWidget->TemporaryHUDs)
	{
		/* 这个HUD正在被其他激活的Widget使用，不移除 */
		if (ActivedWidgetTemporaryHUDClasses.Contains(TemporaryHUDClass))
		{
			continue;
		}

		RemoveHUDClasses.Add(TemporaryHUDClass);
	}

	/* 移除HUD */
	for (auto& RemoveHUDClass : RemoveHUDClasses)
	{
		TArray<UGameHUD*> TempGameHUDs = GameHUDs;
		for (const auto& TempGameHUD : TempGameHUDs)
		{
			if (TempGameHUD->GetClass() == RemoveHUDClass)
			{
				RemoveGameHUD(TempGameHUD);
			}
		}
	}
}

/* ==================== UGameplayTagSlot ==================== */

void UScreenWidgetManager::RegisterSlot(UGameplayTagSlot* InSlot)
{
	if (!IsValid(InSlot) || !InSlot->SlotTag.IsValid() || Slots.Contains(InSlot))
	{
		DLOG(DLogUI, Warning, TEXT("Fail To RegisterSlot"))
		return;
	}

	Slots.Add(InSlot);
	InSlot->ClearChildren();

	OnSlotRegister.Broadcast(InSlot);
}

void UScreenWidgetManager::UnRegisterSlot(UGameplayTagSlot* InSlot)
{
	if (!IsValid(InSlot) || !InSlot->SlotTag.IsValid() || !Slots.Contains(InSlot))
	{
		DLOG(DLogUI, Warning, TEXT("Fail To UnRegisterSlot"))
		return;
	}

	OnSlotUnRegister.Broadcast(InSlot);
	Slots.Remove(InSlot);
}

void UScreenWidgetManager::ClearupSlots()
{
	TArray<UUserWidgetBase*> TempActivedWidgets = ActivedWidgets;
	for (const auto& TempActivedWidget : TempActivedWidgets)
	{
		InactiveWidget(TempActivedWidget, true);
	}

	OnSlslotClearup.Broadcast();
	Slots.Reset();
}

UGameplayTagSlot* UScreenWidgetManager::GetSlot(const FGameplayTag InSlotTag) const
{
	if (!InSlotTag.IsValid())
	{
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

UUserWidgetBase* UScreenWidgetManager::GetSlotWidget(const FGameplayTag InSlotTag)
{
	for (const auto& ActivedWidget : ActivedWidgets)
	{
		if (ActivedWidget->SlotTag == InSlotTag)
		{
			return ActivedWidget;
		}
	}

	return nullptr;
}

/* ==================== User Widget Base ==================== */

UUserWidgetBase* UScreenWidgetManager::GetContainerWidget(const FWidgetContainer& WidgetContainer)
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

UUserWidgetBase* UScreenWidgetManager::OpenUserWidget(const TSubclassOf<UUserWidgetBase> InWidgetClass, const FOnWidgetActiveStateChanged OnFinish)
{
	UUserWidgetBase* NewWidget = CreateWidget<UUserWidgetBase>(GetWorld(), InWidgetClass);
	if (OpenUserWidget(NewWidget, OnFinish))
	{
		return NewWidget;
	}
	else
	{
		return nullptr;
	}
}

bool UScreenWidgetManager::OpenUserWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget) || !InWidget->SlotTag.IsValid())
	{
		DLOG(DLogUI, Warning, TEXT("Fail To Open User Widget"))
		return false;
	}

	AddTemporaryGameHUD(InWidget);

	const UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag);
	if (IsValid(Slot))
	{
		/* 查找当前插槽是否已有其他Widget */
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
			InactiveWidget(RemoveWidget, FOnWidgetActiveStateChanged::CreateUObject(this, &UScreenWidgetManager::OnInactiveWidgetFinish, InWidget, OnFinish));
		}
		else
		{
			ActiveWidget(InWidget, OnFinish);
		}
	}

	return true;
}

bool UScreenWidgetManager::CloseUserWidget(const FGameplayTag InSlotTag, const FOnWidgetActiveStateChanged OnFinish, const bool MarkAsGarbage)
{
	if (!InSlotTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("SlotTag Is NULL"))
		return false;
	}

	bool bHasWidgetClose = false;;
	TArray<UUserWidgetBase*> TempActivedWidgets = ActivedWidgets;

	/* 查找是否有与插槽标签匹配的Widget */
	for (const auto& TempActivedWidget : TempActivedWidgets)
	{
		if (TempActivedWidget->SlotTag == InSlotTag)
		{
			if (!bHasWidgetClose)
			{
				bHasWidgetClose = true;
			}

			CloseUserWidget(TempActivedWidget, OnFinish, MarkAsGarbage);
		}
	}

	/* 当前没有指定插槽标签的Widget */
	if (!bHasWidgetClose)
	{
		OnFinish.ExecuteIfBound(nullptr);
	}

	return true;
}

bool UScreenWidgetManager::CloseUserWidget(UUserWidgetBase* InWidget, const FOnWidgetActiveStateChanged OnFinish, const bool MarkAsGarbage)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is NULL"))
		return false;
	}

	InactiveWidget(InWidget, OnFinish, MarkAsGarbage);
	return true;
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
	/* Widget进入 #1#
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

	/* Widget移出 #1#
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

	/* 如果有动画的话 #1#
	const FTimerHandle TimerHandle = PlayWidgetAnimation(MoveWidget, false, FTimerDelegate::CreateLambda(OnWidgetMoveOut));
	if (TimerHandle.IsValid())
	{
		return;
	}

	OnWidgetMoveOut();*/
}

void UScreenWidgetManager::ActiveWidget(UUserWidgetBase* InWidget, const FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is NULL"))
		OnFinish.ExecuteIfBound(InWidget);
		return;
	}

	if (ActivedWidgets.Contains(InWidget))
	{
		DLOG(DLogUI, Warning, TEXT("InWidget Is Already Actived"))
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
	OnWidgetOpen.Broadcast(InWidget);

	const FTimerHandle TimerHandle = PlayWidgetAnimation(InWidget, true, FTimerDelegate::CreateUObject(this, &UScreenWidgetManager::OnActiveAnimationPlayFinish, InWidget, OnFinish));
	if (TimerHandle.IsValid())
	{
		WidgetAnimationTimerHandles.Add(FWidgetAnimationTimerHandle(TimerHandle, InWidget, OnFinish));
		return;
	}

	OnActiveAnimationPlayFinish(InWidget, OnFinish);
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

void UScreenWidgetManager::InactiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish, bool MarkAsGarbage)
{
	if (!IsValid(InWidget) || !ActivedWidgets.Contains(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is NULL"))
		OnFinish.ExecuteIfBound(InWidget);
		return;
	}

	InWidget->NativeOnInactived();

	const FTimerHandle TimerHandle = PlayWidgetAnimation(InWidget, false, FTimerDelegate::CreateUObject(this, &UScreenWidgetManager::OnInactiveAnimationPlayFinish, InWidget, OnFinish));
	if (TimerHandle.IsValid())
	{
		WidgetAnimationTimerHandles.Add(FWidgetAnimationTimerHandle(TimerHandle, InWidget, OnFinish));
		return;
	}

	OnInactiveAnimationPlayFinish(InWidget, OnFinish);
}

void UScreenWidgetManager::InactiveWidget(UUserWidgetBase* InWidget, const bool bIsInstant, const FOnWidgetActiveStateChanged OnFinish, const bool MarkAsGarbage)
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

		if (MarkAsGarbage)
		{
			InWidget->MarkAsGarbage();
		}
	}
	else
	{
		InactiveWidget(InWidget, OnFinish, MarkAsGarbage);
	}
}

void UScreenWidgetManager::OnInactiveWidgetFinish(UUserWidgetBase* OldWidget, UUserWidgetBase* NewWidget, FOnWidgetActiveStateChanged OnFinish)
{
	ActiveWidget(NewWidget, OnFinish);
}

FTimerHandle UScreenWidgetManager::PlayWidgetAnimation(UUserWidgetBase* InWidget, const bool InIsActive, FTimerDelegate const& InDelegate)
{
	FTimerHandle TimerHandle;

	if (IWidgetAnimationInterface::Execute_HasActivationAnimation(InWidget, InIsActive))
	{
		IWidgetAnimationInterface::Execute_PlayActivationAnimation(InWidget, InIsActive);

		if (IWidgetAnimationInterface::Execute_GetActivationAnimationDuration(InWidget, InIsActive) > 0.f)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, InDelegate, IWidgetAnimationInterface::Execute_GetActivationAnimationDuration(InWidget, InIsActive), false);
		}
	}

	return TimerHandle;
}

void UScreenWidgetManager::OnActiveAnimationPlayFinish(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	TArray<FWidgetAnimationTimerHandle> TempHandles = WidgetAnimationTimerHandles;
	if (const FWidgetAnimationTimerHandle* Found = TempHandles.FindByKey(InWidget))
	{
		Found->OnFinish.ExecuteIfBound(Found->Widget);
		WidgetAnimationTimerHandles.Remove(*Found);
	}
	else
	{
		OnFinish.ExecuteIfBound(InWidget);
	}

	InWidget->NativeOnActived();
}

void UScreenWidgetManager::OnInactiveAnimationPlayFinish(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	RemoveTemporaryGameHUD(InWidget);

	if (InWidget->IsA<UGameHUD>())
	{
		RemoveGameHUD(Cast<UGameHUD>(InWidget));
	}

	TArray<FWidgetAnimationTimerHandle> TempHandles = WidgetAnimationTimerHandles;
	if (const FWidgetAnimationTimerHandle* Found = TempHandles.FindByKey(InWidget))
	{
		Found->OnFinish.ExecuteIfBound(Found->Widget);
		WidgetAnimationTimerHandles.Remove(*Found);
	}
	else
	{
		OnFinish.ExecuteIfBound(InWidget);
	}

	InWidget->RemoveFromParent();
	ActivedWidgets.Remove(InWidget);
	OnWidgetClose.Broadcast(InWidget);

	InWidget->NativeOnDestroy();
	InWidget->MarkAsGarbage();
}

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

FReply UScreenWidgetManager::OnMenuResponseStateChanged(UInteractableUserWidgetBase* InteractableWidget, const bool TargetEventState)
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
