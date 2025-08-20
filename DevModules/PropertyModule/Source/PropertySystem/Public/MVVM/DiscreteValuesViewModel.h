// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyValueViewModel.h"
#include "DiscreteValuesViewModel.generated.h"

class UDiscreteValueViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDiscreteValueAdded, UDiscreteValueViewModel*, Item);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDiscreteValueRemoved, UDiscreteValueViewModel*, Item);

/**
 * 
 */
UCLASS(MinimalAPI)
class UDiscreteValuesViewModel : public UPropertyValueViewModel
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void AddValue(FName InValueName, FText InValueDisplayName, int32 Index = -1);
	PROPERTYSYSTEM_API void AddValueWithProperty(const FProperty* InProperty, int32 Index = -1);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void RemoveValue(FName InValueName);
	PROPERTYSYSTEM_API void RemoveValueWithProperty(const FProperty* InProperty);

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UDiscreteValueViewModel* GetCurrentValue();

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UDiscreteValueViewModel* GetDefaultValue();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetValueByIndex(int32 InValueIndex);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetValueByName(FName InValueName);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetValueByItem(UDiscreteValueViewModel* InValue);

public:
	UPROPERTY(BlueprintAssignable)
	FOnDiscreteValueAdded OnDiscreteValueAddedEvent;

	UPROPERTY(BlueprintAssignable)
	FOnDiscreteValueRemoved OnDiscreteValueRemovedEvent;

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bAllowWrap = false;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 DefaultValueIndex = 0;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 CurrentValueIndex = 0;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UDiscreteValueViewModel>> Values;
};
