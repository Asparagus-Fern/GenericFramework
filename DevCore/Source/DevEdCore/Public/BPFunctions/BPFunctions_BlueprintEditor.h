// Fill out your copyright notice in the Description page of Project Settings.

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
