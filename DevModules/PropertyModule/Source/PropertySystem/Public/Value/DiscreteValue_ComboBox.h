// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DiscreteValueBase.h"
#include "DiscreteValue_ComboBox.generated.h"

class UComboBoxString;

/**
 * 
 */
UCLASS(Abstract)
class UDiscreteValue_ComboBox : public UDiscreteValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

protected:
	virtual void OnDiscreteValueAdded_Implementation(UDiscreteValueViewModel* Item) override;
	virtual void OnDiscreteValueRemoved_Implementation(UDiscreteValueViewModel* Item) override;
	virtual void OnDiscreteValueChanged_Implementation() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UComboBoxString> ComboBox_PropertyValue;
};
