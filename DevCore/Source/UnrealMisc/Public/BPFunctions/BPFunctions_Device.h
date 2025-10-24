// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Type/NetworkAdapterType.h"
#include "BPFunctions_Device.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMISC_API UBPFunctions_Device : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* ==================== Generic ==================== */
public:
	UFUNCTION(BlueprintPure, Category="Device | Generic")
	static FString GetDeviceID();

	UFUNCTION(BlueprintPure, Category="Device | Generic")
	static FString GetDeviceName();

	UFUNCTION(BlueprintPure, Category="Device | Generic")
	static FString GetDeviceUserName();

	UFUNCTION(BlueprintPure, Category="Device | Generic")
	static FString GetDeviceBaseDir();

	UFUNCTION(BlueprintPure, Category="Device | Generic")
	static FString GetDeviceUserDir();

	UFUNCTION(BlueprintPure, Category="Device | Generic")
	static FString GetDeviceUserTempDir();

	UFUNCTION(BlueprintPure, Category="Device | Generic")
	static FString GetDeviceUserHomeDir();

	UFUNCTION(BlueprintPure, Category="Device | Generic")
	static void GetNetworkAdapterInfo(TArray<FNetworkAdapterInfo>& Infos);

public:
	UFUNCTION(BlueprintCallable, Category="Device | CPU")
	static void Test_CPUInfo();

	/* CPU 供应商 Ex:GenuineIntel */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static FString GetCPUVendor();

	/* CPU 品牌 Ex:13th Gen Intel(R) Core(TM) i5-13600KF */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static FString GetCPUBrand();

	/* CPU 物理核心数 */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static int32 GetCPUPhysicalCores();

	/* CPU 内核数 */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static int32 GetCPUCores();

	/* CPU 逻辑核心数 */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static int32 GetCPULogicalCores();

	/* CPU利用率 */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static float GetCPUUsage();

	/* CPU 基准速度 (MHz) Ex:3494MHz */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static float GetCPUFrequency();

	/* 进程数 */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static int32 GetCPUProcessCount();

	/* 线程数 */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static int32 GetCPUThreadCount();

	/* 运行时间 */
	UFUNCTION(BlueprintPure, Category="Device | CPU")
	static double GetSystemUptimeSecond();

public:
	UFUNCTION(BlueprintCallable, Category="Device | GPU")
	static void Test_GPUInfo();

	/* Ex:NVIDIA GeForce RTX 4070 Ti */
	UFUNCTION(BlueprintPure, Category="Device | GPU")
	static FString GetGPUAdapterName();

	/* 驱动程序内部版本号 Ex:32.0.15.6094 */
	UFUNCTION(BlueprintPure, Category="Device | GPU")
	static FString GetGPUAdapterInternalDriverVersion();

	/* 驱动程序公开版本号 Ex:560.94 */
	UFUNCTION(BlueprintPure, Category="Device | GPU")
	static FString GetGPUAdapterUserDriverVersion();

	/* 驱动程序日期 */
	UFUNCTION(BlueprintPure, Category="Device | GPU")
	static FString GetGPUAdapterDriverDate();

	UFUNCTION(BlueprintPure, Category="Device | GPU")
	static FString GetGPUDeviceId();

	UFUNCTION(BlueprintPure, Category="Device | GPU")
	static FString GetGPUDeviceRevision();

	UFUNCTION(BlueprintPure, Category="Device | GPU")
	static FString GetGPUVendorId();

	/* ==================== Android ==================== */
public:
	UFUNCTION(BlueprintCallable, Category="Device | Android")
	static bool CheckAndroidPermission(const FString& InPermission);
};
