// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerEdSetting.h"

#define LOCTEXT_NAMESPACE "UManagerEdSetting"

FName UManagerEdSetting::GetCategoryName() const
{
	return "Editor";
}

#undef LOCTEXT_NAMESPACE
