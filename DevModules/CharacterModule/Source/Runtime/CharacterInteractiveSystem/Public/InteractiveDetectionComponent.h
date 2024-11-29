// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Procedure/ProcedureInterface.h"
#include "InteractiveDetectionComponent.generated.h"

/**
 * 提供角色范围内交互检测的能力
 */
UCLASS(ClassGroup=(DevPlugin), meta=(BlueprintSpawnableComponent))
class CHARACTERINTERACTIVESYSTEM_API UInteractiveDetectionComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UInteractiveDetectionComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UFUNCTION()
	void HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
