// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_Json.h"

#include "JsonConvert.h"
#include "GenericJsonObject.h"
#include "JsonObjectConverter.h"
#include "JsonType.h"
#include "Blueprint/BlueprintExceptionInfo.h"

#define LOCTEXT_NAMESPACE "FGenericJsonModule"

FJsonObjectConverter::CustomExportCallback EnumOverrideExportCallback;

bool UBPFunctions_Json::GetJsonField(UGenericJsonObject* JsonObject, const FString& FieldName, int32& OutValue)
{
	if (!IsValid(JsonObject))
	{
		return false;
	}

	if (FieldName.IsEmpty())
	{
		return false;
	}

	return true;
}

DEFINE_FUNCTION(UBPFunctions_Json::execGetJsonField)
{
	P_GET_OBJECT_REF(UGenericJsonObject, JsonObject);
	P_GET_PROPERTY(FStrProperty, FieldName);

	Stack.StepCompiledIn<FProperty>(nullptr);
	FProperty* ValueProp = Stack.MostRecentProperty;
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;

	if (!ValueProp || !ValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AccessViolation,LOCTEXT("GetJsonField_MissingOutputProperty", "Failed to resolve the output parameter for GetJsonField."));
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}

	bool bResult;
	if (FieldName.IsEmpty())
	{
		const FStructProperty* StructProperty = static_cast<FStructProperty*>(ValueProp);
		if (!StructProperty)
		{
			bResult = false;
			*StaticCast<bool*>(RESULT_PARAM) = bResult;
			return;
		}

		P_NATIVE_BEGIN
			bResult = FJsonObjectConverter::JsonObjectToUStruct(JsonObject->GetJsonObject().ToSharedRef(), StructProperty->Struct, ValuePtr);
		P_NATIVE_END
		*StaticCast<bool*>(RESULT_PARAM) = bResult;
		return;
	}

	P_NATIVE_BEGIN
		bResult = JsonFieldToProperty(FieldName, JsonObject, ValueProp, ValuePtr);
	P_NATIVE_END

	*static_cast<bool*>(RESULT_PARAM) = bResult;
}

bool UBPFunctions_Json::SetJsonField(UGenericJsonObject* JsonObject, const FString& FieldName, const int32& Value)
{
	if (!IsValid(JsonObject))
	{
		return false;
	}

	if (FieldName.IsEmpty())
	{
		return false;
	}

	return true;
}

DEFINE_FUNCTION(UBPFunctions_Json::execSetJsonField)
{
	P_GET_ENUM_REF(EGenericResult, Result);
	P_GET_OBJECT_REF(UGenericJsonObject, JsonObject);
	P_GET_PROPERTY(FStrProperty, FieldName);

	Stack.StepCompiledIn<FProperty>(nullptr);
	FProperty* SourceProperty = Stack.MostRecentProperty;
	void* SourceValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;

	if (!SourceProperty || !SourceValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			LOCTEXT("SetField_MissingInputProperty", "Failed to resolve the input parameter for SetField.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}

	bool bResult;
	if (FieldName.IsEmpty())
	{
		FStructProperty* StructProperty = CastField<FStructProperty>(SourceProperty);
		if (!StructProperty)
		{
			bResult = false;
			*StaticCast<bool*>(RESULT_PARAM) = bResult;
			return;
		}

		P_NATIVE_BEGIN
			bResult = FJsonObjectConverter::UStructToJsonObject(StructProperty->Struct, SourceValuePtr, JsonObject->GetJsonObject().ToSharedRef());
		P_NATIVE_END
	}
	else
	{
		P_NATIVE_BEGIN
			bResult = PropertyToJsonField(FieldName, SourceProperty, SourceValuePtr, JsonObject);
		P_NATIVE_END
	}

	// If successful, refresh the stored JsonString
	P_NATIVE_BEGIN
		if (bResult)
		{
			FString JsonString;
			if (!JsonObject->EncodeJson(JsonString))
			{
				FFrame::KismetExecutionMessage(TEXT("Error serializing JSON Object."), ELogVerbosity::Error);
				bResult = false;
			}
		}
	P_NATIVE_END

	*StaticCast<bool*>(RESULT_PARAM) = bResult;
}

void UBPFunctions_Json::SaveStructToJsonFile(EGenericResult& Result, const FString& FilePath, const int32& Value)
{
}

DEFINE_FUNCTION(UBPFunctions_Json::execSaveStructToJsonFile)
{
	P_GET_ENUM_REF(EGenericResult, Result);
	P_GET_PROPERTY(FStrProperty, FilePath);

	Stack.StepCompiledIn<FStructProperty>(nullptr);
	FProperty* Property = Stack.MostRecentProperty;
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;

	Result = EGenericResult::InValid;

	if (!Property || !ValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			LOCTEXT("SetField_MissingInputProperty", "Failed to resolve the input parameter.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}

	const FStructProperty* StructProperty = CastField<FStructProperty>(Property);
	if (!StructProperty)
	{
		GenericLOG(GenericLogJson, Error, TEXT("Invalid Struct Property"));
		return;
	}

	P_NATIVE_BEGIN;
		if (FJsonConvert::StructToJsonFile(FilePath, StructProperty->Struct, ValuePtr))
		{
			Result = EGenericResult::Valid;
		}
		else
		{
			Result = EGenericResult::InValid;
		}
	P_NATIVE_END;
}

void UBPFunctions_Json::LoadJsonFileToStruct(EGenericResult& Result, const FString& FilePath, int32& Value)
{
}

DEFINE_FUNCTION(UBPFunctions_Json::execLoadJsonFileToStruct)
{
	P_GET_ENUM_REF(EGenericResult, Result);
	P_GET_PROPERTY(FStrProperty, FilePath);

	Stack.StepCompiledIn<FStructProperty>(nullptr);
	FProperty* Property = Stack.MostRecentProperty;
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;

	Result = EGenericResult::InValid;

	if (!Property || !ValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			LOCTEXT("SetField_MissingInputProperty", "Failed to resolve the input parameter.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}

	const FStructProperty* StructProperty = CastField<FStructProperty>(Property);
	if (!StructProperty)
	{
		GenericLOG(GenericLogJson, Error, TEXT("Invalid Struct Property"));
		return;
	}

	P_NATIVE_BEGIN;
		if (FJsonConvert::JsonFileToStruct(FilePath, StructProperty->Struct, ValuePtr))
		{
			Result = EGenericResult::Valid;
		}
		else
		{
			Result = EGenericResult::InValid;
		}
	P_NATIVE_END;
}

bool UBPFunctions_Json::JsonFieldToProperty(const FString& FieldName, UGenericJsonObject* SourceObject, FProperty* TargetProperty, void* TargetValuePtr)
{
	check(SourceObject->GetJsonObject().IsValid());
	check(TargetProperty && TargetValuePtr);

	// Check that field with name exists
	const TSharedPtr<FJsonValue> JsonValue = SourceObject->GetJsonObject()->TryGetField(FieldName);
	if (!JsonValue.IsValid())
	{
		FFrame::KismetExecutionMessage(*FString::Printf(TEXT("Field '%s' was not found on the provided JSON object."), *FieldName), ELogVerbosity::Warning);
		return false;
	}

	return FJsonObjectConverter::JsonValueToUProperty(JsonValue, TargetProperty, TargetValuePtr);
}

bool UBPFunctions_Json::PropertyToJsonField(const FString& FieldName, FProperty* SourceProperty, const void* SourceValuePtr, UGenericJsonObject*& TargetObject)
{
	check(SourceProperty && SourceValuePtr);

	if (!TargetObject->GetJsonObject().IsValid())
	{
		TargetObject->GetJsonObject() = MakeShared<FJsonObject>();
	}

	TargetObject->GetJsonObject()->SetField(FieldName, FJsonObjectConverter::UPropertyToJsonValue(SourceProperty, SourceValuePtr));
	return true;
}

#undef LOCTEXT_NAMESPACE
