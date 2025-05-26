// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ListEntry/PropertyListEntry_Scalar.h"
#include "PropertyListEntry_ScalarSlider.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROPERTYPATHSYSTEM_API UPropertyListEntry_ScalarSlider : public UPropertyListEntry_Scalar
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;
	virtual void Refresh() override;

	UFUNCTION()
	void HandleSliderValueChanged(float Value);

	UFUNCTION()
	void HandleSliderCaptureEnded();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USlider> Slider_PropertyValue;
};
