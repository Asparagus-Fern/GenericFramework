// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "CommonInputComponent.generated.h"

UCLASS()
class PLAYERINPUTUTILITIES_API UCommonInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UCommonInputComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
