// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ListEntry/PropertyListEntry_Discrete.h"
#include "PropertyListEntry_DiscreteRotator.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROPERTYPATHSYSTEM_API UPropertyListEntry_DiscreteRotator : public UPropertyListEntry_Discrete
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;

	virtual void HandleRotatorChangedValue(int32 Value, bool bUserInitiated);
	virtual void HandleOptionIncrease();
	virtual void HandleOptionDecrease();

	virtual void Refresh() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonRotator> Rotator_PropertyValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Increase;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Decrease;
};
