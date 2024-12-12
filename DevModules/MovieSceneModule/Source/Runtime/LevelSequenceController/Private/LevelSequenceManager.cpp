// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceManager.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

bool ULevelSequenceManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void ULevelSequenceManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void ULevelSequenceManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool ULevelSequenceManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

bool ULevelSequenceManager::RegisterLevelSequence(FName SequenceID, ULevelSequence* InSequence, FLevelSequenceHandle& LevelSequenceHandle)
{
	if (LevelSequenceHandles.Contains(SequenceID))
	{
		DLOG(DLogMovieScene, Warning, TEXT("SequenceID Is Already Register"))
		return false;
	}

	if (!IsValid(InSequence) || SequenceID == NAME_None)
	{
		DLOG(DLogMovieScene, Error, TEXT("SequenceID / InSequence Is NULL"))
		return false;
	}

	ALevelSequenceActor* LevelSequenceActor = nullptr;
	ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(this, InSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

	if (!IsValid(LevelSequenceActor) || !IsValid(LevelSequencePlayer))
	{
		DLOG(DLogMovieScene, Error, TEXT("CreateLevelSequencePlayer Fail"))
		return false;
	}

	const FLevelSequenceHandle NewLevelSequenceHandle = FLevelSequenceHandle(SequenceID, LevelSequenceActor, LevelSequencePlayer);
	LevelSequenceHandle = NewLevelSequenceHandle;
	LevelSequenceHandles.Add(NewLevelSequenceHandle);

	return true;
}

void ULevelSequenceManager::UnRegisterLevelSequence(FName SequenceID)
{
	if (LevelSequenceHandles.Contains(SequenceID))
	{
		DLOG(DLogMovieScene, Warning, TEXT("SequenceID Is Already Register"))
		return;
	}

	const FLevelSequenceHandle* Found = LevelSequenceHandles.FindByKey(SequenceID);
	LevelSequenceHandles.Remove(*Found);
}

// void ULevelSequenceManager::SetLevelSequence(ULevelSequence* InLevelSequence)
// {
// 	if (!IsValid(InLevelSequence))
// 	{
// 		return;
// 	}
//
// 	InitializeLevelSequence(InLevelSequence);
//
// 	if (IsValid(LevelSequenceActor))
// 	{
// 		LevelSequenceActor->SetSequence(InLevelSequence);
// 	}
// }
//
// void ULevelSequenceManager::SetSequencePlaybackSettings(FMovieSceneSequencePlaybackSettings InSettings)
// {
// 	if (IsValid(LevelSequencePlayer))
// 	{
// 		LevelSequencePlayer->SetPlaybackSettings(InSettings);
// 	}
// }
//
// void ULevelSequenceManager::InitializeLevelSequence(ULevelSequence* InLevelSequence)
// {
// 	if (!IsValid(InLevelSequence))
// 	{
// 		return;
// 	}
//
// 	if (!LevelSequenceActor && !LevelSequencePlayer)
// 	{
// 		FMovieSceneSequencePlaybackSettings Settings = FMovieSceneSequencePlaybackSettings();
// 		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), InLevelSequence, Settings, LevelSequenceActor);
// 	}
// }
