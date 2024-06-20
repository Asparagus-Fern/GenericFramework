// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/DebugManager.h"

#define LOCTEXT_NAMESPACE "UDebugManager"

UDebugManager::UDebugManager()
{
	DisplayName = LOCTEXT("DisplayName", "Debug Manager");
	ProcedureOrder = -99;
}

void UDebugManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

#undef LOCTEXT_NAMESPACE
