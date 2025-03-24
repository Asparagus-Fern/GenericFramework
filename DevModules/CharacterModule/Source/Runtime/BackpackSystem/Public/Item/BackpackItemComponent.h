// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackpackItemInterface.h"
#include "Components/ActorComponent.h"
#include "BackpackItemComponent.generated.h"


UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent))
class BACKPACKSYSTEM_API UBackpackItemComponent : public UActorComponent, public IBackpackItemInterface
{
	GENERATED_BODY()

public:
	UBackpackItemComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
};
