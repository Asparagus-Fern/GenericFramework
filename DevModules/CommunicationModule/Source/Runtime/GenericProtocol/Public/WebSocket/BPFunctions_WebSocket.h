// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocketType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_WebSocket.generated.h"

/**
 * 
 */
UCLASS()
class GENERICPROTOCOL_API UBPFunctions_WebSocket : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To WebSocket Protocol Enum", CompactNodeTitle = "->", BlueprintAutocast), Category="WebSocket")
	static EWebSocketProtocol BP_ConvertToWebSocketProtocolEnum(FString InProtocol);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To WebSocket Protocol String", CompactNodeTitle = "->", BlueprintAutocast), Category="WebSocket")
	static FString BP_ConvertToWebSocketProtocolString(EWebSocketProtocol InProtocol);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To WebSocket Code Enum", CompactNodeTitle = "->", BlueprintAutocast), Category="WebSocket")
	static EWebSocketCode BP_ConvertToWebSocketCodeEnum(int32 InCode);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To WebSocket Code Int", CompactNodeTitle = "->", BlueprintAutocast), Category="WebSocket")
	static int32 BP_ConvertToWebSocketCodeInt(EWebSocketCode InCode);

public:
	UFUNCTION(BlueprintPure, Category = "WebSocket")
	static FString GetWebSocketUrl(FString Host, int32 Port, EWebSocketProtocol Protocol);
};
