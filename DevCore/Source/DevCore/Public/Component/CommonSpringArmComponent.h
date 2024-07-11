// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "CommonSpringArmComponent.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpringArmInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVCORE_API ISpringArmInterface
{
	GENERATED_BODY()

public:
};

UCLASS(ClassGroup=(Camera), meta=(BlueprintSpawnableComponent))
class DEVCORE_API UCommonSpringArmComponent : public USpringArmComponent, public ISpringArmInterface
{
	GENERATED_BODY()

public:
	UCommonSpringArmComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring Arm")
	float ArmZoomSpeedRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring Arm")
	float MinArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring Arm")
	float MaxArmLength = 5000000.f;

public:
	UFUNCTION(BlueprintCallable)
	void AddTargetArmLength(float InValue);

	UFUNCTION(BlueprintCallable)
	void SetTargetArmLength(float InValue);

protected:
	float DesiredArmLength = 0.f;
	void UpdateTargetArmLength(float DeltaTime);
};
