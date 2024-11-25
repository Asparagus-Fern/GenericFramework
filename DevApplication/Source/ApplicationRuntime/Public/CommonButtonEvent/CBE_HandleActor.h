// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneType.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleActor.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCBE_HandleActor : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

	/* UCBE_HandleActor */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFindActorHandle FindActorHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UHandleActor*> HandleActors;
};
