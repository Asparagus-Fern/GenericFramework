// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PropertyVisualData.generated.h"

class UPropertyListEntryBase;
class UPropertyEntity;

/**
 * 
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyVisualData : public UDataAsset
{
	GENERATED_BODY()

public:
	TSubclassOf<UPropertyListEntryBase> GetEntryForProperty(UPropertyEntity* InProperty);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = ListEntries, meta = (AllowAbstract))
	TMap<TSubclassOf<UPropertyEntity>, TSubclassOf<UPropertyListEntryBase>> EntryWidgetForClass;

	UPROPERTY(EditDefaultsOnly, Category = ListEntries, meta = (AllowAbstract))
	TMap<FName, TSubclassOf<UPropertyListEntryBase>> EntryWidgetForName;
};
