// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputMappingContext.h"
#include "Components/ActorComponent.h"
#include "PlayerInputConfigurationComponent.generated.h"

class UPlayerInputManager;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnhancedInputMappingContext
{
	GENERATED_BODY()

public:
	bool operator==(const FEnhancedInputMappingContext& Other) const { return InputMappingContext == Other.InputMappingContext; }
	bool operator==(const UInputMappingContext* Other) const { return InputMappingContext == Other; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Priority = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FModifyContextOptions ModifyContextOptions;
};

/**
 * 
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent))
class PLAYERINPUTUTILITIES_API UPlayerInputConfigurationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerInputConfigurationComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetupPlayerInput();

	UFUNCTION(BlueprintNativeEvent)
	void RemovePlayerInput();

protected:
	UPlayerInputManager* GetOwnerPlayerInputManager() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnhancedInputMappingContext> EnhancedInputMappingContexts;
};
