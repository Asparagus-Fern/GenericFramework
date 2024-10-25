// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CommonActor.h"
#include "CompassActor.generated.h"

class UTextRenderComponent;
class UArrowComponent;

UCLASS(NotBlueprintable, HideCategories=(Object,Collision,Physics,Networking,Input,LevelInstance,Cooking,LOD,HLOD,Replication))
class WORLDUTILITIES_API ACompassActor : public ACommonActor
{
	GENERATED_BODY()

public:
	ACompassActor();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	// virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY()
	UArrowComponent* ArrowComponentN = nullptr;

	UPROPERTY()
	UTextRenderComponent* TextRenderN = nullptr;

	UPROPERTY()
	UArrowComponent* ArrowComponentS = nullptr;

	UPROPERTY()
	UTextRenderComponent* TextRenderS = nullptr;

	UPROPERTY()
	UArrowComponent* ArrowComponentE = nullptr;

	UPROPERTY()
	UTextRenderComponent* TextRenderE = nullptr;

	UPROPERTY()
	UArrowComponent* ArrowComponentW = nullptr;

	UPROPERTY()
	UTextRenderComponent* TextRenderW = nullptr;

private:
	void SetupComponent(UArrowComponent*& InArrow, FName InArrowName, UTextRenderComponent*& InTextRender, FName InTextRenderName, float InArrowYaw = 0.f, FColor InArrowColor = FColor(255, 0, 0, 255), FString InText = TEXT("N"));

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = -180.f, UIMin= -180.f, ClampMax=180.f, UIMax=180.f))
	float Angle = 0.f;

public:
	UFUNCTION(BlueprintPure)
	FVector GetDirectionNorth() const;

	UFUNCTION(BlueprintPure)
	FVector GetDirectionEast() const;
};
