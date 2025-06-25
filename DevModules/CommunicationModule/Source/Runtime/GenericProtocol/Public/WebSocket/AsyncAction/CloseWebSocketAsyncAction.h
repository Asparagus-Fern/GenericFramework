// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocket/WebSocketAsyncActionBase.h"
#include "CloseWebSocketAsyncAction.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCloseWebSocketAsyncAction : public UWebSocketAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWebSocketClosedEvent OnClosed;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	UCloseWebSocketAsyncAction* CloseWebSocket(UGenericWebSocket* WebSocket, int32 Code = 1000, FString Reason = "Close Normal");

protected:
	virtual void OnClosedInternal(int32 Status, const FString& Reason, bool bWasClean) override;
};
