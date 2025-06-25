// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Udp/UdpSocketAsyncActionBase.h"
#include "ConnectUdpSenderAsyncAction.generated.h"

/**
 * 
 */
UCLASS()
class GENERICPROTOCOL_API UConnectUdpSenderAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "UDP")
	FUdpSocketSenderConnectedEvent OnSenderConnected;

	UPROPERTY(BlueprintAssignable, Category = "UDP")
	FUdpSocketSenderConnectionErrorEvent OnSenderConnectionError;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="UDP")
	static UConnectUdpSenderAsyncAction* ConnectUdpSender(UGenericUdpSocket* UdpSocket, bool& Result);

private:
	UFUNCTION()
	void HandleOnSenderConnected(const FString& SendBoundIp, const int32& SendBoundPort);

	UFUNCTION()
	void HandleOnSenderConnectionError(const FString& SendIp, const int32& SendPort);
};
