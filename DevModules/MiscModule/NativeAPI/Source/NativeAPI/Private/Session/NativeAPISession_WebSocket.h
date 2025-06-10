// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeAPITypes.h"
#include "INativeAPISessionFeature.h"
#include "WebSocket/WebSocketType.h"

#if WITH_WEBSOCKETS
class IWebSocket;
#endif

/**
 * 
 */
class FNativeAPISession_WebSocket : public INativeAPISessionFeature
{
public:
	FNativeAPISession_WebSocket();
	virtual bool StartSession() override;
	virtual void EndSession() override;

	virtual FName GetSessionName() override
	{
		static FName SessionName(TEXT("WebSocket"));
		return SessionName;
	}

private:
	void HandleOnWebSocketConnection();
	void HandleOnWebSocketConnectionError(const FString& Error);
	void HandleOnWebSocketMessage(const FString& InMessage);

#if WITH_WEBSOCKETS
	TSharedPtr<IWebSocket> WebSocket;
#endif

	FWebSocketConnection Connection;
};
