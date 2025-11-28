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
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Unique Network ID (PlayerController)", CompactNodeTitle = "->", BlueprintAutocast))
	static FUniqueNetworkID Conv_PlayerControllerToUniqueNetworkID(APlayerController* InPlayerController);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Unique Network ID (PlayerState)", CompactNodeTitle = "->", BlueprintAutocast))
	static FUniqueNetworkID Conv_PlayerStateToUniqueNetworkID(APlayerState* InPlayerState);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Unique Network ID (UniqueNetIdRepl)", CompactNodeTitle = "->", BlueprintAutocast))
	static FUniqueNetworkID Conv_UniqueNetIdReplToUniqueNetworkID(const FUniqueNetIdRepl& InUniqueNetIDRepl);

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool GetSessionHandleByUniqueNetID(const UObject* WorldContextObject, const FUniqueNetworkID& UniqueNetworkID, FGenericSessionHandle& OutHandle);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool GetSessionHandleByNetID(const UObject* WorldContextObject, const FUniqueNetIdRepl& UniqueNetIDRepl, FGenericSessionHandle& OutHandle);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool GetSessionHandleByName(const UObject* WorldContextObject, FName InSessionName, FGenericSessionHandle& OutHandle);
};
