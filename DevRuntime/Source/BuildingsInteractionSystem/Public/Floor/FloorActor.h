// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CommonActor.h"
#include "Interface/FloorBodyInteractionInterface.h"
#include "Procedure/ProcedureInterface.h"
#include "FloorActor.generated.h"

class UFloorBodyComponent;

/**
 * 
 */
UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API AFloorActor : public ACommonActor, public IProcedureInterface, public IFloorBodyInteractionInterface
{
	GENERATED_BODY()

public:
	AFloorActor();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	int32 GetFloor() const { return Floor; }
	void SetFloor(int32 InFloor) { Floor = InFloor; }

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IFloorBodyInteractionInterface */
protected:
	virtual void HandleBeginCursorOverBody_Implementation(UFloorBodyComponent* BodyComponent) override;
	virtual void HandleEndCursorOverBody_Implementation(UFloorBodyComponent* BodyComponent) override;
	virtual void HandleBodyClicked_Implementation(UFloorBodyComponent* BodyComponent) override;

	/* AFloorActor */
public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UFloorBodyComponent* FloorBodyComponent = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(ClampMin = 0))
	int32 Floor = 0;
};
