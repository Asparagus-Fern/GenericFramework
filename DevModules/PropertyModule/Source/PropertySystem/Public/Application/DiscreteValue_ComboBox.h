// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMG/PropertyValue/PropertyDiscreteValueBase.h"
#include "DiscreteValue_ComboBox.generated.h"

class UComboBoxString;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UDiscreteValue_ComboBox : public UPropertyDiscreteValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

protected:
	PROPERTYSYSTEM_API virtual void OnPropertyValueAdded_Implementation(USinglePropertyValueViewModel* ViewModel) override;
	PROPERTYSYSTEM_API virtual void OnPropertyValueRemoved_Implementation(USinglePropertyValueViewModel* ViewModel) override;
	PROPERTYSYSTEM_API virtual void OnSelectedValueIndexChanged_Implementation(int32 SelectedValueIndex) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UComboBoxString> ComboBox_PropertyValue;
};
