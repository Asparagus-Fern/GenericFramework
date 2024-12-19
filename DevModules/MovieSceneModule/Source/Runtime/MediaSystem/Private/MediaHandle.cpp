// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaHandle.h"

#include "IMediaModule.h"
#include "MediaManager.h"
#include "MediaPlayer.h"
#include "Manager/ManagerStatics.h"

void UMediaHandle::ClearHandle_Implementation()
{
	Super::ClearHandle_Implementation();
}

void UMediaHandle::LoadMovieSceneDataSource_Implementation()
{
	MediaPlayer->OpenPlaylist(MediaPlaylist);

	if (!MediaPlayer->OnEndReached.Contains(this, "OnEndReached"))
	{
		MediaPlayer->OnEndReached.AddDynamic(this, &UMediaHandle::OnEndReached);
	}
	
	// IMediaModule* MediaModule = FModuleManager::LoadModulePtr<IMediaModule>("Media");
	// MediaModule->GetPlayerFactory(MediaPlayer->GetGuid());
}

void UMediaHandle::Play_Implementation()
{
	MediaPlayer->OpenPlaylist(MediaPlaylist);
	MediaPlayer->Play();
}

void UMediaHandle::Pause_Implementation()
{
	MediaPlayer->Pause();
}

void UMediaHandle::Stop_Implementation()
{
	MediaPlayer->Close();
}

void UMediaHandle::Seek_Implementation(FTimespan InTime)
{
	MediaPlayer->Seek(InTime);
}

void UMediaHandle::SetMovieSceneLoopSetting_Implementation(FMovieSceneLoopSetting InMovieSceneLoopSetting)
{
	if (MovieSceneSetting.MovieSceneLoopSetting.bEnableLoop != InMovieSceneLoopSetting.bEnableLoop)
	{
		MediaPlayer->SetLooping(InMovieSceneLoopSetting.bEnableLoop);
	}
}

FTimespan UMediaHandle::GetTime()
{
	return MediaPlayer->GetTime();
}

void UMediaHandle::OnEndReached()
{
	Execute_OnMovieSceneFinish(this);
}
