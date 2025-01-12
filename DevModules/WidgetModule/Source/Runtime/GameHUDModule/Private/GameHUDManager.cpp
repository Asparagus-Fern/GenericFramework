// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUDManager.h"

#include "GameHUDSetting.h"
#include "BPFunctions/BPFunctions_Object.h"
#include "HUD/GameHUD.h"
#include "UWidget/Override/GameplayTagSlot.h"

bool UGameHUDManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGameHUDManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UGameplayTagSlot::OnBuildGameplayTagSlot.AddUObject(this, &UGameHUDManager::RegisterSlot);
	UGameplayTagSlot::OnRemoveGameplayTagSlot.AddUObject(this, &UGameHUDManager::UnRegisterSlot);
}

void UGameHUDManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UGameplayTagSlot::OnBuildGameplayTagSlot.RemoveAll(this);
	UGameplayTagSlot::OnRemoveGameplayTagSlot.RemoveAll(this);
}

bool UGameHUDManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGameHUDManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);

	if (UGameHUDSetting::Get()->AutoCreateGameHUD)
	{
		CreateGameHUDs(UGameHUDSetting::Get()->GameHUDClasses, true);
	}
}

void UGameHUDManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);
}

/* ==================== UGameplayTagSlot ==================== */

void UGameHUDManager::RegisterSlot(UGameplayTagSlot* InSlot)
{
	if (!IsValid(InSlot))
	{
		DLOG(DLogUI, Error, TEXT("Invalid GameplayTagSlot"))
		return;
	}

	if (!InSlot->SlotTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("Invalid GameplayTag"))
		return;
	}

	if (Slots.Contains(InSlot))
	{
		DLOG(DLogUI, Warning, TEXT("GameplayTag : %s Is Already Register"), *InSlot->SlotTag.ToString())
		return;
	}

	InSlot->ClearChildren();
	Slots.Add(InSlot);

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnSlotRegister, BPDelegate_OnSlotRegister, InSlot)
}

void UGameHUDManager::UnRegisterSlot(UGameplayTagSlot* InSlot)
{
	if (!IsValid(InSlot))
	{
		DLOG(DLogUI, Error, TEXT("Invalid GameplayTagSlot"))
		return;
	}

	if (!InSlot->SlotTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("Invalid GameplayTag"))
		return;
	}

	if (!Slots.Contains(InSlot))
	{
		DLOG(DLogUI, Warning, TEXT("GameplayTag : %s Is Already UnRegister"), *InSlot->SlotTag.ToString())
		return;
	}

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnSlotUnRegister, BPDelegate_OnSlotUnRegister, InSlot)
	Slots.Remove(InSlot);
}

UGameplayTagSlot* UGameHUDManager::GetSlot(const FGameplayTag InSlotTag) const
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

/* ==================== Game HUD ==================== */

void UGameHUDManager::CreateGameHUDs(TArray<TSoftClassPtr<UGameHUD>> InGameHUDClasses, const bool bAddToViewport)
{
	TArray<TSubclassOf<UGameHUD>> GameHUDClasses = UBPFunctions_Object::LoadClass<UGameHUD>(InGameHUDClasses);
	TArray<TSubclassOf<UGameHUD>> CurrentGameHUDClasses = GetCurrentGameHUDClasses();

	for (const auto& CurrentGameHUDClass : CurrentGameHUDClasses)
	{
		if (GameHUDClasses.Contains(CurrentGameHUDClass))
		{
			GameHUDClasses.Remove(CurrentGameHUDClass);
		}
	}

	CreateGameHUDs(GameHUDClasses, bAddToViewport);
}

void UGameHUDManager::CreateGameHUDs(TArray<TSubclassOf<UGameHUD>> InGameHUDClasses, const bool bAddToViewport)
{
	TArray<TSubclassOf<UGameHUD>> CurrentGameHUDClasses = GetCurrentGameHUDClasses();
	TArray<UGameHUD*> GameHUDs;

	for (const auto& GameHUDClass : InGameHUDClasses)
	{
		if (!IsValid(GameHUDClass))
		{
			DLOG(DLogUI, Error, TEXT("GameHUDClass Is Invalid"))
			continue;
		}

		/* 以创建的HUD不再创建 */
		if (CurrentGameHUDClasses.Contains(GameHUDClass))
		{
			DLOG(DLogUI, Error, TEXT("GameHUDClass Is Already Created"))
			continue;
		}

		GameHUDs.Add(CreateWidget<UGameHUD>(GetWorld(), GameHUDClass));
	}

	CreateGameHUDs(GameHUDs, bAddToViewport);
}

void UGameHUDManager::CreateGameHUDs(TArray<UGameHUD*> InGameHUDs, const bool bAddToViewport)
{
	for (const auto& GameHUD : InGameHUDs)
	{
		CreateGameHUD(GameHUD, bAddToViewport);
	}
}

void UGameHUDManager::CreateGameHUD(UGameHUD* InGameHUD, bool bAddToViewport)
{
	if (!IsValid(InGameHUD))
	{
		DLOG(DLogUI, Error, TEXT("InGameHUD Is Invalid"))
		return;;
	}

	if (!GameHUDs.Contains(InGameHUD))
	{
		GameHUDs.Add(InGameHUD);

		if (bAddToViewport)
		{
			InGameHUD->AddToViewport(InGameHUD->ViewportZOrder);
		}

		BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDCreated, BPDelegate_OnHUDCreated, InGameHUD);
	}
}

void UGameHUDManager::RemoveGameHUDs(TArray<UGameHUD*> InGameHUDs)
{
	for (auto& InGameHUD : InGameHUDs)
	{
		RemoveGameHUD(InGameHUD);
	}
}

void UGameHUDManager::RemoveGameHUD(UGameHUD* InGameHUD)
{
	if (GameHUDs.Contains(InGameHUD))
	{
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDDestroyed, BPDelegate_OnHUDDestroyed, InGameHUD);
		GameHUDs.Remove(InGameHUD);
	}
}

void UGameHUDManager::RemoveGameHUDs(TArray<FGameplayTag> InHUDTags)
{
	for (auto& InHUDTag : InHUDTags)
	{
		RemoveGameHUD(InHUDTag);
	}
}

void UGameHUDManager::RemoveGameHUD(const FGameplayTag InHUDTag)
{
	if (TObjectPtr<UGameHUD>* Found = GameHUDs.FindByPredicate([InHUDTag](TObjectPtr<UGameHUD> InGameHUD)
		{
			return InGameHUD->HUDTag == InHUDTag;
		}
	))
	{
		RemoveGameHUD(*Found);
	}
}

void UGameHUDManager::ClearupGameHUDs()
{
	TArray<UGameHUD*> TempGameHUDs = GameHUDs;
	for (const auto& GameHUD : TempGameHUDs)
	{
		RemoveGameHUD(GameHUD);
	}
}

UGameHUD* UGameHUDManager::GetGameHUDByTag(const FGameplayTag InHUDTag)
{
	if (TObjectPtr<UGameHUD>* Found = GameHUDs.FindByPredicate([InHUDTag](TObjectPtr<UGameHUD> InGameHUD)
		{
			return InGameHUD->HUDTag == InHUDTag;
		}
	))
	{
		return *Found;
	}

	return nullptr;
}

TArray<UGameHUD*> UGameHUDManager::GetGameHUDsByTag(FGameplayTag InHUDTag)
{
	TArray<UGameHUD*> Result;
	for (auto& HUD : GameHUDs)
	{
		if (HUD->HUDTag.MatchesTag(InHUDTag))
		{
			Result.Add(HUD);
		}
	}
	return Result;
}

void UGameHUDManager::SetAllGameHUDActiveState(bool IsActived)
{
	for (const auto& GameHUD : GameHUDs)
	{
		SetGameHUDActiveState(GameHUD, IsActived);
	}
}

void UGameHUDManager::SetGameHUDActiveState(UGameHUD* InGameHUD, const bool IsActived) const
{
	if (!IsValid(InGameHUD))
	{
		DLOG(DLogUI, Error, TEXT("InGameHUD Is Invalid"))
		return;
	}

	InGameHUD->SetIsActived(IsActived);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDActiveStateChanged, BPDelegate_OnHUDActiveStateChanged, InGameHUD, IsActived);
}

void UGameHUDManager::SetGameHUDActiveState(FGameplayTag InTag, bool IsActived)
{
	if (!InTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("InTag Is Invalid"))
		return;
	}

	SetGameHUDActiveState(GetGameHUDByTag(InTag), IsActived);
}

void UGameHUDManager::AddTemporaryGameHUD(UUserWidgetBase* InWidget)
{
	TArray<TSubclassOf<UGameHUD>> GameHUDClasses = GetCurrentGameHUDClasses();

	/* 确保已经创建的HUD不会被二次创建 */
	for (auto& TemporaryHUDClass : InWidget->TemporaryHUDs)
	{
		if (!GameHUDClasses.Contains(TemporaryHUDClass))
		{
			UGameHUD* NewTemporaryHUD = CreateWidget<UGameHUD>(GetWorld(), TemporaryHUDClass);
			CreateGameHUD(NewTemporaryHUD, false);
		}
		// else
		// {
		// 	for (const auto& GameHUD : GameHUDs)
		// 	{
		// 		if (GameHUD.GetClass() == TemporaryHUDClass)
		// 		{
		// 			ActiveWidget(GameHUD);
		// 		}
		// 	}
		// }
	}
}

void UGameHUDManager::RemoveTemporaryGameHUD(UUserWidgetBase* InWidget)
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

TArray<TSubclassOf<UGameHUD>> UGameHUDManager::GetCurrentGameHUDClasses()
{
	TArray<TSubclassOf<UGameHUD>> GameHUDClasses;
	for (const auto& GameHUD : GameHUDs)
	{
		GameHUDClasses.Add(GameHUD->GetClass());
	}
	return GameHUDClasses;
}
