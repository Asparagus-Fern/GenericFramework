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
