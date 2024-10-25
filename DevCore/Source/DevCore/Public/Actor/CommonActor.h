// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommonActor.generated.h"

UCLASS()
class DEVCORE_API ACommonActor : public AActor
{
	GENERATED_BODY()

public:
	ACommonActor();
	virtual void BeginPlay() override;
	// virtual void Tick(float DeltaTime) override;
};
