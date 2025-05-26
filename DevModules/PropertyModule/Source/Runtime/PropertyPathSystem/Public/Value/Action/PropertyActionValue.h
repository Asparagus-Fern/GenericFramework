// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/PropertyEntity.h"
#include "PropertyActionValue.generated.h"

DECLARE_DELEGATE_OneParam(FOnExecutePropertyAction, UPropertyEntity*);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnExecuteDynamicPropertyAction, UPropertyEntity*, Property);

/**
 * 事件类型的属性
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyActionValue : public UPropertyEntity
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FText GetActionText() const;

	UFUNCTION(BlueprintCallable)
	void SetActionText(FText InActionText);

	void SetAction(const FOnExecutePropertyAction& InAction);
	void SetAction(TFunction<void(UPropertyEntity*)> InAction);

	UFUNCTION(BlueprintCallable)
	void SetDynamicAction(FOnExecuteDynamicPropertyAction InAction);

	UFUNCTION(BlueprintCallable)
	virtual void ExecuteAction();

protected:
	/* 事件名 */
	FText ActionText;

	/* 事件 */
	FOnExecutePropertyAction Action;
};
