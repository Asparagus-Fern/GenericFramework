// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MVVMViewModelBase.h"
#include "PropertyListViewModel.generated.h"

class UPropertyDataSourceCollection;
class UPropertyList;

/**
 * 
 */
UCLASS(EditInlineNew, MinimalAPI)
class UPropertyListViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(Categories="Property.Proxy"))
	FGameplayTag PropertyProxyTag;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText PropertyCategory;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPropertyList> PropertyListClass = nullptr;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPropertyDataSourceCollection> PropertyDataSourceCollectionClass = nullptr;
};
