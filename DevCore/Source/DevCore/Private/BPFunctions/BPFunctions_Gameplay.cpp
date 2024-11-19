// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Gameplay.h"

#include "AIController.h"
#include "EngineUtils.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

UGameInstance* UBPFunctions_Gameplay::GetGameInstanceByClass(const UObject* WorldContextObject, const TSubclassOf<UGameInstance> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameInstance<UGameInstance>();
	}

	return nullptr;
}

AGameModeBase* UBPFunctions_Gameplay::GetGameModeByClass(const UObject* WorldContextObject, const TSubclassOf<AGameModeBase> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetAuthGameMode<AGameModeBase>();
	}

	return nullptr;
}

AGameStateBase* UBPFunctions_Gameplay::GetGameStateByClass(const UObject* WorldContextObject, const TSubclassOf<AGameStateBase> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameState<AGameStateBase>();
	}

	return nullptr;
}

AHUD* UBPFunctions_Gameplay::GetHUDByClass(const UObject* WorldContextObject, const TSubclassOf<AHUD> InClass)
{
	ensure(InClass);

	if (const APlayerController* PC = GetFirstPlayerControllerByClass(WorldContextObject, APlayerController::StaticClass()))
	{
		return PC->GetHUD<AHUD>();
	}

	return nullptr;
}

APawn* UBPFunctions_Gameplay::GetPawnByClass(const UObject* WorldContextObject, const TSubclassOf<APawn> InClass)
{
	ensure(InClass);

	if (const APlayerController* PC = GetFirstPlayerControllerByClass(WorldContextObject, APlayerController::StaticClass()))
	{
		return PC->GetPawn<APawn>();
	}

	return nullptr;
}

APlayerController* UBPFunctions_Gameplay::GetFirstPlayerControllerByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetFirstPlayerController<APlayerController>();
	}

	return nullptr;
}

APlayerController* UBPFunctions_Gameplay::GetPlayerControllerByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass, int32 InIndex)
{
	ensure(InClass);

	return UGameplayStatics::GetPlayerController(WorldContextObject, InIndex);
}

APlayerState* UBPFunctions_Gameplay::GetPlayerStateByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerState> InClass)
{
	ensure(InClass);

	if (const APlayerController* PC = GetFirstPlayerControllerByClass(WorldContextObject, APlayerController::StaticClass()))
	{
		return PC->GetPlayerState<APlayerState>();
	}

	return nullptr;
}

bool UBPFunctions_Gameplay::GetIsPlayerPossessPawn(const APawn* InPawn)
{
	return IsValid(Cast<APlayerController>(InPawn->GetController()));
}

bool UBPFunctions_Gameplay::GetIsAIPossessPawn(const APawn* InPawn)
{
	return IsValid(Cast<AAIController>(InPawn->GetController()));
}

void UBPFunctions_Gameplay::SetAllActorsVisibility(const UObject* WorldContextObject, const TSubclassOf<AActor> InClass, const bool bIsHiddenInGame)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		for (TActorIterator<AActor> It(World, InClass); It; ++It)
		{
			AActor* Actor = *It;
			if (IsValid(Actor))
			{
				Actor->SetActorHiddenInGame(bIsHiddenInGame);
			}
		}
	}
}

void UBPFunctions_Gameplay::SetAllActorsVisibilityWithInterface(const UObject* WorldContextObject, const TSubclassOf<UInterface> Interface, const bool bIsHiddenInGame)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (IsValid(Actor) && Actor->GetClass()->ImplementsInterface(Interface))
			{
				Actor->SetActorHiddenInGame(bIsHiddenInGame);
			}
		}
	}
}

void UBPFunctions_Gameplay::SetAllActorsVisibilityWithTag_Class(const UObject* WorldContextObject, const TSubclassOf<AActor> InClass, const FName InTag, const bool bIsHiddenInGame)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		for (TActorIterator<AActor> It(World, InClass); It; ++It)
		{
			AActor* Actor = *It;
			if (IsValid(Actor) && Actor->ActorHasTag(InTag))
			{
				Actor->SetActorHiddenInGame(bIsHiddenInGame);
			}
		}
	}
}

void UBPFunctions_Gameplay::SetAllActorsVisibilityWithTag_Interface(const UObject* WorldContextObject, const TSubclassOf<UInterface> Interface, const FName InTag, const bool bIsHiddenInGame)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (IsValid(Actor) && Actor->GetClass()->ImplementsInterface(Interface) && Actor->ActorHasTag(InTag))
			{
				Actor->SetActorHiddenInGame(bIsHiddenInGame);
			}
		}
	}
}

bool UBPFunctions_Gameplay::GetActorForwardHitResult(const AActor* InActor, FHitResult& HitResult, const ECollisionChannel TraceChannel)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(InActor))
	{
		const FVector Start = InActor->GetActorLocation();
		const FVector End = InActor->GetActorForwardVector() * UE_BIG_NUMBER + Start;
		return World->LineTraceSingleByChannel(HitResult, Start, End, TraceChannel);
	}

	return false;
}

bool UBPFunctions_Gameplay::GetActorRightHitResult(const AActor* InActor, FHitResult& HitResult, const ECollisionChannel TraceChannel)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(InActor))
	{
		const FVector Start = InActor->GetActorLocation();
		const FVector End = InActor->GetActorRightVector() * UE_BIG_NUMBER + Start;
		return World->LineTraceSingleByChannel(HitResult, Start, End, TraceChannel);
	}

	return false;
}

bool UBPFunctions_Gameplay::GetActorDownHitResult(const AActor* InActor, FHitResult& HitResult, const ECollisionChannel TraceChannel)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(InActor))
	{
		const FVector Start = InActor->GetActorLocation();
		const FVector End = FVector(0.f, 0.f, -1.f) * UE_BIG_NUMBER + Start;
		return World->LineTraceSingleByChannel(HitResult, Start, End, TraceChannel);
	}

	return false;
}

bool UBPFunctions_Gameplay::GetComponentForwardHitResult(const USceneComponent* InComponent, FHitResult& HitResult, const ECollisionChannel TraceChannel)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(InComponent))
	{
		const FVector Start = InComponent->GetComponentLocation();
		const FVector End = InComponent->GetForwardVector() * UE_BIG_NUMBER + Start;
		return World->LineTraceSingleByChannel(HitResult, Start, End, TraceChannel);
	}

	return false;
}

bool UBPFunctions_Gameplay::GetComponentRightHitResult(const USceneComponent* InComponent, FHitResult& HitResult, const ECollisionChannel TraceChannel)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(InComponent))
	{
		const FVector Start = InComponent->GetComponentLocation();
		const FVector End = InComponent->GetRightVector() * UE_BIG_NUMBER + Start;
		return World->LineTraceSingleByChannel(HitResult, Start, End, TraceChannel);
	}

	return false;
}

bool UBPFunctions_Gameplay::GetComponentDownHitResult(const USceneComponent* InComponent, FHitResult& HitResult, const ECollisionChannel TraceChannel)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(InComponent))
	{
		const FVector Start = InComponent->GetComponentLocation();
		const FVector End = FVector(0.f, 0.f, -1.f) * UE_BIG_NUMBER + Start;
		return World->LineTraceSingleByChannel(HitResult, Start, End, TraceChannel);
	}

	return false;
}
