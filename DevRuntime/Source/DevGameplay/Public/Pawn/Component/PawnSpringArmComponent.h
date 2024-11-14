// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnSpringArmComponent.generated.h"

UCLASS(ClassGroup=(DevPlugin), meta=(BlueprintSpawnableComponent))
class DEVGAMEPLAY_API UPawnSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	UPawnSpringArmComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpringArmLag = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReassessmentSpringArmLength = 100.f;

public:
	UFUNCTION(BlueprintCallable)
	void AddTargetArmLength(float InValue);

	UFUNCTION(BlueprintCallable)
	void SetTargetArmLength(float InValue);

	UFUNCTION(BlueprintPure)
	bool GetIsReassessment(float InValue) const;

protected:
	float DesiredArmLength = 0.f;
	void UpdateTargetArmLength(float DeltaTime);
};
