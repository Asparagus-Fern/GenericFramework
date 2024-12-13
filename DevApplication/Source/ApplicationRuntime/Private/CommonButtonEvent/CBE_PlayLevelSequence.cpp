// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_PlayLevelSequence.h"

#include "LevelSequenceActor.h"
#include "LevelSequenceManager.h"
#include "LevelSequencePlayer.h"
#include "Manager/ManagerStatics.h"

bool UCBE_PlayLevelSequence::CanExecuteButtonEvent_Implementation()
{
	return SequenceID != NAME_None;
}

void UCBE_PlayLevelSequence::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (ULevelSequenceManager* LevelSequenceManager = GetManager<ULevelSequenceManager>())
	{
		bool bIsSequenceHandleValid = true;
		FLevelSequenceHandle LevelSequenceHandle;

		/* Not Exist, Register New Level Sequence Handle */
		if (!LevelSequenceManager->ExistLevelSequenceHandle(SequenceID))
		{
			if (!Sequence)
			{
				DLOG(DLogMovieScene, Warning, TEXT("Try To Register New Level Sequence Handle Fail"))
				bIsSequenceHandleValid = false;
			}
			else
			{
				LevelSequenceManager->RegisterLevelSequence(SequenceID, Sequence, LevelSequenceHandle);
			}
		}
		/* Exist, Get Level Sequence Handle By ID */
		else
		{
			LevelSequenceManager->GetLevelSequenceHandle(SequenceID, LevelSequenceHandle);
		}

		/* The Level Sequence That Current Play Is Not Same As Last One */
		if (Sequence && LevelSequenceHandle.LevelSequenceActor->LevelSequenceAsset != Sequence)
		{
			LevelSequenceHandle.LevelSequenceActor->SetSequence(Sequence);
		}

		/* Set The New Playback Settings */
		if (bNewSequencePlaybackSettings)
		{
			LevelSequenceHandle.LevelSequencePlayer->SetPlaybackSettings(Settings);
		}

		/* IsValid To Operate The Level Sequence Handle */
		if (bIsSequenceHandleValid)
		{
			if (bIsAsync)
			{
				LevelSequenceHandle.LevelSequencePlayer->OnPause.AddDynamic(this, &UCBE_PlayLevelSequence::OnLevelSequenceFinish);
				LevelSequenceHandle.LevelSequencePlayer->OnStop.AddDynamic(this, &UCBE_PlayLevelSequence::OnLevelSequenceFinish);
				LevelSequenceHandle.LevelSequencePlayer->OnFinished.AddDynamic(this, &UCBE_PlayLevelSequence::OnLevelSequenceFinish);
			}

			LevelSequenceHandle.LevelSequencePlayer->Play();
		}
	}

	if (!bIsAsync)
	{
		MarkAsActivedFinish();
	}
}

void UCBE_PlayLevelSequence::OnLevelSequenceFinish()
{
	if (ULevelSequenceManager* LevelSequenceManager = GetManager<ULevelSequenceManager>())
	{
		FLevelSequenceHandle LevelSequenceHandle;
		if (LevelSequenceManager->GetLevelSequenceHandle(SequenceID, LevelSequenceHandle))
		{
			LevelSequenceHandle.LevelSequencePlayer->OnPause.RemoveAll(this);
			LevelSequenceHandle.LevelSequencePlayer->OnStop.RemoveAll(this);
			LevelSequenceHandle.LevelSequencePlayer->OnFinished.RemoveAll(this);
		}
	}

	MarkAsActivedFinish();
}
