// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtraProcType.h"
#include "ThreadType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_ExtraProc.generated.h"

/**
 * 
 */
UCLASS()
class EXTRAPROC_API UBPFunctions_ExtraProc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool LaunchExtraProc(const FProcStartUpInfo& Info, FThreadHandle& ProcHandle);

	UFUNCTION(BlueprintCallable)
	static void TerminationExtraProc(FThreadHandle& ProcHandle, bool bKillTree = false);
};
