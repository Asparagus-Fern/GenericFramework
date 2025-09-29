// Copyright ChenTaiye 2025,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_ExternalData.generated.h"

class UExternalData;

UENUM()
enum class EExternalDataResult : uint8
{
	Valid,
	NotValid,
};

/**
 * 
 */
UCLASS()
class EXTERNALDATA_API UBPFunctions_ExternalData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "Json Data", meta = (CustomStructureParam = "Value", ExpandEnumAsExecs = "ExecResult", BlueprintInternalUseOnly = "true"))
	static void GetData(EExternalDataResult& ExecResult, UPARAM(ref)
	                    const UExternalData* Data, int32& Value);

private:
	DECLARE_FUNCTION(execGetData);
};
