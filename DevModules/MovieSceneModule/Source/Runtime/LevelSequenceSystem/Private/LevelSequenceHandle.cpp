// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelSequenceHandle.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

ULevelSequenceHandle* ULevelSequenceHandle::Register(FName HandleName)
{
	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		return HandleManager->RegisterHandle<ULevelSequenceHandle>(HandleName);
	}
	return nullptr;
}
