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
	static USendWebSocketMessageAsyncAction* SendMessage(const FString& Message);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	static USendWebSocketMessageAsyncAction* SendJsonMessage(UGenericJsonObject* JsonObject);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	static USendWebSocketMessageAsyncAction* SendBinaryMessage(const TArray<uint8>& Message, const bool bIsBinary = false);

protected:
	virtual void OnMessageSentInternal(const FString& Message) override;
};
