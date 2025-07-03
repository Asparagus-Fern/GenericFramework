// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ThreadType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Thread.generated.h"

/**
 * 
 */
UCLASS()
class GENERICTHREADSYSTEM_API UBPFunctions_Thread : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, category="Thread")
	static bool IsThreadValid(const FThreadHandle& ThreadHandle);

	UFUNCTION(BlueprintPure, category="Thread")
	static bool IsThreadRunning(const FThreadHandle& ThreadHandle);

	UFUNCTION(BlueprintPure, category="Thread")
	static bool GetThreadName(const FThreadHandle& ThreadHandle, FString& ThreadName);

	UFUNCTION(BlueprintPure, category="Thread")
	static bool GetThreadDuration(const FThreadHandle& ThreadHandle, FTimespan& Duration);

public:
	UFUNCTION(BlueprintPure, meta= (CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), category="Thread")
	static bool EqualEqual_ThreadHandle(const FThreadHandle& A, const FThreadHandle& B);

	UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "!=", ScriptMethod = "NotEqual", ScriptOperator = "!=", Keywords = "!= not equal"), category="Thread")
	static bool NotEqual_ThreadHandle(const FThreadHandle& A, const FThreadHandle& B);
};
