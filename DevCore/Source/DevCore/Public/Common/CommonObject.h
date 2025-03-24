// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "UObject/Object.h"
#include "CommonObject.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class DEVCORE_API UCommonObject : public UObject
{
	GENERATED_BODY()

public:
	UCommonObject(const FObjectInitializer& ObjectInitializer);
	virtual UWorld* GetWorld() const override;
};
