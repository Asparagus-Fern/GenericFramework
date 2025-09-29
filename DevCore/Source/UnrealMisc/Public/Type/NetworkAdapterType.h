// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkAdapterType.generated.h"

USTRUCT(BlueprintType)
struct FNetworkAdapterIp
{
	GENERATED_BODY()

public:
	/* IP */
	UPROPERTY(BlueprintReadOnly)
	FString Ip;

	/* 子网掩码 */
	UPROPERTY(BlueprintReadOnly)
	FString Mask;

	/* 网关 */
	UPROPERTY(BlueprintReadOnly)
	FString Gateway;
};


/**
 * See _IP_ADAPTER_INFO For More In IPTypes.h
 */
USTRUCT(BlueprintType)
struct FNetworkAdapterInfo
{
	GENERATED_BODY()

public:
	/* 适配器名称 */
	UPROPERTY(BlueprintReadOnly)
	FString Name;

	/* 适配器说明 */
	UPROPERTY(BlueprintReadOnly)
	FString Description;

	/* 是否为此适配器启用动态主机配置协议 (DHCP) */
	UPROPERTY(BlueprintReadOnly)
	bool bEnableDHCP = true;

	/* 适配器索引 */
	UPROPERTY(BlueprintReadOnly)
	int32 Index;

	/* 适配器类型 */
	UPROPERTY(BlueprintReadOnly)
	int32 Type = INDEX_NONE;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FNetworkAdapterIp> IPList;

	/* 硬件地址 */
	UPROPERTY(BlueprintReadOnly)
	FString MacAddress;
};
