// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "PropertyType.generated.h"

/**
 * Reason Why Cause Property Changed
 */
UENUM(BlueprintType)
enum class EPropertyChangeReason : uint8
{
	/* Property Is Changed */
	Change,

	/* Property Dependency Changed */
	DependencyChanged,

	/* Property Is Reset To Default */
	ResetToDefault,

	/* Property Is Reset To Initial */
	ResetToInitial,
};
