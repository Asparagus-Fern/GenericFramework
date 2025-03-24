// Copyright ChenTaiye 2025. All Rights Reserved.

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
