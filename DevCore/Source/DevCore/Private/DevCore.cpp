// Copyright Epic Games, Inc. All Rights Reserved.

#include "DevCore.h"

#include "Input/InputManager.h"
#include "Pawn/PawnManager.h"
#include "Procedure/ProcedureManager.h"

#define LOCTEXT_NAMESPACE "FDevCoreModule"

void FDevCoreModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevCoreModule, DevCore)
