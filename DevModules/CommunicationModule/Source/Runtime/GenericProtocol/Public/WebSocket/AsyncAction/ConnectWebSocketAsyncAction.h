// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocket/WebSocketAsyncActionBase.h"
#include "ConnectWebSocketAsyncAction.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UConnectWebSocketAsyncAction : public UWebSocketAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWebSocketConnectedEvent OnConnected;

	UPROPERTY(BlueprintAssignable)
	FWebSocketConnectionErrorEvent OnConnectionError;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	static UConnectWebSocketAsyncAction* ConnectWithConnection(FWebSocketConnection InWebSocketConnect);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "Headers"), Category ="WebSocket")
	static UConnectWebSocketAsyncAction* ConnectWithURL(FString Host, int32 Port, EWebSocketProtocol Protocol, TMap<FString, FString> Headers);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	static UConnectWebSocketAsyncAction* Connect(UGenericWebSocket* InWebSocket);

protected:
	virtual void OnConnectedInternal() override;
	virtual void OnConnectionErrorInternal(const FString& Error) override;
};
