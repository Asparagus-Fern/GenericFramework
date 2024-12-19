// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelSequenceHandle.h"

#include "LevelSequenceActor.h"
#include "LevelSequenceManager.h"
#include "LevelSequencePlayer.h"
#include "Manager/ManagerStatics.h"

void ULevelSequenceHandle::ClearHandle_Implementation()
{
	if (ULevelSequenceManager* LevelSequenceManager = GetManager<ULevelSequenceManager>())
	{
		LevelSequenceManager->UnRegisterLevelSequence(this);
	}
}

void ULevelSequenceHandle::LoadMovieSceneDataSource_Implementation()
{
	IMovieSceneInterface::LoadMovieSceneDataSource_Implementation();
}

void ULevelSequenceHandle::Play_Implementation()
{
	LevelSequencePlayer->Play();
}

void ULevelSequenceHandle::Pause_Implementation()
{
	LevelSequencePlayer->Pause();
}

void ULevelSequenceHandle::Stop_Implementation()
{
	LevelSequencePlayer->Stop();
}

void ULevelSequenceHandle::Seek_Implementation(FTimespan InTime)
{
}

FTimespan ULevelSequenceHandle::GetTime()
{
	// LevelSequencePlayer->GetCurrentTime()
	return FTimespan();
}
