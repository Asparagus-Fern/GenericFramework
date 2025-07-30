// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyScreen.generated.h"

class UPropertyPanel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyScreen : public UGenericWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyPanel> Panel_Property;
};
