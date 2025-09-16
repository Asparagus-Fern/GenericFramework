// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/PropertyViewModel.h"
#include "ActionPropertyValueViewModel.generated.h"

DECLARE_DELEGATE_OneParam(FOnActionPropertyExecute, class UActionPropertyValueViewModel*);


/**
 * Event Type Property
 */
UCLASS()
class PROPERTYSYSTEM_API UActionPropertyValueViewModel : public UPropertyViewModel
{
	GENERATED_BODY()

public:
	void ExecuteAction(EPropertyChangedReason ChangedReason);

	void SetAction(const FOnActionPropertyExecute& InEvent);
	void SetAction(TFunction<void(UActionPropertyValueViewModel*)> InEvent);

	UFUNCTION(FieldNotify, BlueprintPure)
	const FText& GetActionText() const;

	UFUNCTION(BlueprintCallable)
	void SetActionText(const FText& InActionText);

private:
	FOnActionPropertyExecute OnActionExecuteEvent;

public:
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetActionText", BlueprintSetter="SetActionText")
	FText ActionText;
};
