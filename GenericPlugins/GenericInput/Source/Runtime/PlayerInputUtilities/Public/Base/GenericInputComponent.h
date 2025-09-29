// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GenericInputComponent.generated.h"

UCLASS()
class PLAYERINPUTUTILITIES_API UGenericInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UGenericInputComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
