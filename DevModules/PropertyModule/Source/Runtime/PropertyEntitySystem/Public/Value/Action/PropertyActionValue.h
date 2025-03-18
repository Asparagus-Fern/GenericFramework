// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/PropertyEntity.h"
#include "PropertyActionValue.generated.h"

DECLARE_DELEGATE_OneParam(FOnExecutePropertyAction, UPropertyEntity*)

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnExecutePropertyDynamicAction, UPropertyEntity*, InProperty);

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyActionValue : public UPropertyEntity
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FText GetActionText() const;

	UFUNCTION(BlueprintCallable)
	void SetActionText(FText InActionText);

	UFUNCTION(BlueprintCallable)
	virtual void ExecuteAction();

	void SetAction(const FOnExecutePropertyAction& InAction);
	void SetAction(TFunction<void(UPropertyEntity*)> InAction);

	UFUNCTION(BlueprintCallable)
	void SetDynamicAction(FOnExecutePropertyDynamicAction InDynamicAction);

protected:
	FText ActionText;

	FOnExecutePropertyAction Action;
	FOnExecutePropertyDynamicAction DynamicAction;
};
