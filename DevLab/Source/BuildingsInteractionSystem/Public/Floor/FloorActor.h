// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/FloorBodyInteractionInterface.h"
#include "Interface/ProcedureInterface.h"
#include "FloorActor.generated.h"

class ABuildingActor;
class UFloorBodyComponent;

/**
 * 
 */
UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API AFloorActor : public AActor, public IProcedureInterface, public IFloorBodyInteractionInterface
{
	GENERATED_BODY()

public:
	AFloorActor();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	int32 GetFloor() const { return Floor; }
	void SetFloor(int32 InFloor) { Floor = InFloor; }

	ABuildingActor* GetOwnerBuilding();
	void SetOwnerBuilding(ABuildingActor* InBuildingActor);

	/* IProcedureInterface */
public:
	virtual void OnActived_Implementation() override;
	virtual void OnInactived_Implementation() override;

	/* IFloorBodyInteractionInterface */
protected:
	virtual void HandleBeginCursorOverBody_Implementation(UFloorBodyComponent* BodyComponent) override;
	virtual void HandleEndCursorOverBody_Implementation(UFloorBodyComponent* BodyComponent) override;
	virtual void HandleBodyClicked_Implementation(UFloorBodyComponent* BodyComponent) override;
	virtual void HandleFloorSelectionChanged_Implementation(bool bIsSelected) override;

	/* AFloorActor */
public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UFloorBodyComponent* FloorBodyComponent = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<ABuildingActor> OwnerBuilding = nullptr;

	UPROPERTY(BlueprintReadOnly)
	int32 Floor = 0;

public:
	UFUNCTION(BlueprintPure)
	bool GetIsFloorSelected() const;
};
