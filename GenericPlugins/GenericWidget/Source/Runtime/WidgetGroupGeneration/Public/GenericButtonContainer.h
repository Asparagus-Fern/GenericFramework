// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "GenericButtonContainer.generated.h"

class UGenericButtonGroup;
class UGenericButtonCollection;

/**
 * Determines How To Arrange Child Buttons
 */
UCLASS(Abstract, MinimalAPI)
class UGenericButtonContainer : public UGenericWidget
{	
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API virtual UGenericButtonCollection* GetButtonCollection() const;
	WIDGETGROUPGENERATION_API virtual void SetButtonCollection(UGenericButtonCollection* InButtonCollection);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API virtual UGenericButtonGroup* GetButtonGroup() const;
	WIDGETGROUPGENERATION_API virtual void SetButtonGroup(UGenericButtonGroup* InButtonGroup);

private:
	UPROPERTY()
	TWeakObjectPtr<UGenericButtonCollection> ButtonCollection = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UGenericButtonGroup> ButtonGroup = nullptr;
};
