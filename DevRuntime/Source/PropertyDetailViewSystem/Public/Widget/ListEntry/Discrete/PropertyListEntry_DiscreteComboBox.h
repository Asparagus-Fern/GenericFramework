// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ListEntry/PropertyListEntry_Discrete.h"
#include "PropertyListEntry_DiscreteComboBox.generated.h"

class UComboBoxString;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyListEntry_DiscreteComboBox : public UPropertyListEntry_Discrete
{
	GENERATED_BODY()

public:
	virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;
	
protected:
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;
	virtual void Refresh() override;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UComboBoxString> ComboBox_PropertyValue;
};
