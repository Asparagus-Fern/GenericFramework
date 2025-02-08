// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions_Property.h"

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
