// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "GenericLevelSequenceSubsystem.h"

#include "GenericLevelSequenceHandle.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneType.h"
#include "Type/DebugType.h"

UGenericLevelSequenceSubsystem* UGenericLevelSequenceSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

UGenericLevelSequenceHandle* UGenericLevelSequenceSubsystem::RegisterLevelSequenceHandle(ULevelSequence* InLevelSequence, const FMovieSceneSequencePlaybackSettings& InSettings)
{
	if (!IsValid(InLevelSequence))
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("InLevelSequence Is InValid"))
		return nullptr;
	}

	UGenericLevelSequenceHandle* NewHandle = NewObject<UGenericLevelSequenceHandle>(this);

	ALevelSequenceActor* LevelSequenceActor = nullptr;
	ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(NewHandle, InLevelSequence, InSettings, LevelSequenceActor);

	NewHandle->LevelSequenceActor = LevelSequenceActor;
	NewHandle->LevelSequencePlayer = LevelSequencePlayer;
	LevelSequenceHandles.Add(NewHandle);

	return NewHandle;
}

void UGenericLevelSequenceSubsystem::UnRegisterLevelSequenceHandle(UGenericLevelSequenceHandle* InHandle)
{
	if (LevelSequenceHandles.Contains(InHandle))
	{
		if (InHandle->IsPlaying())
		{
			InHandle->CloseMovieScene();
		}

		LevelSequenceHandles.Remove(InHandle);
	}
}
