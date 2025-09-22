// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "UMG/PropertyListItemOption.h"
#include "PropertyOptionReset.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyOptionReset : public UPropertyListItemOption
{
	GENERATED_BODY()

protected:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;
	PROPERTYSYSTEM_API virtual void NativeOnClicked() override;

protected:
	virtual void OnPropertyApply_Implementation(UPropertyViewModel* InViewModel) override;
	virtual void OnPropertyReset_Implementation(UPropertyViewModel* InViewModel) override;
	virtual void OnPropertyValueChanged_Implementation(UPropertyViewModel* InViewModel, EPropertyChangedReason ChangedReason) override;
};
