// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "FloorMarkPointComponent.generated.h"


UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API UFloorMarkPointComponent : public USceneComponent, public IProcedureBaseInterface
{
	GENERATED_BODY()

public:
	UFloorMarkPointComponent();
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnRefresh() override;

	/* UFloorMarkPointComponent */
public:
	DECLARE_EVENT_OneParam(UFloorMarkPointComponent, FOnFloorMarkPointRefresh, UFloorMarkPointComponent*)

	static FOnFloorMarkPointRefresh OnFloorMarkPointRefresh;

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<UFloorMarkPointComponent*> MarkPointComponents;
};
