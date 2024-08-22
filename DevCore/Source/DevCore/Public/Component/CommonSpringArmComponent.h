// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "CommonSpringArmComponent.generated.h"

UCLASS(ClassGroup=(Camera), meta=(BlueprintSpawnableComponent))
class DEVCORE_API UCommonSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	UCommonSpringArmComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring Arm")
	float ArmZoomSpeedRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring Arm", meta=(ClampMin = 0.f, UIMin = 0.f))
	float MinArmLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring Arm")
	float MaxArmLength = 500000000.f;

public:
	UFUNCTION(BlueprintCallable)
	void AddTargetArmLength(float InValue);

	UFUNCTION(BlueprintCallable)
	void SetTargetArmLength(float InValue);

protected:
	float DesiredArmLength = 0.f;
	void UpdateTargetArmLength(float DeltaTime);
};
