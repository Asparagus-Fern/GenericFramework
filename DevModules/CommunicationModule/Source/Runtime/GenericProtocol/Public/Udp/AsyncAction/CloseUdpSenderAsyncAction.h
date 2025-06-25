// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Udp/UdpSocketAsyncActionBase.h"
#include "CloseUdpSenderAsyncAction.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCloseUdpSenderAsyncAction : public UUdpSenderAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketSenderClosedEvent OnSenderClosed;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="UDP")
	static UCloseUdpSenderAsyncAction* CloseUdpSender(UGenericUdpSocket* UdpSocket, bool& Result);

protected:
	virtual void OnSenderClosedInternal(const FString& SendIp, const int32& SendPort) override;
};
