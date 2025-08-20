// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Type/DebugType.h"
#include "UObject/Object.h"
#include "GenericObject.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class DEVCORE_API UGenericObject : public UObject
{
	GENERATED_BODY()

public:
	UGenericObject(const FObjectInitializer& ObjectInitializer);
	virtual UWorld* GetWorld() const override;
};
