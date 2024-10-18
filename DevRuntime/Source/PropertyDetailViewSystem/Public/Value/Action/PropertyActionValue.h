// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/PropertyEntity.h"
#include "PropertyActionValue.generated.h"

DECLARE_DELEGATE_OneParam(FOnExecutePropertyAction, UPropertyEntity*)

/**
 * 事件类型的属性
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyActionValue : public UPropertyEntity
{
	GENERATED_BODY()

public:
	FText GetActionText() const;
	void SetActionText(FText InActionText);

	void SetAction(const FOnExecutePropertyAction& InAction);
	void SetAction(TFunction<void(UPropertyEntity*)> InAction);

	virtual void ExecuteAction();

protected:
	/* 事件名 */
	FText ActionText;

	/* 事件 */
	FOnExecutePropertyAction Action;
};
