// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Procedure/ProcedureInterface.h"
#include "BuildingActor.generated.h"

class AFloorActor;

UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API ABuildingActor : public AActor, public IProcedureInterface
{
	GENERATED_BODY()

public:
	ABuildingActor();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	/* IProcedureInterface */
protected:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	virtual void OnRefresh_Implementation() override;
	virtual void OnActived_Implementation() override;
	virtual void OnInactived_Implementation() override;

	/* ABuildingActor */
public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AFloorActor>> FloorClasses;

	UPROPERTY(Transient)
	TArray<UChildActorComponent*> FloorComponents;

public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor)
	void RefreshBuilding();
#endif

	UFUNCTION(BlueprintCallable)
	static void DispatchBuildingActived(ABuildingActor* InBuildingActor) { OnBuildingActived.Broadcast(InBuildingActor); }

protected:
	DECLARE_EVENT_OneParam(ABuildingActor, FBuildingEvent, ABuildingActor*);

	static FBuildingEvent OnBuildingActived;

	void HandleBuildingActived(ABuildingActor* InBuildingActor);
};
