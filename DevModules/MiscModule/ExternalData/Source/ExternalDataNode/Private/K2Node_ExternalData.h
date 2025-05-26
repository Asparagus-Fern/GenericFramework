// Copyright ChenTaiye 2025,. All Rights Reserved.

#pragma once

#include "K2Node_CallFunction.h"
#include "K2Node_ExternalData.generated.h"

class UEdGraphPin;
class FBlueprintActionDatabaseRegistrar;

/**
 * 
 */
UCLASS()
class UK2Node_ExternalData : public UK2Node_CallFunction
{
	GENERATED_BODY()
	
	//~ Begin UEdGraphNode Interface
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    //~ End UEdGraphNode Interface
	
	//~ Begin K2Node Interface
	virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;
	//~ End K2Node Interface
};
