// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FloorBodyComponent.generated.h"


class UFloorStaticMeshComponent;

UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API UFloorBodyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFloorBodyComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnRegister() override;

	/* UFloorBodyComponent */
public:
	DECLARE_EVENT_OneParam(UFloorBodyComponent, FOnFloorBodyRefresh, UFloorBodyComponent*)

	static FOnFloorBodyRefresh OnFloorBodyRefresh;

public:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UStaticMesh>> BodyStaticMeshes;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TArray<UStaticMeshComponent*> BodyComponents;

protected:
	UStaticMeshComponent* GetComponentByStaticMesh(TObjectPtr<UStaticMesh> StaticMesh);

	UFUNCTION()
	void HandleBeginCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleEndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleOnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
