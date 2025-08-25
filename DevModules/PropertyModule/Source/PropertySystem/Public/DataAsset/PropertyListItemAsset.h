// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PropertyListItemAsset.generated.h"

class UPropertyListItemObject;

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyListItemAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<UPropertyListItemObject>> PropertyListItemObjects;
};
