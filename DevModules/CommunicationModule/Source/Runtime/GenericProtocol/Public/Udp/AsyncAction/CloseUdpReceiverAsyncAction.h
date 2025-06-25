// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Udp/UdpSocketAsyncActionBase.h"
#include "CloseUdpReceiverAsyncAction.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCloseUdpReceiverAsyncAction : public UUdpReceiverAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketReceiverClosedEvent OnReceiverClosed;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="UDP")
	static UCloseUdpReceiverAsyncAction* CloseUdpReceiver(UGenericUdpSocket* UdpSocket, bool& Result);

protected:
	virtual void OnReceiverClosedInternal() override;
};
