// Copyright ChenTaiye 2025,. All Rights Reserved.

#include "BPFunctions_ExternalData.h"
#include "ExternalData.h"
#include "Blueprint/BlueprintExceptionInfo.h"

#define LOCTEXT_NAMESPACE "FExternalDataModule"

void UBPFunctions_ExternalData::GetData(EExternalDataResult& ExecResult, const UExternalData* Data, int32& Value)
{
	checkNoEntry();
}

DEFINE_FUNCTION(UBPFunctions_ExternalData::execGetData)
{
	P_GET_ENUM_REF(EExternalDataResult, ExecResult);
	P_GET_OBJECT_REF(UExternalData, Data);

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);

	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;

	ExecResult = EExternalDataResult::NotValid;

	if (!ValueProp || !ValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("ExternalData_GetInvalidValueWarning", "Failed to resolve the Value for Get Data")
		);

		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}
	else
	{
		P_NATIVE_BEGIN;
			if (Data != nullptr && Data->RowStruct.IsValid() && Data->LoadData())
			{
				ValueProp->Struct->CopyScriptStruct(ValuePtr, Data->RowStruct.GetMemory());
				ExecResult = EExternalDataResult::Valid;
			}
			else
			{
				ExecResult = EExternalDataResult::NotValid;
			}
		P_NATIVE_END;
	}
}

#undef LOCTEXT_NAMESPACE
