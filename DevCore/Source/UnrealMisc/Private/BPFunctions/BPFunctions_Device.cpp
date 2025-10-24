// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_Device.h"

#include "Type/DebugType.h"
#include "StaticFunctions/StaticFunctions_Convert.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Pdh.h"
#include "Psapi.h"
#include "TlHelp32.h"
#include "iptypes.h"
#include "iphlpapi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#elif PLATFORM_ANDROID
#include "AndroidPermissionFunctionLibrary.h"
#endif

#define DeviceTest(TestName) \
{ \
	FString TestFunctionName = TEXT(#TestName); \
	FString TestFunction = FStaticFunctions_Convert::ToString(Get##TestName()); \
	GenericLOG(LogTemp, Warning, TEXT("%s : %s"), *TestFunctionName, *TestFunction) \
	GenericPRINT(Warning, TEXT("%s : %s"), *TestFunctionName, *TestFunction) \
}

/* ==================== Generic ==================== */

FString UBPFunctions_Device::GetDeviceID()
{
	FString DeviceID = TEXT("");

#if PLATFORM_WINDOWS
	HKEY hKey;
	LONG lResult;

	// 尝试打开注册表键
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Cryptography"), 0, KEY_READ, &hKey);

	if (lResult == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		TCHAR szValue[256] = {0};
		DWORD dwValueSize = sizeof(szValue);

		// 查询 MachineGuid 键值
		lResult = RegQueryValueEx(hKey, TEXT("MachineGuid"), nullptr, &dwType, (LPBYTE)szValue, &dwValueSize);

		if (lResult == ERROR_SUCCESS)
		{
			DeviceID = FString(szValue);
		}
		else
		{
			// 处理查询失败的情况，例如键值不存在
			UE_LOG(LogTemp, Error, TEXT("Failed to query MachineGuid. Error code: %d"), lResult);
		}

		RegCloseKey(hKey);
	}
	else
	{
		// 处理打开注册表键失败的情况
		UE_LOG(LogTemp, Error, TEXT("Failed to open registry key. Error code: %d"), lResult);
	}
#elif PLATFORM_ANDROID && USE_ANDROID_JNI
	extern FString AndroidThunkCpp_GetAndroidId();
	DeviceID = AndroidThunkCpp_GetAndroidId();
#endif

	return DeviceID;
}

FString UBPFunctions_Device::GetDeviceName()
{
	return FPlatformProcess::ComputerName();
}

FString UBPFunctions_Device::GetDeviceUserName()
{
	return FPlatformProcess::UserName();
}

FString UBPFunctions_Device::GetDeviceBaseDir()
{
	return FPlatformProcess::BaseDir();
}

FString UBPFunctions_Device::GetDeviceUserDir()
{
	return FPlatformProcess::UserDir();
}

FString UBPFunctions_Device::GetDeviceUserTempDir()
{
	return FPlatformProcess::UserTempDir();
}

FString UBPFunctions_Device::GetDeviceUserHomeDir()
{
	return FPlatformProcess::UserHomeDir();
}

void UBPFunctions_Device::GetNetworkAdapterInfo(TArray<FNetworkAdapterInfo>& Infos)
{
#if PLATFORM_WINDOWS
	PIP_ADAPTER_INFO pAdapterInfo = nullptr;
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		pAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[ulOutBufLen];
	}

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_SUCCESS)
	{
		PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
		while (pAdapter)
		{
			FNetworkAdapterInfo NetworkAdapterInfo;

			NetworkAdapterInfo.Name = FStaticFunctions_Convert::ToString(pAdapter->AdapterName);
			NetworkAdapterInfo.Description = FStaticFunctions_Convert::ToString(pAdapter->Description);
			NetworkAdapterInfo.MacAddress = FString::Printf(TEXT("%02X-%02X-%02X-%02X-%02X-%02X"), pAdapter->Address[0], pAdapter->Address[1], pAdapter->Address[2], pAdapter->Address[3], pAdapter->Address[4], pAdapter->Address[5]);
			NetworkAdapterInfo.Index = pAdapter->Index;
			NetworkAdapterInfo.Type = pAdapter->Type;
			NetworkAdapterInfo.bEnableDHCP = FStaticFunctions_Convert::ToBool(pAdapter->DhcpEnabled);

			PIP_ADDR_STRING pIpAddr = &pAdapter->IpAddressList;
			while (pIpAddr)
			{
				FNetworkAdapterIp NetworkAdapterIp;
				NetworkAdapterIp.Ip = pIpAddr->IpAddress.String;
				NetworkAdapterIp.Mask = pIpAddr->IpMask.String;
				NetworkAdapterIp.Gateway = pAdapter->GatewayList.IpAddress.String;

				NetworkAdapterInfo.IPList.Add(NetworkAdapterIp);
				pIpAddr = pIpAddr->Next;
			}

			Infos.Add(NetworkAdapterInfo);
			pAdapter = pAdapter->Next;
		}
	}
	delete[] pAdapterInfo;
#endif
}

void UBPFunctions_Device::Test_CPUInfo()
{
	DeviceTest(CPUVendor)
	DeviceTest(CPUBrand)
	DeviceTest(CPUPhysicalCores)
	DeviceTest(CPUCores)
	DeviceTest(CPULogicalCores)
	DeviceTest(CPUUsage)
	DeviceTest(CPUFrequency)
	DeviceTest(CPUProcessCount)
	DeviceTest(CPUThreadCount)
	DeviceTest(SystemUptimeSecond)
}

FString UBPFunctions_Device::GetCPUVendor()
{
	return FPlatformMisc::GetCPUVendor();
}

FString UBPFunctions_Device::GetCPUBrand()
{
	return FPlatformMisc::GetCPUBrand();
}

int32 UBPFunctions_Device::GetCPUPhysicalCores()
{
	return FGenericPlatformMisc::NumberOfCores();
}

int32 UBPFunctions_Device::GetCPUCores()
{
	return FGenericPlatformMisc::NumberOfCoresIncludingHyperthreads();
}

int32 UBPFunctions_Device::GetCPULogicalCores()
{
	return -1;
}

float UBPFunctions_Device::GetCPUUsage()
{
	// static PDH_HQUERY query;
	// static PDH_HCOUNTER counter;
	// static bool initialized = false;
	//
	// if (!initialized)
	// {
	// 	PdhOpenQuery(nullptr, 0, &query);
	// 	PdhAddCounter(query, L"\\Processor(_Total)\\% Processor Time", 0, &counter);
	// 	initialized = true;
	// }
	//
	// PDH_FMT_COUNTERVALUE value;
	// PdhCollectQueryData(query);
	// PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, nullptr, &value);
	// return value.doubleValue;
	return 0.f;
}

float UBPFunctions_Device::GetCPUFrequency()
{
#if PLATFORM_WINDOWS
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		return 0.f;
	}

	DWORD mhz = 0;
	DWORD size = sizeof(DWORD);
	if (RegQueryValueEx(hKey, L"~MHz", nullptr, nullptr, reinterpret_cast<LPBYTE>(&mhz), &size) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return 0.f;
	}

	RegCloseKey(hKey);
	return static_cast<float>(mhz);
#else
	return -1.f;
#endif
}

int32 UBPFunctions_Device::GetCPUProcessCount()
{
#if PLATFORM_WINDOWS
	DWORD processes[1024], cbNeeded;
	if (!EnumProcesses(processes, sizeof(processes), &cbNeeded))
	{
		return 0;
	}
	return cbNeeded / sizeof(DWORD);
#else
	return -1;
#endif
}

int32 UBPFunctions_Device::GetCPUThreadCount()
{
#if PLATFORM_WINDOWS
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) return 0;

	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32);

	int32 threadCount = 0;
	if (Thread32First(hSnapshot, &te32))
	{
		do
		{
			threadCount++;
		}
		while (Thread32Next(hSnapshot, &te32));
	}

	CloseHandle(hSnapshot);
	return threadCount;
#else
	return -1;
#endif
}

double UBPFunctions_Device::GetSystemUptimeSecond()
{
#if PLATFORM_WINDOWS
	return static_cast<double>(GetTickCount64()) / 1000.0;
#else
	return -1.f;
#endif
}

void UBPFunctions_Device::Test_GPUInfo()
{
	DeviceTest(GPUAdapterName)
	DeviceTest(GPUAdapterInternalDriverVersion)
	DeviceTest(GPUAdapterUserDriverVersion)
	DeviceTest(GPUAdapterDriverDate)
	DeviceTest(GPUDeviceId)
	DeviceTest(GPUDeviceRevision)
	DeviceTest(GPUVendorId)
}

FString UBPFunctions_Device::GetGPUAdapterName()
{
	return GRHIGlobals.GpuInfo.AdapterName;
}

FString UBPFunctions_Device::GetGPUAdapterInternalDriverVersion()
{
	return GRHIGlobals.GpuInfo.AdapterInternalDriverVersion;
}

FString UBPFunctions_Device::GetGPUAdapterUserDriverVersion()
{
	return GRHIGlobals.GpuInfo.AdapterUserDriverVersion;
}

FString UBPFunctions_Device::GetGPUAdapterDriverDate()
{
	return GRHIGlobals.GpuInfo.AdapterDriverDate;
}

FString UBPFunctions_Device::GetGPUDeviceId()
{
	return FStaticFunctions_Convert::ToString(GRHIGlobals.GpuInfo.DeviceId);
}

FString UBPFunctions_Device::GetGPUDeviceRevision()
{
	return FStaticFunctions_Convert::ToString(GRHIGlobals.GpuInfo.DeviceRevision);
}

FString UBPFunctions_Device::GetGPUVendorId()
{
	return FStaticFunctions_Convert::ToString(GRHIGlobals.GpuInfo.VendorId);
}

/* ==================== Android ==================== */

bool UBPFunctions_Device::CheckAndroidPermission(const FString& InPermission)
{
#if PLATFORM_ANDROID
	return UAndroidPermissionFunctionLibrary::CheckPermission(InPermission);
#else
	return false;
#endif
}
