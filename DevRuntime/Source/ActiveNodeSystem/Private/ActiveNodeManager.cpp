// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNodeManager.h"

#include "ActiveNodeSubsystem.h"
#include "Manager/ManagerCollection.h"

#define LOCTEXT_NAMESPACE "UActiveNodeManager"

UActiveNodeManager::UActiveNodeManager()
{
	DisplayName = LOCTEXT("DisplayName", "Active Node Manager");
	ProcedureOrder = 0;

	bAutoLogin = true;
	bBlockUpdate = false;
}

#undef LOCTEXT_NAMESPACE
