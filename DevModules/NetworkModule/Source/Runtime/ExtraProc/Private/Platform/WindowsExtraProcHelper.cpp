// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WindowsExtraProcHelper.h"

#include "Windows/WindowsHWrapper.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <winbase.h>
#include "Windows/HideWindowsPlatformTypes.h"

#if PLATFORM_WINDOWS
Windows::HANDLE JobHandle;

bool GetJobHandle(Windows::HANDLE& OutHandle)
{
	if (JobHandle != nullptr)
	{
		OutHandle = JobHandle;
		return true;
	}

	JobHandle = CreateJobObject(nullptr, nullptr);

	if (JobHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create Job Object : error %d"), GetLastError());
		return false;
	}

	JOBOBJECT_EXTENDED_LIMIT_INFORMATION LimitInformation;
	FPlatformMemory::Memzero(&LimitInformation, sizeof(LimitInformation));

	LimitInformation.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	if (0 == SetInformationJobObject(JobHandle, JobObjectExtendedLimitInformation, &LimitInformation, sizeof(LimitInformation)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not SetInformationJobObject"));
		return false;
	}

	OutHandle = JobHandle;
	return true;
}

bool FWindowsExtraProcHelper::SetProcEndWithCurrentProcTermination(const FProcHandle& InProc)
{
	Windows::HANDLE Handle;

	if (GetJobHandle(Handle) && InProc.IsValid())
	{
		if (AssignProcessToJobObject(Handle, InProc.Get()) == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("AssignProcessToObject failed, error : %d"), GetLastError())
			return false;
		}

		return true;
	}

	return false;
}

#endif
