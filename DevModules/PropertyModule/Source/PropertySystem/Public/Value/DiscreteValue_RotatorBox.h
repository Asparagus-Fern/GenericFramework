// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "DiscreteValueBase.h"
#include "DiscreteValue_RotatorBox.generated.h"

class UGenericRotatorBox;
class UDiscreteValuesViewModel;
class UGenericButton;
class UTextBlock;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UDiscreteValue_RotatorBox : public UDiscreteValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void OnRotatedWithDirection(int32 Value, ERotatorDirection RotatorDir);

protected:
	virtual void OnDiscreteValueAdded_Implementation(UDiscreteValueViewModel* Item) override;
	virtual void OnDiscreteValueRemoved_Implementation(UDiscreteValueViewModel* Item) override;
	virtual void OnDiscreteValueChanged_Implementation() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericRotatorBox> GenericRotator_PropertyValue;
};
