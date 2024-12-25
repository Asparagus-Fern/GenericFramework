// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleLevelSequence.h"

#include "LevelSequenceActor.h"
#include "LevelSequenceManager.h"
#include "LevelSequencePlayer.h"
#include "Manager/ManagerStatics.h"

bool UCBE_HandleLevelSequence::CanExecuteButtonEvent_Implementation()
{
	return IsValid(Sequence);
}

void UCBE_HandleLevelSequence::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (ULevelSequenceManager* LevelSequenceManager = GetManager<ULevelSequenceManager>())
	{
		if (ULevelSequenceHandle* LevelSequenceHandle = LevelSequenceManager->RegisterLevelSequence(Sequence))
		{
			/* Set The New Playback Settings */
			if (bNewSequencePlaybackSettings)
			{
				LevelSequenceHandle->LevelSequencePlayer->SetPlaybackSettings(Settings);
			}

			LevelSequenceHandle->OnPlayFinish.AddUObject(this, &UCBE_HandleLevelSequence::OnPlayFinish);

			IMovieSceneInterface::Execute_SetMovieSceneState(LevelSequenceHandle, MovieSceneState);
		}
	}

	if (!bIsAsync)
	{
		MarkAsActivedFinish();
	}
}

void UCBE_HandleLevelSequence::OnPlayFinish()
{
	if (bIsAsync)
	{
		MarkAsActivedFinish();
	}
}
