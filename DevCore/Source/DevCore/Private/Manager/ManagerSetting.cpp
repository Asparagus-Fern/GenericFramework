// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/ManagerSetting.h"

#include "Manager/GlobalManagerSetting.h"

#define LOCTEXT_NAMESPACE "UManagerSetting"

FName UManagerSetting::GetContainerName() const
{
	return "Developer";
}

FName UManagerSetting::GetCategoryName() const
{
	return "Runtime";
}

FName UManagerSetting::GetSectionName() const
{
	return Super::GetSectionName();
}

#undef LOCTEXT_NAMESPACE
