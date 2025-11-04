// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_Gameplay.h"

#include "Engine/EngineTypes.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/GameState.h"
#include "GameFramework/HUD.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
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

AGameSession* UBPFunctions_Gameplay::GetGameSessionByClass(const UObject* WorldContextObject, const TSubclassOf<AGameSession> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (AGameModeBase* GameModeBase = World->GetAuthGameMode<AGameModeBase>())
		{
			return GameModeBase->GameSession;
		}
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

APlayerController* UBPFunctions_Gameplay::GetPlayerControllerByIndex(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass, int32 InIndex)
{
	ensure(InClass);
	return UGameplayStatics::GetPlayerController(WorldContextObject, InIndex);
}

ULocalPlayer* UBPFunctions_Gameplay::GetLocalPlayerByIndex(const UObject* WorldContextObject, const TSubclassOf<ULocalPlayer> InClass, int32 InIndex)
{
	ensure(InClass);

	if (APlayerController* PC = GetPlayerControllerByIndex(WorldContextObject, APlayerController::StaticClass(), InIndex))
	{
		return PC->GetLocalPlayer();
	}

	return nullptr;
}

APlayerState* UBPFunctions_Gameplay::GetPlayerStateByIndex(const UObject* WorldContextObject, const TSubclassOf<APlayerState> InClass, int32 InIndex)
{
	ensure(InClass);

	if (const APlayerController* PC = GetPlayerControllerByIndex(WorldContextObject, APlayerController::StaticClass(), InIndex))
	{
		return PC->GetPlayerState<APlayerState>();
	}

	return nullptr;
}

AHUD* UBPFunctions_Gameplay::GetHUDByIndex(const UObject* WorldContextObject, const TSubclassOf<AHUD> InClass, int32 InIndex)
{
	ensure(InClass);

	if (const APlayerController* PC = GetPlayerControllerByIndex(WorldContextObject, APlayerController::StaticClass(), InIndex))
	{
		return PC->GetHUD<AHUD>();
	}

	return nullptr;
}

APawn* UBPFunctions_Gameplay::GetPawnByIndex(const UObject* WorldContextObject, const TSubclassOf<APawn> InClass, int32 InIndex)
{
	ensure(InClass);

	if (const APlayerController* PC = GetPlayerControllerByIndex(WorldContextObject, APlayerController::StaticClass(), InIndex))
	{
		return PC->GetPawn<APawn>();
	}

	return nullptr;
}

APlayerController* UBPFunctions_Gameplay::GetPlayerControllerByUniqueNetID(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass, const FUniqueNetIdRepl& InNetID)
{
	ensure(InClass);

	if (APlayerState* PlayerState = GetPlayerStateByUniqueNetID(WorldContextObject, APlayerState::StaticClass(), InNetID))
	{
		return PlayerState->GetPlayerController();
	}

	return nullptr;
}

ULocalPlayer* UBPFunctions_Gameplay::GetLocalPlayerByUniqueNetID(const UObject* WorldContextObject, const TSubclassOf<ULocalPlayer> InClass, const FUniqueNetIdRepl& InNetID)
{
	ensure(InClass);

	if (APlayerController* PC = GetPlayerControllerByUniqueNetID(WorldContextObject, APlayerController::StaticClass(), InNetID))
	{
		return PC->GetLocalPlayer();
	}

	return nullptr;
}

APlayerState* UBPFunctions_Gameplay::GetPlayerStateByUniqueNetID(const UObject* WorldContextObject, const TSubclassOf<APlayerState> InClass, const FUniqueNetIdRepl& InNetID)
{
	ensure(InClass);
	return UGameplayStatics::GetPlayerStateFromUniqueNetId(WorldContextObject, InNetID);
}

AHUD* UBPFunctions_Gameplay::GetHUDByUniqueNetID(const UObject* WorldContextObject, const TSubclassOf<AHUD> InClass, const FUniqueNetIdRepl& InNetID)
{
	ensure(InClass);

	if (APlayerController* PC = GetPlayerControllerByUniqueNetID(WorldContextObject, APlayerController::StaticClass(), InNetID))
	{
		return PC->GetHUD();
	}

	return nullptr;
}

APawn* UBPFunctions_Gameplay::GetPawnByUniqueNetID(const UObject* WorldContextObject, const TSubclassOf<APawn> InClass, const FUniqueNetIdRepl& InNetID)
{
	ensure(InClass);

	if (APlayerState* PlayerState = GetPlayerStateByUniqueNetID(WorldContextObject, APlayerState::StaticClass(), InNetID))
	{
		return PlayerState->GetPawn();
	}

	return nullptr;
}

bool UBPFunctions_Gameplay::GetPlayerID(const APlayerController* InPlayer, int32& Result)
{
	if (APlayerState* PlayerState = InPlayer->GetPlayerState<APlayerState>())
	{
		Result = PlayerState->GetPlayerId();
		return true;
	}
	return false;
}

bool UBPFunctions_Gameplay::GetPlayerIDByPlayerState(const APlayerState* InPlayerState, int32& Result)
{
	Result = InPlayerState->GetPlayerId();
	return true;
}

bool UBPFunctions_Gameplay::GetPlayerIDByPawn(const APawn* InPawn, int32& Result)
{
	if (APlayerState* PlayerState = InPawn->GetPlayerState<APlayerState>())
	{
		Result = PlayerState->GetPlayerId();
		return true;
	}
	return false;
}

bool UBPFunctions_Gameplay::GetPlayerUniqueNetID(const APlayerController* InPlayer, FUniqueNetIdRepl& Result)
{
	if (APlayerState* PlayerState = InPlayer->GetPlayerState<APlayerState>())
	{
		Result = PlayerState->GetUniqueId();
		return true;
	}
	return false;
}

bool UBPFunctions_Gameplay::GetPlayerUniqueNetIDByPlayerState(const APlayerState* InPlayerState, FUniqueNetIdRepl& Result)
{
	Result = InPlayerState->GetUniqueId();
	return true;
}

bool UBPFunctions_Gameplay::GetPlayerUniqueNetIDByPawn(const APawn* InPawn, FUniqueNetIdRepl& Result)
{
	if (APlayerState* PlayerState = InPawn->GetPlayerState())
	{
		Result = PlayerState->GetUniqueId();
		return true;
	}
	return false;
}

bool UBPFunctions_Gameplay::GetPlayerUniqueNetIDByPlayerIndex(const UObject* WorldContextObject, int32 InPlayerIndex, FUniqueNetIdRepl& Result)
{
	if (APlayerState* PlayerState = GetPlayerStateByIndex(WorldContextObject, APlayerState::StaticClass(), InPlayerIndex))
	{
		Result = PlayerState->GetUniqueId();
		return true;
	}
	return false;
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
