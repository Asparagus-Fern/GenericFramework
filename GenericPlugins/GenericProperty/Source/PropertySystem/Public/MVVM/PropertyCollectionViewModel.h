// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PropertyCollectionViewModel.generated.h"

class UPropertyListViewModel;

/**
 * 
 */
UCLASS(EditInlineNew, MinimalAPI)
class UPropertyCollectionViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<TObjectPtr<UPropertyListViewModel>> PropertyListViewModels;
};
