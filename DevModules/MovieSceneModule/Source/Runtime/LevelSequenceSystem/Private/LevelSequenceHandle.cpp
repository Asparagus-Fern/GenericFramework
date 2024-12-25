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

void ULevelSequenceHandle::OpenMovieScene_Implementation()
{
	Super::OpenMovieScene_Implementation();
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

void ULevelSequenceHandle::Seek_Implementation(int32 InDays, int32 InHours, int32 InMinutes, int32 InSeconds, int32 InMicroSeconds)
{
	Super::Seek_Implementation(InDays, InHours, InMinutes, InSeconds, InMicroSeconds);
}

FTimespan ULevelSequenceHandle::GetMovieSceneCurrentTime_Implementation()
{
	// LevelSequencePlayer->GetCurrentTime();
	return Super::GetMovieSceneCurrentTime_Implementation();
}