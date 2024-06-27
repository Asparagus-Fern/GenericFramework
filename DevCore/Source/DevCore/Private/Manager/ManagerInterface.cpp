// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/ManagerInterface.h"

FText IManagerInterface::GetManagerDisplayName()
{
	return FText::GetEmpty();
}

bool IManagerInterface::IsEditorManager()
{
	return DoesSupportWorldType(EWorldType::Editor);
}

bool IManagerInterface::DoesSupportWorldType(EWorldType::Type InWorldType)
{
	return InWorldType == EWorldType::Game || InWorldType == EWorldType::PIE || InWorldType == EWorldType::GamePreview || InWorldType == EWorldType::GameRPC;
}
