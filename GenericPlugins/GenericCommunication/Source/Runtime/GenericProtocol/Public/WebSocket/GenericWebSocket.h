// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocketType.h"
#include "Obect/GenericObject.h"
#include "GenericWebSocket.generated.h"

class UGenericJsonObject;
class IWebSocket;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketConnectedEvent, UGenericWebSocket*, WebSocket);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketConnectionErrorEvent, const FString&, Error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWebSocketRawMessageEvent, const TArray<uint8>&, Data, int32, BytesRemaining);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWebSocketBinaryMessageEvent, const TArray<uint8>&, Data, bool, bIsLastFragment);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketMessageEvent, const FString&, Message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketMessageSentEvent, const FString&, Message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWebSocketClosedEvent, int32, Status, const FString&, Reason, bool, bWasClean);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebSocketReStartedEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketReStartErrorEvent, const FString&, Error);

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericWebSocket : public UGenericObject
{
	GENERATED_BODY()

public:
	UGenericWebSocket(const FObjectInitializer& ObjectInitializer);

public:
	/* 创建一个 WebSocket 对象以连接到 WebSocket 服务器 */
	UFUNCTION(BlueprintPure, Category = "WebSocket")
	static GENERICPROTOCOL_API UGenericWebSocket* CreateWebSocket();

	/* 返回此socket当前是否连接到服务器。 */
	UFUNCTION(BlueprintPure, Category = "WebSocket")
	GENERICPROTOCOL_API bool IsConnected() const;

	/* 连接到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void ConnectWithConnection(const FGenericWebSocketConnection& InWebSocketConnect);

	/* 连接到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket", meta=(AutoCreateRefTerm = "Headers"))
	GENERICPROTOCOL_API void ConnectWithURL(FString Host, int32 Port, EGenericWebSocketProtocol Protocol, const TMap<FString, FString>& Headers);

	/* 连接到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void Connect();

	/* 关闭与 WebSocket 服务器的连接 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void Close(int32 Code = 1000, FString Reason = "Close Normal");

	/* 重启与 WebSocket 服务器的连接 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void ReStart();

	/* 将指定的消息发送到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void SendMessage(const FString& Message);

	/* 将指定的消息发送到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void SendJsonMessage(UGenericJsonObject* JsonObject);

	/* 将指定的消息发送到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void SendBinaryMessage(const TArray<uint8>& Message, const bool bIsBinary = false);

private:
	void BindWebSocketDelegate();
	void UnBindWebSocketDelegate() const;

public:
	UFUNCTION(BlueprintPure, Category = "WebSocket")
	GENERICPROTOCOL_API FString GetHost() const;

	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void SetHost(FString InHost);

	UFUNCTION(BlueprintPure, Category = "WebSocket")
	GENERICPROTOCOL_API int32 GetPort() const;

	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void SetPort(int32 InPort);

	UFUNCTION(BlueprintPure, Category = "WebSocket")
	GENERICPROTOCOL_API EGenericWebSocketProtocol GetProtocol() const;

	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	GENERICPROTOCOL_API void SetProtocol(EGenericWebSocketProtocol InProtocol);

	UFUNCTION(BlueprintCallable)
	GENERICPROTOCOL_API void AddHeader(const FString& Header, const FString& Value);

	UFUNCTION(BlueprintCallable)
	GENERICPROTOCOL_API void AddHeaders(TMap<FString, FString> Headers);

	UFUNCTION(BlueprintCallable)
	GENERICPROTOCOL_API void RemoveHeader(const FString& Header);

	UFUNCTION(BlueprintCallable)
	GENERICPROTOCOL_API void RemoveHeaders(TArray<FString> Headers);

	UFUNCTION(BlueprintPure)
	GENERICPROTOCOL_API TMap<FString, FString> GetHeaders();

	UFUNCTION(BlueprintCallable)
	GENERICPROTOCOL_API void SetHeaders(TMap<FString, FString> Headers);

public:
	/* 当 WebSocket 成功连接到服务器时调用此事件 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketConnectedEvent OnConnectedEvent;

	/* 当 WebSocket 无法连接到服务器时调用此事件 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketConnectionErrorEvent OnConnectionErrorEvent;

	/* 当接收到任何 WebSocket 的消息时调用此事件 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketRawMessageEvent OnRawMessageEvent;

	/* 当接收到 WebSocket 的二进制消息时调用此事件 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketBinaryMessageEvent OnBinaryMessageEvent;

	/* 当接收到 WebSocket 的文本消息时调用此事件 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketMessageEvent OnMessageEvent;

	/* 当发送完 WebSocket 消息时调用此事件 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketMessageSentEvent OnMessageSentEvent;

	/* 当连接关闭时调用此事件。 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketClosedEvent OnCloseEvent;

	/* 当重新连接时调用此事件。 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketReStartedEvent OnReStartedEvent;

	/* 当重新连接失败时调用此事件。 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "WebSocket")
	FWebSocketReStartErrorEvent OnReStartErrorEvent;

protected:
	GENERICPROTOCOL_API virtual void OnConnected();
	GENERICPROTOCOL_API virtual void OnConnectionError(const FString& Error);
	GENERICPROTOCOL_API virtual void OnRawMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining);
	GENERICPROTOCOL_API virtual void OnBinaryMessage(const void* Data, SIZE_T Size, bool bIsLastFragment);
	GENERICPROTOCOL_API virtual void OnMessage(const FString& Message);
	GENERICPROTOCOL_API virtual void OnMessageSent(const FString& Message);
	GENERICPROTOCOL_API virtual void OnClosed(int32 Status, const FString& Reason, bool bWasClean);

private:
	TSharedPtr<IWebSocket> WebSocket = nullptr;
	TSharedPtr<IWebSocket> WebSocketCache = nullptr;
	FGenericWebSocketConnection WebSocketConnect;

	bool bBroadcastReStart = false;
};
