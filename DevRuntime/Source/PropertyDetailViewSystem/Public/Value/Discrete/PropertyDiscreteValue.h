// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value/PropertyValueBase.h"
#include "PropertyDiscreteValue.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValue : public UPropertyValueBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetDiscreteOptionByIndex(int32 Index) PURE_VIRTUAL(,);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetDiscreteOptionIndex() const PURE_VIRTUAL(, return INDEX_NONE;);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetDiscreteOptionDefaultIndex() const { return INDEX_NONE; }

	UFUNCTION(BlueprintCallable)
	virtual TArray<FText> GetDiscreteOptions() const PURE_VIRTUAL(, return TArray<FText>(););
};
