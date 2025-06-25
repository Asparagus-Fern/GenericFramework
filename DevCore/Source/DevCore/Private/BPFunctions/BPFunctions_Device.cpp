// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_Device.h"

#include "SocketSubsystem.h"
#include "BPFunctions/BPFunctions_Convert.h"
#include "Debug/DebugType.h"
#include "GenericPlatform/GenericPlatformDriver.h"

#include "tinyxml2.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Pdh.h"
#include "Psapi.h"
#include "TlHelp32.h"
#include "iptypes.h"
#include "iphlpapi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#elif PLATFORM_ANDROID

#endif

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

			NetworkAdapterInfo.Name = FConvertLibrary::ToString(pAdapter->AdapterName);
			NetworkAdapterInfo.Description = FConvertLibrary::ToString(pAdapter->Description);
			NetworkAdapterInfo.MacAddress = FString::Printf(TEXT("%02X-%02X-%02X-%02X-%02X-%02X"), pAdapter->Address[0], pAdapter->Address[1], pAdapter->Address[2], pAdapter->Address[3], pAdapter->Address[4], pAdapter->Address[5]);
			NetworkAdapterInfo.Index = pAdapter->Index;
			NetworkAdapterInfo.Type = pAdapter->Type;
			NetworkAdapterInfo.bEnableDHCP = FConvertLibrary::ToBool(pAdapter->DhcpEnabled);

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
#elif PLATFORM_ANDROID
	
#endif
}

void UBPFunctions_Device::Test_CPUInfo()
{
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("CPUVendor"), *GetCPUVendor())
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("CPUBrand"), *GetCPUBrand())
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("PhysicalCores"), *FString::FromInt(GetPhysicalCores()))
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("CPUCores"), *FString::FromInt(GetCPUCores()))
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("LogicalCores"), *FString::FromInt(GetLogicalCores()))
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("CPUUsage"), *FString::SanitizeFloat(GetCPUUsage()))
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("CPUFrequency"), *FString::SanitizeFloat(GetCPUFrequency()))
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("CPUProcessCount"), *FString::FromInt(GetCPUProcessCount()))
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("CPUThreadCount"), *FString::FromInt(GetCPUThreadCount()))
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("SystemUptimeSecond"), *FString::SanitizeFloat(GetSystemUptimeSecond()))
}

FString UBPFunctions_Device::GetCPUVendor()
{
#if PLATFORM_WINDOWS
	return FWindowsPlatformMisc::GetCPUVendor();
#endif
}

FString UBPFunctions_Device::GetCPUBrand()
{
#if PLATFORM_WINDOWS
	return FWindowsPlatformMisc::GetCPUBrand();
#endif
}

int32 UBPFunctions_Device::GetPhysicalCores()
{
#if PLATFORM_WINDOWS
	return FGenericPlatformMisc::NumberOfCores();
#endif
}

int32 UBPFunctions_Device::GetCPUCores()
{
	return FGenericPlatformMisc::NumberOfCoresIncludingHyperthreads();
}

int32 UBPFunctions_Device::GetLogicalCores()
{
	return -1;
}

float UBPFunctions_Device::GetCPUUsage()
{
#if PLATFORM_WINDOWS
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
#endif
}

float UBPFunctions_Device::GetCPUFrequency()
{
#if PLATFORM_WINDOWS
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		return 0.0f;
	}

	DWORD mhz = 0;
	DWORD size = sizeof(DWORD);
	if (RegQueryValueEx(hKey, L"~MHz", nullptr, nullptr,
	                    reinterpret_cast<LPBYTE>(&mhz), &size
	) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return 0.0f;
	}

	RegCloseKey(hKey);
	return static_cast<float>(mhz);
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
#endif
}

double UBPFunctions_Device::GetSystemUptimeSecond()
{
#if PLATFORM_WINDOWS
	return static_cast<double>(GetTickCount64()) / 1000.0;
#endif
}

void UBPFunctions_Device::Test_GPUInfo()
{
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("GPUName"), *GetGPUAdapterName())
	GenericLOG(GenericLogNetwork, Warning, TEXT("%s : %s"), TEXT("GPUAdapterInternalDriverVersion"), *GetAdapterInternalDriverVersion())
}

FString UBPFunctions_Device::GetGPUAdapterName()
{
	return FString(GRHIAdapterName);
}

FString UBPFunctions_Device::GetAdapterInternalDriverVersion()
{
	return FString(GRHIAdapterInternalDriverVersion);
}
