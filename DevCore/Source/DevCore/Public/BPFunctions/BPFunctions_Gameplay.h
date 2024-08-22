// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Gameplay.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Gameplay : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static UGameInstance* GetGameInstanceByClass(const UObject* WorldContextObject, const TSubclassOf<UGameInstance> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static AGameModeBase* GetGameModeByClass(const UObject* WorldContextObject, const TSubclassOf<AGameModeBase> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static AGameStateBase* GetGameStateByClass(const UObject* WorldContextObject, const TSubclassOf<AGameStateBase> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static AHUD* GetHUDByClass(const UObject* WorldContextObject, const TSubclassOf<AHUD> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static APawn* GetPawnByClass(const UObject* WorldContextObject, const TSubclassOf<APawn> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static APlayerController* GetFirstPlayerControllerByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static APlayerController* GetPlayerControllerByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass, int32 InIndex);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static APlayerState* GetPlayerStateByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerState> InClass);

	/* Actor */
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void SetAllActorsVisibility(const UObject* WorldContextObject, TSubclassOf<AActor> InClass, bool bIsHiddenInGame);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void SetAllActorsVisibilityWithInterface(const UObject* WorldContextObject, TSubclassOf<UInterface> Interface, bool bIsHiddenInGame);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), DisplayName="SetAllActorsVisibilityWithTag(Class)")
	static void SetAllActorsVisibilityWithTag_Class(const UObject* WorldContextObject, TSubclassOf<AActor> InClass, FName InTag, bool bIsHiddenInGame);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), DisplayName="SetAllActorsVisibilityWithTag(Interface)")
	static void SetAllActorsVisibilityWithTag_Interface(const UObject* WorldContextObject, TSubclassOf<UInterface> Interface, FName InTag, bool bIsHiddenInGame);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2))
	static bool GetActorForwardHitResult(const AActor* InActor, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2))
	static bool GetActorRightHitResult(const AActor* InActor, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2))
	static bool GetActorDownHitResult(const AActor* InActor, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	/* Component */
public:
	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2))
	static bool GetComponentForwardHitResult(const USceneComponent* InComponent, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2))
	static bool GetComponentRightHitResult(const USceneComponent* InComponent, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);

	UFUNCTION(BlueprintPure, meta=(AdvancedDisplay = 2))
	static bool GetComponentDownHitResult(const USceneComponent* InComponent, FHitResult& HitResult, ECollisionChannel TraceChannel = ECC_Camera);
};
