// Fill out your copyright notice in the Description page of Project Settings.


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

bool UManagerSetting::GetEnableManager() const
{
	return bEnableManager && UGlobalManagerSetting::Get()->bEnableAllManager;
}

#undef LOCTEXT_NAMESPACE
