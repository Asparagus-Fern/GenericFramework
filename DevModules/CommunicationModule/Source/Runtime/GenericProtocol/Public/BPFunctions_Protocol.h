// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Protocol.generated.h"

/**
 * 
 */
UCLASS()
class GENERICPROTOCOL_API UBPFunctions_Protocol : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "WebSocket")
	static FString GetAddress(FString Host, int32 Port);
};
