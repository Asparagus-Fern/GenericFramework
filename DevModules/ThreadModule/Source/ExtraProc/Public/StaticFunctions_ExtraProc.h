// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtraProcType.h"
// #include "StaticFunctions_ExtraProc.generated.h"

/**
 * 
 */
class EXTRAPROC_API FStaticFunctions_ExtraProc 
{
public:
	static bool LaunchExtraProc(const FProcStartUpInfo& Info, FGuid& ProcId);
	static bool LaunchExtraProc(const FString& Urls, const FString& Params, bool RunInBackground, bool CreatePipe, bool TerminateWithParentProc, FGuid& OutProcId);
	static void TerminationExtraProc(FGuid ProcId, bool bKillTree = false);
};
