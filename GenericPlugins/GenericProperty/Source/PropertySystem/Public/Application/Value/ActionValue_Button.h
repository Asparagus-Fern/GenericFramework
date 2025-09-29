// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMG/PropertyValue/PropertyActionValueBase.h"
#include "ActionValue_Button.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UActionValue_Button : public UPropertyActionValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

protected:
	UFUNCTION()
	void HandleOnButtonClicked();
	
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnActionTextChanged(const FText& InActionText);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnActionExecute();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_PropertyValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_PropertyValue;
};
