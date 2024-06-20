// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/ManagerInterface.h"


bool IManagerInterface::IsSupportWorldType(const UWorld* InWorld)
{
	if (!IsValid(InWorld))
	{
		return false;
	}

	return InWorld->WorldType == EWorldType::Game || InWorld->WorldType == EWorldType::PIE || InWorld->WorldType == EWorldType::Editor;
}

bool IManagerInterface::IsWorldType(const EWorldType::Type InWorldType)
{
	return GetWorldType() == InWorldType;
}
