// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "WindowsExtraProcHelper.generated.h"

#if PLATFORM_WINDOWS

/**
 * 
 */
class FWindowsExtraProcHelper
{
public:
	static bool SetProcEndWithCurrentProcTermination(const FProcHandle& InProc);
};

#endif
