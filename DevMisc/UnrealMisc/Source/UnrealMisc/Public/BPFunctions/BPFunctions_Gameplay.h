// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Engine/GameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameState.h"
#include "GameFramework/HUD.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Gameplay.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMISC_API UBPFunctions_Gameplay : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* Gameplay */
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"), Category="Gameplay")
	static UGameInstance* GetGameInstanceByClass(const UObject* WorldContextObject, const TSubclassOf<UGameInstance> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"), Category="Gameplay")
	static AGameModeBase* GetGameModeByClass(const UObject* WorldContextObject, const TSubclassOf<AGameModeBase> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"), Category="Gameplay")
	static AGameStateBase* GetGameStateByClass(const UObject* WorldContextObject, const TSubclassOf<AGameStateBase> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"), Category="Gameplay")
	static AHUD* GetHUDByClass(const UObject* WorldContextObject, const TSubclassOf<AHUD> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"), Category="Gameplay")
	static APawn* GetPawnByClass(const UObject* WorldContextObject, const TSubclassOf<APawn> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"), Category="Gameplay")
	static APlayerController* GetFirstPlayerControllerByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"), Category="Gameplay")
	static APlayerController* GetPlayerControllerByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass, int32 InIndex);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"), Category="Gameplay")
	static APlayerState* GetPlayerStateByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerState> InClass);

	/* Pawn */
public:
	UFUNCTION(BlueprintPure, Category="Pawn")
	static bool GetIsPlayerPossessPawn(const APawn* InPawn);

	UFUNCTION(BlueprintPure, Category="Pawn")
	static bool GetIsAIPossessPawn(const APawn* InPawn);

	/* Actor */
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category="Actor")
	static void SetAllActorsVisibility(const UObject* WorldContextObject, TSubclassOf<AActor> InClass, bool bIsHiddenInGame);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category="Actor")
	static void SetAllActorsVisibilityWithInterface(const UObject* WorldContextObject, TSubclassOf<UInterface> Interface, bool bIsHiddenInGame);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), DisplayName="SetAllActorsVisibilityWithTag(Class)", Category="Actor")
	static void SetAllActorsVisibilityWithTag_Class(const UObject* WorldContextObject, TSubclassOf<AActor> InClass, FName InTag, bool bIsHiddenInGame);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), DisplayName="SetAllActorsVisibilityWithTag(Interface)", Category="Actor")
	static void SetAllActorsVisibilityWithTag_Interface(const UObject* WorldContextObject, TSubclassOf<UInterface> Interface, FName InTag, bool bIsHiddenInGame);

public:
	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2), Category="Actor")
	static bool GetActorForwardHitResult(const AActor* InActor, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2), Category="Actor")
	static bool GetActorRightHitResult(const AActor* InActor, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2), Category="Actor")
	static bool GetActorDownHitResult(const AActor* InActor, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	/* Component */
public:
	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2), Category="Component")
	static bool GetComponentForwardHitResult(const USceneComponent* InComponent, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2), Category="Component")
	static bool GetComponentRightHitResult(const USceneComponent* InComponent, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2), Category="Component")
	static bool GetComponentDownHitResult(const USceneComponent* InComponent, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);
};
