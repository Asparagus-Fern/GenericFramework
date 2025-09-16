// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericButtonBuilder.h"
#include "GenericSettingBuilder.generated.h"

class UPropertyCollectionViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericSettingBuilder : public UGenericButtonBuilder
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TObjectPtr<UPropertyCollectionViewModel> PropertyCollectionViewModel = nullptr;
};
