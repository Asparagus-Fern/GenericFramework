// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocket/WebSocketType.h"
#include "WebSocket/GenericWebSocket.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WebSocketAsyncActionBase.generated.h"

class UGenericWebSocket;

/**
 * 
 */
UCLASS(Abstract)
class GENERICPROTOCOL_API UWebSocketAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void SetReadyToDestroy() override;

protected:
	void InitWebSocket(UGenericWebSocket* InWebSocket);
	UGenericWebSocket* GetWebSocket();
	
private:
	void BindWebSocketDelegate();
	void UnBindWebSocketDelegate() const;

private:
	UFUNCTION()
	void HandleOnConnected(UGenericWebSocket* WebSocket);

	UFUNCTION()
	void HandleOnConnectionError(const FString& Error);

	UFUNCTION()
	void HandleOnRawMessage(const TArray<uint8>& Data, int32 BytesRemaining);

	UFUNCTION()
	void HandleOnBinaryMessage(const TArray<uint8>& Data, bool bIsLastFragment);

	UFUNCTION()
	void HandleOnMessage(const FString& Message);

	UFUNCTION()
	void HandleOnMessageSent(const FString& Message);

	UFUNCTION()
	void HandleOnClosed(int32 Status, const FString& Reason, bool bWasClean);

	UFUNCTION()
	void HandleOnReStarted();

	UFUNCTION()
	void HandleOnReStartError(const FString& Error);

protected:
	virtual void OnConnectedInternal(UGenericWebSocket* WebSocket) { return; }
	virtual void OnConnectionErrorInternal(const FString& Error) { return; }
	virtual void OnRawMessageInternal(const TArray<uint8>& Data, int32 BytesRemaining) { return; }
	virtual void OnBinaryMessageInternal(const TArray<uint8>& Data, bool bIsLastFragment) { return; }
	virtual void OnMessageInternal(const FString& Message) { return; }
	virtual void OnMessageSentInternal(const FString& Message) { return; }
	virtual void OnClosedInternal(int32 Status, const FString& Reason, bool bWasClean) { return; }
	virtual void OnReStartedInternal() { return; }
	virtual void OnReStartErrorInternal(const FString& Error) { return; }

private:
	UPROPERTY()
	UGenericWebSocket* WebSocketInternal = nullptr;
};
