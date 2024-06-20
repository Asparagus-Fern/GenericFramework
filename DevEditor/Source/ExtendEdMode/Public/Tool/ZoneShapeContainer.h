// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZoneShapeContainer.generated.h"

UCLASS()
class EXTENDEDMODE_API AZoneShapeContainer : public AActor
{
	GENERATED_BODY()

public:
	AZoneShapeContainer();

protected:
	UPROPERTY(Category = Zone, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UZoneShapeComponent> ZoneShapeComponent;

public:
	UFUNCTION(BlueprintPure)
	UZoneShapeComponent* GetZoneShapeComponent() { return ZoneShapeComponent; }
};
