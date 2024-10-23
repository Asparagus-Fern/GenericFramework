// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneType.h"
#include "Manager/CoreManager.h"
#include "SceneManager.generated.h"

class ACompassActor;

/**
 * 
 */
UCLASS()
class WORLDUTILITIES_API USceneManager : public UCoreManager
{
	GENERATED_BODY()

public:
	USceneManager(const FObjectInitializer& ObjectInitializer);
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Tick(float DeltaTime) override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	TArray<AActor*> FindActors(const FFindActorHandle& FindActorHandle, bool bUpdate = false);
	float GetPlayerPointToNorthAngle(int32 PlayerIndex) const;

protected:
	UPROPERTY(Transient)
	TArray<FFoundActorHandle> FoundActorHandles;

	UPROPERTY(Transient)
	ACompassActor* CompassActor = nullptr;
};
