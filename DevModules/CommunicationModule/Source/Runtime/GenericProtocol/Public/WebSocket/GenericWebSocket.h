// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocketType.h"
#include "Generic/GenericObject.h"
#include "GenericWebSocket.generated.h"

class UGenericJsonObject;
class IWebSocket;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebSocketConnectedEvent);

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
UCLASS()
class GENERICPROTOCOL_API UGenericWebSocket : public UGenericObject
{
	GENERATED_BODY()

public:
	UGenericWebSocket(const FObjectInitializer& ObjectInitializer);

public:
	/* 创建一个 WebSocket 对象以连接到 WebSocket 服务器 */
	UFUNCTION(BlueprintPure, Category = "WebSocket")
	static UGenericWebSocket* CreateWebSocket();

	/* 返回此socket当前是否连接到服务器。 */
	UFUNCTION(BlueprintPure, Category = "WebSocket")
	bool IsConnected() const;

	/* 连接到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void ConnectWithConnection(const FWebSocketConnection& InWebSocketConnect);

	/* 连接到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket", meta=(AutoCreateRefTerm = "Headers"))
	void ConnectWithURL(FString Host, int32 Port, EWebSocketProtocol Protocol, const TMap<FString, FString>& Headers);

	/* 连接到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void Connect();

	/* 关闭与 WebSocket 服务器的连接 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void Close(int32 Code = 1000, FString Reason = "Close Normal");

	/* 重启与 WebSocket 服务器的连接 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void ReStart();

	/* 将指定的消息发送到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void SendMessage(const FString& Message);

	/* 将指定的消息发送到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void SendJsonMessage(UGenericJsonObject* JsonObject);

	/* 将指定的消息发送到 WebSocket 服务器 */
	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void SendBinaryMessage(const TArray<uint8>& Message, const bool bIsBinary = false);

private:
	void BindWebSocketDelegate();
	void UnBindWebSocketDelegate() const;

public:
	UFUNCTION(BlueprintPure, Category = "WebSocket")
	FString GetHost() const;

	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void SetHost(FString InHost);

	UFUNCTION(BlueprintPure, Category = "WebSocket")
	int32 GetPort() const;

	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void SetPort(int32 InPort);

	UFUNCTION(BlueprintPure, Category = "WebSocket")
	EWebSocketProtocol GetProtocol() const;

	UFUNCTION(BlueprintCallable, Category = "WebSocket")
	void SetProtocol(EWebSocketProtocol InProtocol);

	UFUNCTION(BlueprintCallable)
	void AddHeader(const FString& Header, const FString& Value);

	UFUNCTION(BlueprintCallable)
	void AddHeaders(TMap<FString, FString> Headers);

	UFUNCTION(BlueprintCallable)
	void RemoveHeader(const FString& Header);

	UFUNCTION(BlueprintCallable)
	void RemoveHeaders(TArray<FString> Headers);

	UFUNCTION(BlueprintPure)
	TMap<FString, FString> GetHeaders();

	UFUNCTION(BlueprintCallable)
	void SetHeaders(TMap<FString, FString> Headers);

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
	virtual void OnConnected();
	virtual void OnConnectionError(const FString& Error);
	virtual void OnRawMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining);
	virtual void OnBinaryMessage(const void* Data, SIZE_T Size, bool bIsLastFragment);
	virtual void OnMessage(const FString& Message);
	virtual void OnMessageSent(const FString& Message);
	virtual void OnClosed(int32 Status, const FString& Reason, bool bWasClean);

private:
	TSharedPtr<IWebSocket> WebSocket = nullptr;
	TSharedPtr<IWebSocket> WebSocketCache = nullptr;
	FWebSocketConnection WebSocketConnect;

	bool bBroadcastReStart = false;
};
