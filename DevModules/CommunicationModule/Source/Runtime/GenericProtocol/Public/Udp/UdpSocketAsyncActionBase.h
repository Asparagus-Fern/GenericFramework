// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericUdpSocket.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UdpSocketAsyncActionBase.generated.h"

class UGenericUdpSocketBuilder;
class UGenericUdpSocket;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UUdpSocketAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:
	virtual void InitUdpSocket(UGenericUdpSocket* UdpSocket);
	UGenericUdpSocket* GetUdpSocket() const { return UdpSocketInternal; }

private:
	UPROPERTY()
	UGenericUdpSocket* UdpSocketInternal = nullptr;
};


/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UUdpSenderAsyncActionBase : public UUdpSocketAsyncActionBase
{
	GENERATED_BODY()

protected:
	virtual void InitUdpSocket(UGenericUdpSocket* UdpSocket) override;
	virtual void SetReadyToDestroy() override;

protected:
	UFUNCTION()
	void HandleOnMessageSent(const FString& Message);

	UFUNCTION()
	void HandleOnMessageSentError(const FString& Message);

	UFUNCTION()
	void HandleOnSenderClosed(const FString& SendIp, const int32& SendPort);

protected:
	virtual void OnMessageSentInternal(const FString& Message) { return; }
	virtual void OnMessageSentErrorInternal(const FString& Message) { return; }
	virtual void OnSenderClosedInternal(const FString& SendIp, const int32& SendPort) { return; }
};


/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UUdpReceiverAsyncActionBase : public UUdpSocketAsyncActionBase
{
	GENERATED_BODY()

protected:
	virtual void InitUdpSocket(UGenericUdpSocket* UdpSocket) override;
	virtual void SetReadyToDestroy() override;

private:
	UFUNCTION()
	void HandleOnReceiverConnected();

	UFUNCTION()
	void HandleOnReceiverConnectionError();

	UFUNCTION()
	void HandleOnMessage(const FString& Message);

	UFUNCTION()
	void HandleOnReceiverClosed();

protected:
	virtual void OnReceiverConnectedInternal() { return; }
	virtual void OnReceiverConnectionErrorInternal() { return; }
	virtual void OnMessageInternal(const FString& Message) { return; }
	virtual void OnReceiverClosedInternal() { return; }
};
