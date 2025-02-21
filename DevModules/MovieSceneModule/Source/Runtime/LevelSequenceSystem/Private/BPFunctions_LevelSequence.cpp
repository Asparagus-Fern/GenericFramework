// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions_LevelSequence.h"

#include "LevelSequenceHandle.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"
#include "LevelSequencePlayer.h"

ULevelSequenceHandle* UBPFunctions_LevelSequence::RegisterLevelSequenceHandle(FName HandleName, ULevelSequence* InLevelSequence, FMovieSceneSequencePlaybackSettings InSettings)
{
	ULevelSequenceHandle* NewHandle = nullptr;
	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		if (HandleManager->IsHandleRegister(HandleName))
		{
			NewHandle = HandleManager->GetHandle<ULevelSequenceHandle>(HandleName);
			NewHandle->CloseMovieScene();
		}
		else
		{
			NewHandle = HandleManager->RegisterHandle<ULevelSequenceHandle>(HandleName);
		}

		ALevelSequenceActor* LevelSequenceActor = nullptr;
		ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(NewHandle, InLevelSequence, InSettings, LevelSequenceActor);

		NewHandle->LevelSequenceActor = LevelSequenceActor;
		NewHandle->LevelSequencePlayer = LevelSequencePlayer;

		NewHandle->OpenMovieScene();
	}
	return NewHandle;
}
