// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PropertyListViewModel.generated.h"

class UPropertyList;
class UPropertyProxy;

/**
 * 
 */
UCLASS(EditInlineNew)
class PROPERTYSYSTEM_API UPropertyListViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText PropertyCategory;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPropertyList> PropertyListClass = nullptr;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPropertyProxy> PropertyProxyClass = nullptr;
};
