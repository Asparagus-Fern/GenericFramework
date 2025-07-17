// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackpackInterface.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"


UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UBackpackComponent : public UActorComponent, public IBackpackInterface
{
	GENERATED_BODY()

public:
	UBackpackComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
};
