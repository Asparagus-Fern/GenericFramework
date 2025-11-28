// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PropertyCollectionAsset.generated.h"

class UPropertyCollectionViewModel;

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UPropertyCollectionAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TObjectPtr<UPropertyCollectionViewModel> PropertyCollectionViewModel = nullptr;
};
