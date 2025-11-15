// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunction_Network.generated.h"

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UBPFunction_Network : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Unique Network ID(Player Controller)", CompactNodeTitle = "->", BlueprintAutocast))
	static FUniqueNetworkID Conv_PlayerControllerToUniqueNetworkID(APlayerController* InPlayerController);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Unique Network ID(Player State)", CompactNodeTitle = "->", BlueprintAutocast))
	static FUniqueNetworkID Conv_PlayerStateToUniqueNetworkID(APlayerState* InPlayerState);
};
