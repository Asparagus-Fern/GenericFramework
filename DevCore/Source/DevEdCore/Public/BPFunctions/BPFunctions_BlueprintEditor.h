// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_BlueprintEditor.generated.h"

class FBlueprintEditor;

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UBPFunctions_BlueprintEditor : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TSharedPtr<FBlueprintEditor> GetBlueprintEditor(const UBlueprint* InBlueprint);
};
