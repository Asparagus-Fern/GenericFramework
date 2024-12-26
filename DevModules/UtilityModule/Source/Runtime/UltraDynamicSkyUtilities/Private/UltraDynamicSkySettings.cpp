// Fill out your copyright notice in the Description page of Project Settings.


#include "UltraDynamicSkySettings.h"

#define LOCTEXT_NAMESPACE "UUltraDynamicSkySettings"

FName UUltraDynamicSkySettings::GetContainerName() const
{
	return "Developer";
}

FName UUltraDynamicSkySettings::GetCategoryName() const
{
	return "Utility";
}

FName UUltraDynamicSkySettings::GetSectionName() const
{
	return Super::GetSectionName();
}

#undef LOCTEXT_NAMESPACE
