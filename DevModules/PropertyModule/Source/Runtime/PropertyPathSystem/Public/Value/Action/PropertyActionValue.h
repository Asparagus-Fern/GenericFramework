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
UCLASS(MinimalAPI)
class UPropertyActionValue : public UPropertyEntity
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	PROPERTYPATHSYSTEM_API FText GetActionText() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void SetActionText(FText InActionText);

	PROPERTYPATHSYSTEM_API void SetAction(const FOnExecutePropertyAction& InAction);
	PROPERTYPATHSYSTEM_API void SetAction(TFunction<void(UPropertyEntity*)> InAction);

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API void SetDynamicAction(FOnExecuteDynamicPropertyAction InAction);

	UFUNCTION(BlueprintCallable)
	PROPERTYPATHSYSTEM_API virtual void ExecuteAction();

protected:
	/* 事件名 */
	FText ActionText;

	/* 事件 */
	FOnExecutePropertyAction Action;
};
