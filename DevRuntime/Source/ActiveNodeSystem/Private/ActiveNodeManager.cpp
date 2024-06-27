// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNodeManager.h"

#include "ActiveNodeSubsystem.h"

#define LOCTEXT_NAMESPACE "UActiveNodeManager"

UActiveNodeManager::UActiveNodeManager()
{
	bAutoLogin = true;
	bBlockUpdate = false;
}

FText UActiveNodeManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Active Node Manager");
}

#undef LOCTEXT_NAMESPACE
