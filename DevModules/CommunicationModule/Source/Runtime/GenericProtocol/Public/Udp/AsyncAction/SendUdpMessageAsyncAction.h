// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Udp/UdpSocketAsyncActionBase.h"
#include "SendUdpMessageAsyncAction.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class USendUdpMessageAsyncAction : public UUdpSenderAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketMessageSentEvent OnMessageSent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category = "UDP")
	FUdpSocketMessageSentErrorEvent OnMessageSentError;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="UDP")
	static USendUdpMessageAsyncAction* SendUdpMessage(UGenericUdpSocket* UdpSocket, FString InMessage, bool& Result);

protected:
	virtual void OnMessageSentInternal(const FString& Message) override;
	virtual void OnMessageSentErrorInternal(const FString& Message) override;
};
