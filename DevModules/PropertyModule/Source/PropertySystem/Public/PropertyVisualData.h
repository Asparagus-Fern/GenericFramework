// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PropertyVisualData.generated.h"

class UPropertyViewModel;
class UPropertyValueBase;
class UPropertyViewModel;

/**
 * 
 */
UCLASS(BlueprintType)
class PROPERTYSYSTEM_API UPropertyVisualData : public UDataAsset
{
	GENERATED_BODY()

public:
	TSubclassOf<UPropertyValueBase> GatherListItemForProperty(const UPropertyViewModel* InPropertyViewModel) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TSubclassOf<UPropertyViewModel>, TSubclassOf<UPropertyValueBase>> PropertyValueWidgetForClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FName, TSubclassOf<UPropertyValueBase>> PropertyValueWidgetForName;
};
