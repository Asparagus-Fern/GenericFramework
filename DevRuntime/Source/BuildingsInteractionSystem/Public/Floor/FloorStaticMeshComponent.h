// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "FloorStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API UFloorStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Getter, BlueprintGetter="GetFloor")
	int32 Floor = 0;

public:
	UFUNCTION(BlueprintPure)
	int32 GetFloor() const;
	void SetFloor(int32 InFloor);
};
