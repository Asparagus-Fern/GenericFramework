// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PickableDetectionComponent.generated.h"


UCLASS(ClassGroup=(DevPlugin), meta=(BlueprintSpawnableComponent))
class BACKPACKSYSTEM_API UPickableDetectionComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UPickableDetectionComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UFUNCTION()
	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);
	
};
