// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ListEntry/PropertyListEntry_Discrete.h"
#include "PropertyListEntry_DiscreteCheckBox.generated.h"

class UCheckBox;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, MinimalAPI)
class UPropertyListEntry_DiscreteCheckBox : public UPropertyListEntry_Discrete
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	virtual void NativeOnInitialized() override;
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;

	UFUNCTION()
	void OnCheckStateChanged(bool bIsCheck);

	virtual void Refresh() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCheckBox> CheckBox_PropertyValue;
};
