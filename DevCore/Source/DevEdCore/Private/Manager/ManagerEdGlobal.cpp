// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerEdGlobal.h"

#include "Manager/ManagerEdSubsystem.h"

UWorld* FManagerEdGlobal::GetEditorWorld()
{
	return UManagerEdSubsystem::Get()->GetWorld();
}
