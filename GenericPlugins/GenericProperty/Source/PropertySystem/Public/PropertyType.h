// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
// #include "PropertyType.generated.h"

PROPERTYSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogProperty, Log, All);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Property);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_PropertyOption);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_PropertyOption_Reset);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_PropertyProxy);

UENUM(BlueprintType)
enum class EPropertyChangedReason : uint8
{
	UserInput,
	Changed,
	DependencyChanged,
};
