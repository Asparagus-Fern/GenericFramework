// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Common/UdpSocketReceiver.h"
#include "Generic/GenericObject.h"
#include "GenericUdpSocket.generated.h"

class FUdpSocketReceiver;
class UGenericUdpSocketBuilder;

/* ==================== Sender ==================== */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUdpSocketSenderConnectedEvent, const FString&, SendBoundIp, const int32&, SendBoundPort);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUdpSocketSenderConnectionErrorEvent, const FString&, SendIp, const int32&, SendPort);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUdpSocketMessageSentEvent, const FString&, Message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUdpSocketMessageSentErrorEvent, const FString&, Message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUdpSocketSenderClosedEvent, const FString&, SendIp, const int32&, SendPort);

/* ==================== Receiver ==================== */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUdpSocketReceiverConnectedEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUdpSocketReceiverConnectionErrorEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUdpSocketMessageEvent, const FString&, Message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUdpSocketReceiverClosedEvent);

/**
 * 
 */
UCLASS()
class GENERICPROTOCOL_API UGenericUdpSocket : public UGenericObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="UDP")
	static UGenericUdpSocket* CreateUdpSocket(UGenericUdpSocketBuilder* InBuilder);

public:
	UFUNCTION(BlueprintCallable, Category="UDP")
	void UpdateUdpSocket(UGenericUdpSocketBuilder* Builder);

public:
	UFUNCTION(BlueprintCallable, Category="UDP")
	bool ConnectSender();

	UFUNCTION(BlueprintCallable, Category="UDP")
	bool SendMessage(FString InMessage);

	UFUNCTION(BlueprintCallable, Category="UDP")
	bool CloseSender();

	UFUNCTION(BlueprintCallable, Category="UDP")
	bool ConnectReceiver();

	UFUNCTION(BlueprintCallable, Category="UDP")
	bool CloseReceiver();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketSenderConnectedEvent OnSenderConnectedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketSenderConnectionErrorEvent OnSenderConnectionErrorEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketMessageSentEvent OnMessageSentEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketMessageSentErrorEvent OnMessageSentErrorEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketSenderClosedEvent OnSenderClosedEvent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketReceiverConnectedEvent OnReceiverConnectedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketReceiverConnectionErrorEvent OnReceiverConnectionErrorEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketMessageEvent OnMessageEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketReceiverClosedEvent OnReceiverClosedEvent;

private:
	void HandleOnDataReceived(const FArrayReaderPtr& DataPtr, const FIPv4Endpoint& Endpoint) const;

protected:
	UPROPERTY(BlueprintReadOnly)
	UGenericUdpSocketBuilder* Builder = nullptr;

	FSocket* SenderSocket = nullptr;
	FSocket* ReceiverSocket = nullptr;
	FUdpSocketReceiver* UDPReceiver = nullptr;
};
