// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDataSource.h"
#include "PropertyPathHelpers.h"

namespace RequiredPropertyPath
{
	template <typename ArgType0, typename ArgType1>
	TArray<FString> MakeRequiredArgs(ArgType0 InArg0, ArgType1 InArg1)
	{
		return {((void)sizeof(InArg0), InArg1)};
	}

	template <typename ArgType0, typename ArgType1, typename ArgType2, typename ArgType3>
	TArray<FString> MakeRequiredArgs(ArgType0 InArg0, ArgType1 InArg1, ArgType2 InArg2, ArgType3 InArg3)
	{
		return {((void)sizeof(InArg0), InArg1), ((void)sizeof(InArg2), InArg3)};
	}

	template <typename ArgType0, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5>
	FString MakeRequiredArgs(ArgType0 InArg0, ArgType1 InArg1, ArgType2 InArg2, ArgType3 InArg3, ArgType4 InArg4, ArgType5 InArg5)
	{
		return {((void)sizeof(InArg0), InArg1), ((void)sizeof(InArg2), InArg3), ((void)sizeof(InArg4), InArg5)};
	}

	template <typename ArgType0, typename ArgType1, typename ArgType2, typename ArgType3, typename ArgType4, typename ArgType5, typename ArgType6, typename ArgType7>
	FString MakeRequiredArgs(ArgType0 InArg0, ArgType1 InArg1, ArgType2 InArg2, ArgType3 InArg3, ArgType4 InArg4, ArgType5 InArg5, ArgType6 InArg6, ArgType7 InArg7)
	{
		return {((void)sizeof(InArg0), InArg1), ((void)sizeof(InArg2), InArg3), ((void)sizeof(InArg4), InArg5), ((void)sizeof(InArg6), InArg7)};
	}
}

#define GET_PROPERTY_FUNCTION_PATH(...) \
	MakeShared<FPropertyDataSouceDynamic>(RequiredPropertyPath::MakeRequiredArgs(__VA_ARGS__))

#define PATH(ClassName, PropertyName) \
	&##ClassName::##PropertyName, #PropertyName


/**
 * 
 */
class PROPERTYDETAILVIEWSYSTEM_API FPropertyDataSouceDynamic : public FPropertyDataSource
{
public:
	FPropertyDataSouceDynamic(const TArray<FString>& InDynamicPath);

	virtual bool Resolve(UObject* InContext) override;

	virtual FString GetValueAsString(UObject* InContext) const override;

	virtual void SetValue(UObject* InContext, const FString& Value) override;

	virtual FString ToString() const override;

private:
	FCachedPropertyPath DynamicPath;
};
