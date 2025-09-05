// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PropertyListItemAsset.generated.h"

class UPropertyListItemObject;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyListItemAsset : public UDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	UFUNCTION(CallInEditor)
	PROPERTYSYSTEM_API void Generate();
#endif

protected:
	PROPERTYSYSTEM_API virtual void GeneratePropertyListItemObjects(TArray<UPropertyListItemObject*>& Result);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<UPropertyListItemObject>> PropertyListItemObjects;
};
