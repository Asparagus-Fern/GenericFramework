// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/UCBE_StopLevelSequence.h"

#include "LevelSequenceManager.h"
#include "LevelSequencePlayer.h"
#include "Manager/ManagerStatics.h"

bool UUCBE_StopLevelSequence::CanExecuteButtonEvent_Implementation()
{
	return SequenceID != NAME_None;
}

void UUCBE_StopLevelSequence::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (ULevelSequenceManager* LevelSequenceManager = GetManager<ULevelSequenceManager>())
	{
		FLevelSequenceHandle LevelSequenceHandle;
		if (LevelSequenceManager->GetLevelSequenceHandle(SequenceID, LevelSequenceHandle))
		{
			LevelSequenceHandle.LevelSequencePlayer->Stop();
		}
	}
}
