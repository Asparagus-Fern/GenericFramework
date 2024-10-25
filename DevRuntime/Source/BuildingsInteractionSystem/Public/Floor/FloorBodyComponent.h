// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "FloorBodyComponent.generated.h"


class UFloorMarkPointComponent;
class UFloorStaticMeshComponent;

UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API UFloorBodyComponent : public USceneComponent, public IProcedureBaseInterface
{
	GENERATED_BODY()

public:
	UFloorBodyComponent();
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnRefresh() override;

	/* UFloorBodyComponent */
public:
	DECLARE_EVENT_OneParam(UFloorBodyComponent, FOnFloorBodyRefresh, UFloorBodyComponent*)

	static FOnFloorBodyRefresh OnFloorBodyRefresh;

public:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UStaticMesh>> BodyStaticMeshes;

	UPROPERTY(BlueprintReadOnly)
	TArray<UFloorStaticMeshComponent*> BodyComponents;
};
