// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnManager.h"

#include "Kismet/GameplayStatics.h"
#include "Pawn/DevPawn.h"

#define LOCTEXT_NAMESPACE "UPawnManager"

UPawnManager::UPawnManager()
{
}

FText UPawnManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Pawn Manager");
}

void UPawnManager::NativeOnActived()
{
	Super::NativeOnActived();

	// for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	// {
	// 	if (const APlayerController* PlayerController = Iterator->Get())
	// 	{
	// 		if (PlayerController->GetPawn()->GetClass()->ImplementsInterface(UPawnInterface::StaticClass()))
	// 		{
	// 			CurrentPossessPawn.Add(PlayerController->GetLocalPlayer()->GetLocalPlayerIndex(), Cast<IPawnInterface>(PlayerController->GetPawn())->GetPawnTag());
	// 		}
	// 	}
	// }
}

void UPawnManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	PawnMapping.Reset();
	// LastPossessPawn.Reset();
	// CurrentPossessPawn.Reset();
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
			// if (CurrentPossessPawn.Contains(PC->GetLocalPlayer()->GetLocalPlayerIndex()))
			// {
			// 	LastPossessPawn.Add(PC->GetLocalPlayer()->GetLocalPlayerIndex(), CurrentPossessPawn.FindRef(PC->GetLocalPlayer()->GetLocalPlayerIndex()));
			// }
			// CurrentPossessPawn.Add(PC->GetLocalPlayer()->GetLocalPlayerIndex(), PawnInterface->GetPawnTag());

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
