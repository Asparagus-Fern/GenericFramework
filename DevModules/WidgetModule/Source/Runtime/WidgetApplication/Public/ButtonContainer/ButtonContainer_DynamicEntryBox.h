// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericButtonContainer.h"
#include "ButtonContainer_DynamicEntryBox.generated.h"

class UGenericDynamicEntryBox;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UButtonContainer_DynamicEntryBox : public UGenericButtonContainer
{
	GENERATED_BODY()

protected:
	WIDGETAPPLICATION_API virtual void OnChildAdded_Implementation(UGenericWidget* InWidget, int32 NewChildrenCount) override;
	WIDGETAPPLICATION_API virtual void OnChildRemoved_Implementation(UGenericWidget* InWidget, int32 NewChildrenCount) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericDynamicEntryBox> GenericDynamicEntryBox_ButtonContainer;
};
