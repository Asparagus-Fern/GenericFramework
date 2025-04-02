// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtraProcType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_ExtraProc.generated.h"

/**
 * 
 */
UCLASS()
class EXTRAPROC_API UBPFunctions_ExtraProc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

// public:
// 	UFUNCTION(BlueprintPure)
// 	static bool IsValid(const FExtraProcHandle& InHandle);
//
// 	UFUNCTION(BlueprintPure)
// 	static bool IsRunning(const FExtraProcHandle& InHandle);
//
// 	UFUNCTION(BlueprintPure)
// 	static FTimespan GetDuration(const FExtraProcHandle& InHandle);
//
// 	UFUNCTION(BlueprintCallable)
// 	static bool ExecuteExtraProc(const FProcStartUpInfo& Info, FExtraProcHandle& OutHandle);
//
// 	UFUNCTION(BlueprintCallable)
// 	static void TerminationExtraProc(UPARAM(ref) FExtraProcHandle& InHandle, bool bKillTree = false);
//
// 	UFUNCTION(BlueprintPure, meta= (CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"))
// 	static bool EqualEqual_ExtraProcHandle(const FExtraProcHandle& A, const FExtraProcHandle& B);
//
// 	UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "!=", ScriptMethod = "NotEqual", ScriptOperator = "!=", Keywords = "!= not equal"))
// 	static bool NotEqual_ExtraProcHandle(const FExtraProcHandle& A, const FExtraProcHandle& B);
};
