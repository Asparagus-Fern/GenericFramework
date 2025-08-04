// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_Property.h"

#include "Blueprint/BlueprintExceptionInfo.h"

#define LOCTEXT_NAMESPACE "FPropertyUtilitiesModule"

bool UBPFunctions_Property::GetBooleanValue(const UObject* Target, const FName& PropertyName, bool& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetBooleanValue(UObject* Target, const FName& PropertyName, bool Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetIntegerValue(const UObject* Target, const FName& PropertyName, int32& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetIntegerValue(UObject* Target, const FName& PropertyName, int32 Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetInteger64Value(const UObject* Target, const FName& PropertyName, int64& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetInteger64Value(UObject* Target, const FName& PropertyName, int64 Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetFloatValue(const UObject* Target, const FName& PropertyName, float& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetFloatValue(UObject* Target, const FName& PropertyName, float Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetDoubleValue(const UObject* Target, const FName& PropertyName, double& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetDoubleValue(UObject* Target, const FName& PropertyName, double Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetNameValue(const UObject* Target, const FName& PropertyName, FName& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetNameValue(UObject* Target, const FName& PropertyName, FName Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetStringValue(const UObject* Target, const FName& PropertyName, FString& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetStringValue(UObject* Target, const FName& PropertyName, FString Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetTextValue(const UObject* Target, const FName& PropertyName, FText& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetTextValue(UObject* Target, const FName& PropertyName, FText Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetVectorValue(const UObject* Target, const FName& PropertyName, FVector& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetVectorValue(UObject* Target, const FName& PropertyName, FVector Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::GetRotatorValue(const UObject* Target, const FName& PropertyName, FRotator& Value)
{
	return GetValueOfType(Target, PropertyName, Value);
}

bool UBPFunctions_Property::SetRotatorValue(UObject* Target, const FName& PropertyName, FRotator Value)
{
	return SetValueOfType(Target, PropertyName, Value);
}

void UBPFunctions_Property::SetPropertyValue(const UObject* TargetObject, FName PropertyName, const int32& Value)
{
	// We should never hit this! Stubbed to avoid NoExport on the class.
	check(0);
}

void UBPFunctions_Property::Generic_SetPropertyValue(UObject* TargetObject, const FProperty* TargetProperty, void* SourceValuePtr)
{
	TargetProperty->SetValue_InContainer(TargetObject, SourceValuePtr);
}

DEFINE_FUNCTION(UBPFunctions_Property::execSetPropertyValue)
{
	P_GET_OBJECT(UObject, TargetObject)
	P_GET_PROPERTY(FNameProperty, PropertyName)

	if (!IsValid(TargetObject))
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			LOCTEXT("MissingTarget", "Failed to Resolve the Target For SetPropertyValue.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
		return;
	}

	if (PropertyName == NAME_None)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			LOCTEXT("MissingPropertyName", "Failed to Resolve the PropertyName For SetPropertyValue.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
		return;
	}

	const FProperty* TargetProperty = nullptr;
	for (TFieldIterator<FProperty> PropertyIt(TargetObject->GetClass()); PropertyIt; ++PropertyIt)
	{
		const FProperty* Property = *PropertyIt;
		if (Property->GetName() == PropertyName)
		{
			TargetProperty = Property;
			break;
		}
	}

	if (!TargetProperty)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			LOCTEXT("MissingTargetProperty", "Failed to Find Property In Target.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
		return;
	}

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FProperty>(nullptr);
	const FProperty* SourceProperty = CastField<FProperty>(Stack.MostRecentProperty);
	void* SourceValuePtr = Stack.MostRecentPropertyAddress;

	if (!TargetProperty->SameType(SourceProperty))
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("InValidPropertyType", "TargetProperty Is Not Same As SourceProperty.")
		);

		GenericLOG(GenericLogProperty, Error, TEXT("TargetProperty Is Not Same As SourceProperty."))
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
		return;
	}

	if (!SourceProperty || !SourceValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("InValidProperty", "Failed to Resolve the Property For SetPropertyValue.")
		);

		GenericLOG(GenericLogProperty, Error, TEXT("Failed to Resolve the Property For SetPropertyValue."))
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
		return;
	}

	P_FINISH;

	P_NATIVE_BEGIN
		P_THIS->Generic_SetPropertyValue(TargetObject, TargetProperty, SourceValuePtr);
	P_NATIVE_END
}

#undef LOCTEXT_NAMESPACE
