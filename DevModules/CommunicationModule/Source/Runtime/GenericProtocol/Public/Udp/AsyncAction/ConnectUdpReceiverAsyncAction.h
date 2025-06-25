// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Udp/UdpSocketAsyncActionBase.h"
#include "ConnectUdpReceiverAsyncAction.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class  UConnectUdpReceiverAsyncAction : public UUdpReceiverAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketReceiverConnectedEvent OnReceiverConnected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketReceiverConnectionErrorEvent OnReceiverConnectionError;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="UDP")
	static UConnectUdpReceiverAsyncAction* ConnectUdpReceiver(UGenericUdpSocket* UdpSocket, bool& Result);

protected:
	virtual void OnReceiverConnectedInternal() override;
	virtual void OnReceiverConnectionErrorInternal() override;
};
