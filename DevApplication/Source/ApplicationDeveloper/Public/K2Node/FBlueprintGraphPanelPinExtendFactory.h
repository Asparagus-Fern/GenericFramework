#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class FBlueprintGraphPanelPinExtendFactory : public FGraphPanelPinFactory
{
public:
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* Pin) const override;

protected:
	virtual TArray<TSharedPtr<FName>> GetObjectFunctionNames(UObject* InObject) const;
};
