// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleMedia.h"

#include "MediaHandle.h"
#include "MediaManager.h"
#include "MediaPlayer.h"
#include "Manager/ManagerStatics.h"
#include "Widget/MovieScenePanel.h"

UCBE_HandleMedia::UCBE_HandleMedia(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> DefaultMediaPlayer(TEXT("/Script/MediaAssets.MediaPlayer'/MovieSceneModule/Media/MP_Media.MP_Media'"));
	MediaPlayer = DefaultMediaPlayer.Object;
}

bool UCBE_HandleMedia::CanExecuteButtonEvent_Implementation()
{
	return IsValid(MediaPlayer);
}

void UCBE_HandleMedia::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (UMediaManager* MediaManager = GetManager<UMediaManager>())
	{
		if (UMediaHandle* MediaHandle = MediaManager->RegisterMedia(MediaPlayer, MediaSources))
		{
			IMovieSceneInterface::Execute_SetMovieSceneSetting(MediaHandle, MovieSceneSetting);
		}
	}

	if (!bIsAsync)
	{
		MarkAsActivedFinish();
	}
}
