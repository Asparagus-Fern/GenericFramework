// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVM/PropertyViewModel.h"
#include "ActionPropertyValueViewModel.generated.h"

DECLARE_DELEGATE_OneParam(FOnActionPropertyExecute, class UActionPropertyValueViewModel*);


/**
 * Event Type Property
 */
UCLASS(MinimalAPI)
class UActionPropertyValueViewModel : public UPropertyViewModel
{
	GENERATED_BODY()

protected:
	PROPERTYSYSTEM_API virtual bool CanApply() override { return false; }
	PROPERTYSYSTEM_API virtual bool CanReset() override { return false; }

public:
	PROPERTYSYSTEM_API void ExecuteAction(EPropertyChangedReason ChangedReason);

	PROPERTYSYSTEM_API void SetAction(const FOnActionPropertyExecute& InEvent);
	PROPERTYSYSTEM_API void SetAction(TFunction<void(UActionPropertyValueViewModel*)> InEvent);

	UFUNCTION(FieldNotify, BlueprintPure)
	PROPERTYSYSTEM_API const FText& GetActionText() const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetActionText(const FText& InActionText);

private:
	FOnActionPropertyExecute OnActionExecuteEvent;

public:
	UPROPERTY(FieldNotify, EditAnywhere, Getter, Setter, BlueprintGetter="GetActionText", BlueprintSetter="SetActionText")
	FText ActionText;
};
