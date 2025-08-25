// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "UMG/PropertyValue/PropertyDiscreteValueBase.h"
#include "DiscreteValue_RotatorBox.generated.h"

class UGenericRotatorBox;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UDiscreteValue_RotatorBox : public UPropertyDiscreteValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

protected:
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

private:
	UFUNCTION()
	void OnRotatedWithDirection(int32 Value, ERotatorDirection RotatorDir);

	FDelegateHandle OnAllowWrapChangedHandle;
	void HandleOnAllowWrapChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId);

protected:
	PROPERTYSYSTEM_API virtual void OnPropertyValueAdded_Implementation(USinglePropertyValueViewModel* ViewModel) override;
	PROPERTYSYSTEM_API virtual void OnPropertyValueRemoved_Implementation(USinglePropertyValueViewModel* ViewModel) override;
	PROPERTYSYSTEM_API virtual void OnSelectedValueIndexChanged_Implementation(USinglePropertyValueViewModel* ViewModel) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericRotatorBox> GenericRotator_PropertyValue;
};
