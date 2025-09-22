// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "PropertyVisualData.generated.h"

class UPropertyListItemOption;
class UPropertyViewModel;
class UPropertyValueBase;

/**
 * 
 */
UCLASS(BlueprintType)
class PROPERTYSYSTEM_API UPropertyVisualData : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual TSubclassOf<UPropertyValueBase> GatherPropertyValueWidgetClass(const UPropertyViewModel* InPropertyViewModel) const;
	virtual TMap<FGameplayTag, TSubclassOf<UPropertyListItemOption>> GatherPropertyOptionClasses(const UPropertyViewModel* InPropertyViewModel) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TSubclassOf<UPropertyViewModel>, TSubclassOf<UPropertyValueBase>> PropertyValueWidgetForClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FName, TSubclassOf<UPropertyValueBase>> PropertyValueWidgetForName;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="Property.Option"))
	TMap<FGameplayTag, TSubclassOf<UPropertyListItemOption>> PropertyListItemOptionForClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FName, TSubclassOf<UPropertyValueBase>> PropertyListItemOptionForName;
};
