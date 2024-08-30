// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnManager.h"

#include "Kismet/GameplayStatics.h"
#include "Pawn/DevPawn.h"
#include "Pawn/PawnManagerSetting.h"

#define LOCTEXT_NAMESPACE "UPawnManager"

bool UPawnManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UPawnManagerSetting::Get()->bEnableSubsystem;
}

void UPawnManager::NativeOnActived()
{
	Super::NativeOnActived();
}

void UPawnManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	PawnMapping.Reset();
}

void UPawnManager::RegisterPawn(IPawnInterface* InPawnInterface)
{
	if (InPawnInterface->GetPawnTag().IsValid() && !PawnMapping.Contains(InPawnInterface->GetPawnTag()))
	{
		PawnMapping.Add(InPawnInterface->GetPawnTag(), InPawnInterface);
	}
}

void UPawnManager::UnRegisterPawn(IPawnInterface* InPawnInterface)
{
	if (InPawnInterface->GetPawnTag().IsValid() && PawnMapping.Contains(InPawnInterface->GetPawnTag()))
	{
		PawnMapping.Remove(InPawnInterface->GetPawnTag());
	}
}

void UPawnManager::PossessPawn(const int32 PlayerIndex, const FGameplayTag InPawnTag)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex))
	{
		if (IPawnInterface* PawnInterface = PawnMapping.FindRef(InPawnTag))
		{
			PC->Possess(PawnInterface->GetPawn());
		}
	}
}

IPawnInterface* UPawnManager::GetPawnInterface(const FGameplayTag InPawnTag)
{
	if (PawnMapping.Contains(InPawnTag))
	{
		return PawnMapping.FindRef(InPawnTag);
	}
	return nullptr;
}

APawn* UPawnManager::GetPawn(const FGameplayTag InPawnTag)
{
	if (IPawnInterface* PawnInterface = GetPawnInterface(InPawnTag))
	{
		return PawnInterface->GetPawn();
	}
	return nullptr;
}

#undef LOCTEXT_NAMESPACE
