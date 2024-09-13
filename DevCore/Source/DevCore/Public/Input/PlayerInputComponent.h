// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputType.h"
#include "Components/ActorComponent.h"
#include "PlayerInputComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(DevPlugin), meta=(BlueprintSpawnableComponent))
class DEVCORE_API UPlayerInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerInputComponent();
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnhanceInputMappingContext> EnhanceInputMappingContexts;

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetupPlayerInput(UInputComponent* PlayerInputComponent);

	UFUNCTION(BlueprintNativeEvent)
	void RemovePlayerInput(UInputComponent* PlayerInputComponent);
};
