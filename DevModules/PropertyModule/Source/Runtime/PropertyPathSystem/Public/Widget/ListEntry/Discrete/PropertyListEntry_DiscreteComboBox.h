// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ListEntry/PropertyListEntry_Discrete.h"
#include "PropertyListEntry_DiscreteComboBox.generated.h"

class UComboBoxString;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, MinimalAPI)
class UPropertyListEntry_DiscreteComboBox : public UPropertyListEntry_Discrete
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;
	virtual void Refresh() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UComboBoxString> ComboBox_PropertyValue;
};
