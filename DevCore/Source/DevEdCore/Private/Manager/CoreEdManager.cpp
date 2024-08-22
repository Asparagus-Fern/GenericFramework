// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreEdManager.h"

bool UCoreEdManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}
