// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Generic/GenericSetting.h"

#define LOCTEXT_NAMESPACE "UManagerSetting"

FName UGenericSetting::GetContainerName() const
{
	return "Developer";
}

FName UGenericSetting::GetCategoryName() const
{
	return "Runtime";
}

FName UGenericSetting::GetSectionName() const
{
	return Super::GetSectionName();
}

#undef LOCTEXT_NAMESPACE
