// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_CallFunction.h"
#include "K2Node_TrySetJsonField.generated.h"

/**
 * 
 */
UCLASS()
class GENERICJSONNODE_API UK2Node_TrySetJsonField : public UK2Node_CallFunction
{
	GENERATED_BODY()

public:
	UK2Node_TrySetJsonField();

	// //~ Begin UEdGraphNode Interface.
	virtual void AllocateDefaultPins() override;
	virtual FText GetTooltipText() const override;
	// //~ End UEdGraphNode Interface.

	//~ Begin K2Node Interface
	virtual bool IsNodePure() const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	//~ End K2Node Interface

protected:
	void NotifyInputChanged() const;
};
