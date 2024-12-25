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

void UMediaHandle::OpenMovieScene_Implementation()
{
	Super::OpenMovieScene_Implementation();

	MediaPlayer->OpenPlaylist(MediaPlaylist);

	MediaPlayer->OnMediaOpened.AddDynamic(this, &UMediaHandle::OnMediaOpened);
	// MediaPlayer->OnEndReached.AddDynamic(this, &UMediaHandle::OnEndReached);
	MediaPlayer->OnPlaybackSuspended.AddDynamic(this, &UMediaHandle::OnPlaybackSuspended);
	MediaPlayer->OnSeekCompleted.AddDynamic(this, &UMediaHandle::OnSeekCompleted);
	MediaPlayer->OnMediaClosed.AddDynamic(this, &UMediaHandle::OnMediaClosed);
}

void UMediaHandle::CloseMovieScene_Implementation()
{
	Super::CloseMovieScene_Implementation();

	MediaPlayer->OnMediaOpened.RemoveAll(this);
	MediaPlayer->OnPlaybackSuspended.RemoveAll(this);
	// MediaPlayer->OnEndReached.RemoveAll(this);
	MediaPlayer->OnSeekCompleted.RemoveAll(this);
	MediaPlayer->OnMediaClosed.RemoveAll(this);

	MediaPlayer->Close();
}

void UMediaHandle::Play_Implementation()
{
	Super::Play_Implementation();
	MediaPlayer->OpenPlaylist(MediaPlaylist);

	MediaPlayer->Play();
}

void UMediaHandle::Pause_Implementation()
{
	Super::Pause_Implementation();
	MediaPlayer->Pause();
}

void UMediaHandle::Stop_Implementation()
{
	Super::Stop_Implementation();
	MediaPlayer->Close();
	// if (UMediaManager* MediaManager = GetManager<UMediaManager>())
	// {
	// 	MediaManager->UnRegisterMedia(this);
	// }
}

void UMediaHandle::Seek_Implementation(int32 InDays, int32 InHours, int32 InMinutes, int32 InSeconds, int32 InMicroSeconds)
{
	Super::Seek_Implementation(InDays, InHours, InMinutes, InSeconds, InMicroSeconds);
	MediaPlayer->Seek(FTimespan(InDays, InHours, InMinutes, InSeconds));
}

void UMediaHandle::SetMovieSceneLoopSetting_Implementation(FMovieSceneLoopSetting InMovieSceneLoopSetting)
{
	Super::SetMovieSceneLoopSetting_Implementation(InMovieSceneLoopSetting);

	if (MovieSceneSetting.MovieSceneLoopSetting.bEnableLoop != InMovieSceneLoopSetting.bEnableLoop)
	{
		// if (!InMovieSceneLoopSetting.bLoopFragment)
		{
			MediaPlayer->SetLooping(InMovieSceneLoopSetting.bEnableLoop);
		}
	}
}

FTimespan UMediaHandle::GetMovieSceneCurrentTime_Implementation()
{
	return MediaPlayer->GetTime();
}

void UMediaHandle::OnMediaOpened(FString OpenedUrl)
{
	Execute_OnMovieSceneOpenFinish(this);
}

void UMediaHandle::OnEndReached()
{
	Execute_OnMovieScenePlayFinish(this);
}

void UMediaHandle::OnPlaybackSuspended()
{
	Execute_OnMovieScenePlayFinish(this);
}

void UMediaHandle::OnSeekCompleted()
{
	Execute_OnMovieSceneSeekFinish(this);
}

void UMediaHandle::OnMediaClosed()
{
	Execute_OnMovieSceneCloseFinish(this);
}
