// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/StateInterface.h"
#include "BuildingActor.generated.h"

class UFloorBodyComponent;
class AFloorActor;

UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API ABuildingActor : public AActor, public IStateInterface
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

	virtual void HandleOnRefresh_Implementation() override;
	virtual void HandleOnActived_Implementation() override;
	virtual void HandleOnInactived_Implementation() override;

	/* ABuildingActor */
public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AFloorActor>> FloorClasses;

	UPROPERTY(Transient)
	TArray<UChildActorComponent*> FloorComponents;

	UPROPERTY(Transient)
	UChildActorComponent* SelectedFloorComponent = nullptr;

public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor)
	void RefreshBuilding();
#endif

	/* 广播所有BuildingActor，指定的的BuildingActor被选中 */
	UFUNCTION(BlueprintCallable)
	static void DispatchBuildingActived(ABuildingActor* InBuildingActor) { OnBuildingActiveStateChanged.Broadcast(InBuildingActor); }

protected:
	DECLARE_EVENT_OneParam(ABuildingActor, FBuildingEvent, ABuildingActor*);

	static FBuildingEvent OnBuildingActiveStateChanged;

	/* 当有BuildingActor激活状态改变时 */
	void HandleBuildingActiveStateChanged(ABuildingActor* InBuildingActor);

	/* 当有某一层被点击时 */
	void HandleBodyClicked(UFloorBodyComponent* BodyComponent);

public:
	/* 选中某一层 */
	UFUNCTION(BlueprintCallable)
	void SelectFloor(int32 InFloor);

	/* 取消选中当前层 */
	UFUNCTION(BlueprintCallable)
	void DeselectFloor();

	/* 获取指定楼层的ChildActorComponent */
	UFUNCTION(BlueprintPure)
	UChildActorComponent* GetFloorComponent(int32 InFloor);

	/* 获取指定楼层ChildActorComponent的FloorActor */
	UFUNCTION(BlueprintPure)
	AFloorActor* GetFloorActor(int32 InFloor);

	/* 后去当前选中楼层的ChildActorComponent */
	UFUNCTION(BlueprintPure)
	UChildActorComponent* GetSelectedFloorComponent() const;

	/* 后去当前选中楼层的FloorActor */
	UFUNCTION(BlueprintPure)
	AFloorActor* GetSelectedFloorActor();

	/* 获取当前选中楼层 */
	UFUNCTION(BlueprintPure)
	int32 GetSelectedFloor();

protected:
	void SelectFloorInternal(UChildActorComponent* InFloorComponent);
	void SetFloorActorSelection(const UChildActorComponent* FloorComponent, const bool bIsSelected);
};
