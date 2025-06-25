// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Udp/UdpSocketAsyncActionBase.h"
#include "ReceiveUdpMessageAsyncAction.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UReceiveUdpMessageAsyncAction : public UUdpReceiverAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketMessageEvent OnMessage;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="UDP")
	static UReceiveUdpMessageAsyncAction* ReceiveUdpMessage(UGenericUdpSocket* UdpSocket);

protected:
	virtual void OnMessageInternal(const FString& Message) override;
};
