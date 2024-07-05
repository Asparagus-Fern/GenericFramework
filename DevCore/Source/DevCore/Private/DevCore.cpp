// Copyright Epic Games, Inc. All Rights Reserved.

#include "DevCore.h"

#include "Input/InputManager.h"
#include "Pawn/PawnManager.h"
#include "Procedure/ProcedureManager.h"

#define LOCTEXT_NAMESPACE "FDevCoreModule"

void FDevCoreModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UProcedureManager::StaticClass());
	InRegisterManagerClasses.Add(UInputManager::StaticClass());
	InRegisterManagerClasses.Add(UPawnManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevCoreModule, DevCore)
