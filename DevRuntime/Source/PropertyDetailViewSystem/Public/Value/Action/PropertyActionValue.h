// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/PropertyEntity.h"
#include "PropertyActionValue.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyActionValue : public UPropertyEntity
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnExecutePropertyAction, UPropertyEntity*)

public:
	FText GetActionText() const;
	void SetActionText(FText InActionText);

	void SetAction(const FOnExecutePropertyAction& InAction);
	void SetAction(TFunction<void(UPropertyEntity*)> InAction);

	virtual void ExecuteAction();
	
protected:
	FText ActionText;
	FOnExecutePropertyAction Action;
};
