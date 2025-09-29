// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocket/WebSocketAsyncActionBase.h"
#include "SendWebSocketMessageAsyncAction.generated.h"

/**
 * 
 */
UCLASS()
class GENERICPROTOCOL_API USendWebSocketMessageAsyncAction : public UWebSocketAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWebSocketMessageSentEvent OnMessageSent;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	static USendWebSocketMessageAsyncAction* SendWebSocketMessage(UGenericWebSocket* WebSocket, const FString& Message);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	static USendWebSocketMessageAsyncAction* SendWebSocketJsonMessage(UGenericWebSocket* WebSocket, UGenericJsonObject* JsonObject);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	static USendWebSocketMessageAsyncAction* SendWebSocketBinaryMessage(UGenericWebSocket* WebSocket, const TArray<uint8>& Message, const bool bIsBinary = false);

protected:
	virtual void OnMessageSentInternal(const FString& Message) override;
};
