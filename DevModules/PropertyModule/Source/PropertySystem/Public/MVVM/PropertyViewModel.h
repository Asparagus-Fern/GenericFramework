// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PropertyViewModel.generated.h"

class UPropertyValueViewModel;

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UPropertyViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FName PropertyName = NAME_None;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Instanced)
	TObjectPtr<UPropertyValueViewModel> PropertyValue = nullptr;
};
