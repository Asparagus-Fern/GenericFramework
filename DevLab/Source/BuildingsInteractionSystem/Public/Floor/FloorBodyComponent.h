// Copyright ChenTaiye 2025. All Rights Reserved.

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

public:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UStaticMesh>> BodyStaticMeshes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced)
	TArray<UStaticMeshComponent*> BodyComponents;

public:
	DECLARE_EVENT_OneParam(UFloorBodyComponent, FFloorBodyEvent, UFloorBodyComponent*)

	static FFloorBodyEvent OnBeginCursorOverBody;
	static FFloorBodyEvent OnEndCursorOverBody;
	static FFloorBodyEvent OnBodyClicked;
	
public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Floor Body Component")
	void RefreshFloor();
#endif
	
	UFUNCTION(BlueprintCallable, DisplayName="RefreshBody")
	void Refresh();

	UFUNCTION(BlueprintPure)
	void GetBodyBoundingBox(FVector& BoundingBoxMin, FVector& BoundingBoxMax);

	UFUNCTION(BlueprintCallable)
	void AddBodyMouseDelegate();

	UFUNCTION(BlueprintCallable)
	void RemoveBodyMouseDelegate();
	
private:
	UFUNCTION()
	void HandleBeginCursorOverInternal(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleEndCursorOverInternal(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleOnClickedInternal(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
