// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyValueWarning.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyValueWarning : public UGenericWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	const FText& GetWarningText() const;

	UFUNCTION(BlueprintCallable)
	void SetWarningText(const FText& InText);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnWarningTextChanged(const FText& InText);

protected:
	UPROPERTY(EditAnywhere)
	FText WarningText;
};
