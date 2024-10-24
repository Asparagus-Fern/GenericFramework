// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Pawn/PawnType.h"
#include "DSpringArmComponent.generated.h"

UCLASS(ClassGroup=(DevPlugin), meta=(BlueprintSpawnableComponent))
class DEVCORE_API UDSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	UDSpringArmComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSpringArmLimit SpringArmLimit;

public:
	UFUNCTION(BlueprintCallable)
	void AddTargetArmLength(float InValue);

	UFUNCTION(BlueprintCallable)
	void SetTargetArmLength(float InValue);

protected:
	float DesiredArmLength = 0.f;
	void UpdateTargetArmLength(float DeltaTime);
};
