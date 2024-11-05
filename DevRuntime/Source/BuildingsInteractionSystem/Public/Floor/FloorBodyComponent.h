// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FloorBodyComponent.generated.h"


class UFloorStaticMeshComponent;

UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API UFloorBodyComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UFloorBodyComponent();
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UStaticMesh>> BodyStaticMeshes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced)
	TArray<UStaticMeshComponent*> BodyComponents;

public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Floor Body Component")
	void RefreshFloor();
#endif
	
	UFUNCTION(BlueprintCallable, DisplayName="RefreshBody")
	void Refresh();

	UFUNCTION(BlueprintPure)
	void GetBodyBoundingBox(FVector& BoundingBoxMin, FVector& BoundingBoxMax);

private:
	UFUNCTION()
	void HandleBeginCursorOverInternal(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleEndCursorOverInternal(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleOnClickedInternal(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
