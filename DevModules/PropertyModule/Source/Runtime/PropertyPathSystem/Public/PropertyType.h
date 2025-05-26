// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "PropertyType.generated.h"

/**
 * 属性变更原因
 */
enum class EPropertyChangeReason : uint8
{
	/* 属性发生变更 */
	Change,

	/* 属性的依赖发生变更 */
	DependencyChanged,

	/* 属性需要重置为默认值 */
	ResetToDefault,

	/* 属性需要重置为发生变更之前的值 */
	RestoreToInitial,
};
