// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreInternalManager.h"
#include "GameFramework/Actor.h"
#include "ManagerActor.generated.h"

UCLASS(Abstract)
class DEVCORE_API AManagerActor : public AActor, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	AManagerActor();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* IManagerInterface */
public:
	virtual int32 GetManagerOrder() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetManagerOrder(int32 InManagerOrder);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ManagerOrder = 0;
};
