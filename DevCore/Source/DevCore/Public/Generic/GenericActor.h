// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericActor.generated.h"

UCLASS()
class DEVCORE_API AGenericActor : public AActor
{
	GENERATED_BODY()

public:
	AGenericActor();
	virtual void BeginPlay() override;
	// virtual void Tick(float DeltaTime) override;
};
