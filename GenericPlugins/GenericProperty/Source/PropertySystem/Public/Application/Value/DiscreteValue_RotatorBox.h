// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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

private:
	UFUNCTION()
	void OnElementRotated(int32 InIndex, const FText& InText);

protected:
	PROPERTYSYSTEM_API virtual void OnAllowWrapChanged_Implementation(bool IsAllowWrap) override;
	PROPERTYSYSTEM_API virtual void OnPropertyValueAdded_Implementation(const FString& InName, UPropertyViewModel* InViewModel) override;
	PROPERTYSYSTEM_API virtual void OnPropertyValueRemoved_Implementation(const FString& InName, UPropertyViewModel* InViewModel) override;
	PROPERTYSYSTEM_API virtual void OnSelectedValueChanged_Implementation(const FString& SelectedValue) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericRotatorBox> GenericRotator_PropertyValue;
};
