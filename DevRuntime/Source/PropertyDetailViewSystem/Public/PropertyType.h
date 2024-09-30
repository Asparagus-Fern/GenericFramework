// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "PropertyType.generated.h"

#define GET_PROPERTY_FUNCTION_PATH(GetTargetObjectClassName,GetTargetObjectFunctionName,TargetClassName,TargetFunctionOrProperty) \
MakeShared<FPropertyDataSouceDynamic>( \
	TArray<FString>({ \
		GET_FUNCTION_NAME_STRING_CHECKED(GetTargetObjectClassName, GetTargetObjectFunctionName), \
		GET_FUNCTION_NAME_STRING_CHECKED(TargetClassName, TargetFunctionOrProperty) \
	}) \
)

/**
 * 
 */
enum class EPropertyChangeReason : uint8
{
	Change,
	DependencyChanged,
	ResetToDefault,
	RestoreToInitial,
};