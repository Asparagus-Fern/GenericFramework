// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Network/NetworkAdapterType.h"
#include "BPFunctions_Device.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Device : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="Hardware | Network")
	static FString GetDeviceName();

	UFUNCTION(BlueprintPure, Category="Hardware | Network")
	static FString GetDeviceUserName();
	
	UFUNCTION(BlueprintPure, Category="Hardware | Network")
	static FString GetDeviceBaseDir();

	UFUNCTION(BlueprintPure, Category="Hardware | Network")
	static FString GetDeviceUserDir();

	UFUNCTION(BlueprintPure, Category="Hardware | Network")
	static FString GetDeviceUserTempDir();

	UFUNCTION(BlueprintPure, Category="Hardware | Network")
	static FString GetDeviceUserHomeDir();
	
	UFUNCTION(BlueprintPure, Category="Hardware | Network")
	static void GetNetworkAdapterInfo(TArray<FNetworkAdapterInfo>& Infos);

	/* CPU */
public:
	UFUNCTION(BlueprintCallable, Category="Hardware | CPU")
	static void Test_CPUInfo();

	/* CPU 供应商 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static FString GetCPUVendor();

	/* CPU 品牌 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static FString GetCPUBrand();

	/* CPU 物理核心数 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static int32 GetPhysicalCores();

	/* CPU 内核数 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static int32 GetCPUCores();

	/* CPU 逻辑核心数 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static int32 GetLogicalCores();

	/* CPU利用率 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static float GetCPUUsage();

	/* CPU 基准速度 (MHz) */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static float GetCPUFrequency();

	/* 进程数 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static int32 GetCPUProcessCount();

	/* 线程数 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static int32 GetCPUThreadCount();

	/* 运行时间 */
	UFUNCTION(BlueprintPure, Category="Hardware | CPU")
	static double GetSystemUptimeSecond();

public:
	UFUNCTION(BlueprintCallable, Category="Hardware | GPU")
	static void Test_GPUInfo();

	UFUNCTION(BlueprintPure, Category="Hardware | GPU")
	static FString GetGPUAdapterName();

	UFUNCTION(BlueprintPure, Category="Hardware | GPU")
	static FString GetAdapterInternalDriverVersion();

	/* todo : ... */
};
