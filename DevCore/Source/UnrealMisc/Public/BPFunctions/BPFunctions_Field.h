// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Type/DebugType.h"
#include "Type/FieldType.h"
#include "UObject/PropertyAccessUtil.h"
#include "BPFunctions_Field.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMISC_API UBPFunctions_Field : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static bool GetBooleanValue(const UObject* Target, const FName& PropertyName, bool& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetBooleanValue(UObject* Target, const FName& PropertyName, bool Value);

	UFUNCTION(BlueprintPure)
	static bool GetIntegerValue(const UObject* Target, const FName& PropertyName, int32& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetIntegerValue(UObject* Target, const FName& PropertyName, int32 Value);

	UFUNCTION(BlueprintPure)
	static bool GetInteger64Value(const UObject* Target, const FName& PropertyName, int64& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetInteger64Value(UObject* Target, const FName& PropertyName, int64 Value);

	UFUNCTION(BlueprintPure)
	static bool GetFloatValue(const UObject* Target, const FName& PropertyName, float& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetFloatValue(UObject* Target, const FName& PropertyName, float Value);

	UFUNCTION(BlueprintPure)
	static bool GetDoubleValue(const UObject* Target, const FName& PropertyName, double& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetDoubleValue(UObject* Target, const FName& PropertyName, double Value);

	UFUNCTION(BlueprintPure)
	static bool GetNameValue(const UObject* Target, const FName& PropertyName, FName& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetNameValue(UObject* Target, const FName& PropertyName, FName Value);

	UFUNCTION(BlueprintPure)
	static bool GetStringValue(const UObject* Target, const FName& PropertyName, FString& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetStringValue(UObject* Target, const FName& PropertyName, FString Value);

	UFUNCTION(BlueprintPure)
	static bool GetTextValue(const UObject* Target, const FName& PropertyName, FText& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetTextValue(UObject* Target, const FName& PropertyName, FText Value);

	UFUNCTION(BlueprintPure)
	static bool GetVectorValue(const UObject* Target, const FName& PropertyName, FVector& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetVectorValue(UObject* Target, const FName& PropertyName, FVector Value);

	UFUNCTION(BlueprintPure)
	static bool GetRotatorValue(const UObject* Target, const FName& PropertyName, FRotator& Value);

	UFUNCTION(BlueprintCallable)
	static bool SetRotatorValue(UObject* Target, const FName& PropertyName, FRotator Value);

public:
	template <typename T>
	static bool GetValueOfType(const UObject* Target, const FName& PropertyName, T& OutValue)
	{
		const FProperty* NamedProperty = PropertyAccessUtil::FindPropertyByName(PropertyName, Target->GetClass());
		if (nullptr == NamedProperty)
		{
			GenericLOG(GenericLogField, Error, TEXT("Find Null Property Named: %s"), *(PropertyName.ToString()));
			return false;
		}

		const T* TempValue = NamedProperty->ContainerPtrToValuePtr<T>(Target);
		if (TempValue)
		{
			OutValue = *TempValue;
			return true;
		}

		return false;
	}

	template <typename T>
	static bool SetValueOfType(UObject* Target, const FName& PropertyName, T InValue)
	{
		const FProperty* NamedProperty = PropertyAccessUtil::FindPropertyByName(PropertyName, Target->GetClass());
		if (nullptr == NamedProperty)
		{
			GenericLOG(GenericLogField, Error, TEXT("Find Null Property Named: %s"), *(PropertyName.ToString()));
			return false;
		}

		T* TargetPropertyAddress = NamedProperty->ContainerPtrToValuePtr<T>(Target);
		if (TargetPropertyAddress)
		{
			*TargetPropertyAddress = InValue;
			return true;
		}

		return false;
	}

public:
	UFUNCTION(BlueprintCallable, CustomThunk, DisplayName="Set Property Value", meta=(DefaultToSelf="TargetObject", CustomStructureParam = "Value", BlueprintInternalUseOnly))
	static void SetPropertyValue(const UObject* TargetObject, FName PropertyName, const int32& Value);
	static void Generic_SetPropertyValue(UObject* TargetObject, const FProperty* TargetProperty, void* SourceValuePtr);
	DECLARE_FUNCTION(execSetPropertyValue);
};
