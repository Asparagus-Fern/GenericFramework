// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProtocolType.h"
#include "Generic/GenericObject.h"
#include "GenericUdpSocketBuilder.generated.h"

class FUdpSocketBuilder;
class UGenericUdpSocket;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericUdpSocketBuilder : public UGenericObject
{
	GENERATED_BODY()

public:
	GENERICPROTOCOL_API virtual FSocket* BuildSenderSocket();
	GENERICPROTOCOL_API virtual FSocket* BuildReceiverSocket();

private:
	void Build(FUdpSocketBuilder* UdpSocketBuilder) const;

public:
	UFUNCTION(BlueprintCallable, Category="UDP")
	GENERICPROTOCOL_API void SetIsBlocking(bool IsBlocking = false);

	UFUNCTION(BlueprintCallable, Category="UDP")
	GENERICPROTOCOL_API void SetEnableReusable(bool EnableReusable);

	UFUNCTION(BlueprintCallable, Category="UDP")
	GENERICPROTOCOL_API void SetEnableBroadcast(bool EnableBroadcast);

	UFUNCTION(BlueprintCallable, Category="UDP")
	GENERICPROTOCOL_API void SetEnableMulticastLoopback(bool EnableMulticastLoopback);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"), Category="UDP")
	FString SocketName = TEXT("GenericUdpSocket");

	/* Sets socket operations to be blocking/non-blocking */
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"), Category="UDP")
	bool bIsBlocking = false;

	/* Makes the bound address reusable by other sockets. */
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"), Category="UDP")
	bool bEnableReusable = true;

	/* Enables broadcasting. */
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"), Category="UDP")
	bool bEnableBroadcast = false;

	/* Enables multicast loopback. */
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"), Category="UDP")
	bool bEnableMulticastLoopback = false;

public:
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"), Category="UDP")
	bool bEnableSend = true;

	/* Specifies the desired size of the send buffer in bytes (0 = default). */
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true", EditConditionHides, EditCondition = "bEnableSend"), Category="UDP")
	int32 SendBufferSize = 0;

	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true", EditConditionHides, EditCondition = "bEnableSend"), Category="UDP")
	FString SendIp = TEXT("127.0.0.1");

	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true", EditConditionHides, EditCondition = "bEnableSend"), Category="UDP")
	int32 SendPort = 8060;

	UPROPERTY(BlueprintReadOnly)
	FString SendBoundIp = TEXT("127.0.0.1");

	UPROPERTY(BlueprintReadOnly)
	int32 SendBoundPort = 8060;

public:
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true"), Category="UDP")
	bool bEnableReceive = true;

	/* Specifies the desired size of the receive buffer in bytes (0 = default). */
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true", EditConditionHides, EditCondition = "bEnableReceive"), Category="UDP")
	int32 ReceiveBufferSize = 0;

	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true", EditConditionHides, EditCondition = "bEnableReceive"), Category="UDP")
	FString ReceiveIp = TEXT("0.0.0.0");

	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn = "true", EditConditionHides, EditCondition = "bEnableReceive"), Category="UDP")
	int32 ReceivePort = 8060;

	UPROPERTY(BlueprintReadOnly)
	FString ReceiveBoundIp = TEXT("127.0.0.1");

	UPROPERTY(BlueprintReadOnly)
	int32 ReceiveBoundPort = 8060;
};
