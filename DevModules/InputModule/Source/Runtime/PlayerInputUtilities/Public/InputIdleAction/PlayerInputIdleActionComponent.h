// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "PlayerInputIdleActionComponent.generated.h"

class UPlayerInputIdleAction;
class UPlayerInputManager;
class UInputAction;

/**
 * 
 */
UENUM(BlueprintType)
enum class EIdleActionMethod : uint8
{
	/* All Action Will be Refresh */
	All,

	/* Only a Random One Action Will Actived To Refresh */
	Random,

	/* Refresh Action In Sequence */
	Sequence
};

/**
 * 
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UPlayerInputIdleActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerInputIdleActionComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION()
	void HandleRefreshInputIdleAction(const FInputActionInstance& Value);

public:
	UFUNCTION(BlueprintCallable)
	PLAYERINPUTUTILITIES_API void ResetInputIdleAction();

	UFUNCTION(BlueprintPure)
	PLAYERINPUTUTILITIES_API APlayerController* GetOwnerPlayerController() const;

	UFUNCTION(BlueprintPure)
	PLAYERINPUTUTILITIES_API UEnhancedInputComponent* GetOwnerEnhancedInputComponent() const;

protected:
	/* The Key To Refresh Action.Default Is AnyKey. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> RefreshInputIdleAction = nullptr;

	/* Method When Refresh Action. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EIdleActionMethod RefreshMethod = EIdleActionMethod::All;

	/* Exclude Keys When Checking Whether To Refresh. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSet<FKey> ExcludeKeysWhenRefresh;

	/* Actions Need To Handle. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TArray<UPlayerInputIdleAction*> PlayerInputIdleActions;

private:
	int32 CurrentActionIndex = -1;
};
