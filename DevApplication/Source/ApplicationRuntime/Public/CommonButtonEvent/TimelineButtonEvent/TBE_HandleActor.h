// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneType.h"
#include "TimelineButtonEvent.h"
#include "TBE_HandleActor.generated.h"

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UTBE_HandleActor : public UTimelineButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

	/* ITimelineButtonEventInterface */
public:
	virtual void HandleTimelineUpdate_Implementation(float Alpha) override;
	virtual void HandleTimelineFinish_Implementation(float Alpha) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFindActorHandle FindActorHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UHandleActor*> HandleActors;

private:
	UPROPERTY(Transient)
	TArray<AActor*> Actors;
};
