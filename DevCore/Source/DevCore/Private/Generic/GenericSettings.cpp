// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Generic/GenericSettings.h"

#define LOCTEXT_NAMESPACE "UManagerSetting"

FName UGenericSettings::GetContainerName() const
{
	return "Developer";
}

FName UGenericSettings::GetCategoryName() const
{
	return "Runtime";
}

FName UGenericSettings::GetSectionName() const
{
	return Super::GetSectionName();
}

#undef LOCTEXT_NAMESPACE
