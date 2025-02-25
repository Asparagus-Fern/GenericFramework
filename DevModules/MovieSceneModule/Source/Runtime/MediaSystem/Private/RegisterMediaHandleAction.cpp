// Fill out your copyright notice in the Description page of Project Settings.


#include "RegisterMediaHandleAction.h"

#include "MediaHandle.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

URegisterMediaHandleAction* URegisterMediaHandleAction::RegisterMediaHandleByMediaSourse(FName HandleName, UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, FMovieSceneMediaPlaybackSettings InSettings)
{
	if (HandleName == NAME_None)
	{
		DLOG(DLogMovieScene, Error, TEXT("HandleName Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaPlayer))
	{
		DLOG(DLogMovieScene, Error, TEXT("InMediaPlayer Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaSource))
	{
		DLOG(DLogMovieScene, Error, TEXT("InMediaSource Is InValid"))
		return nullptr;
	}

	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		UMediaHandle* NewHandle = nullptr;

		if (HandleManager->IsHandleRegister(HandleName))
		{
			NewHandle = HandleManager->GetHandle<UMediaHandle>(HandleName);
			NewHandle->CloseMovieScene();
		}
		else
		{
			NewHandle = HandleManager->RegisterHandle<UMediaHandle>(HandleName);
		}

		URegisterMediaHandleAction* NewAction = NewObject<URegisterMediaHandleAction>();
		NewAction->MediaHandle = NewHandle;

		InMediaPlayer->OnMediaOpened.AddUniqueDynamic(NewAction, &URegisterMediaHandleAction::OnMediaOpened);
		InMediaPlayer->OnMediaOpenFailed.AddUniqueDynamic(NewAction, &URegisterMediaHandleAction::OnMediaOpenFailed);

		NewHandle->Register(InMediaPlayer, InMediaSource, InSettings);

		return NewAction;
	}

	return nullptr;
}

URegisterMediaHandleAction* URegisterMediaHandleAction::RegisterMediaHandleByMediaPlaylist(FName HandleName, UMediaPlayer* InMediaPlayer, UMediaSource* InMediaPlaylist, FMovieSceneMediaPlaybackSettings InSettings)
{
	if (HandleName == NAME_None)
	{
		DLOG(DLogMovieScene, Error, TEXT("HandleName Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaPlayer))
	{
		DLOG(DLogMovieScene, Error, TEXT("InMediaPlayer Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaPlaylist))
	{
		DLOG(DLogMovieScene, Error, TEXT("InMediaSource Is InValid"))
		return nullptr;
	}

	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		UMediaHandle* NewHandle = nullptr;

		if (HandleManager->IsHandleRegister(HandleName))
		{
			NewHandle = HandleManager->GetHandle<UMediaHandle>(HandleName);
			NewHandle->CloseMovieScene();
		}
		else
		{
			NewHandle = HandleManager->RegisterHandle<UMediaHandle>(HandleName);
		}

		URegisterMediaHandleAction* NewAction = NewObject<URegisterMediaHandleAction>();
		NewAction->MediaHandle = NewHandle;

		InMediaPlayer->OnMediaOpened.AddUniqueDynamic(NewAction, &URegisterMediaHandleAction::OnMediaOpened);
		InMediaPlayer->OnMediaOpenFailed.AddUniqueDynamic(NewAction, &URegisterMediaHandleAction::OnMediaOpenFailed);

		NewHandle->Register(InMediaPlayer, InMediaPlaylist, InSettings);

		return NewAction;
	}

	return nullptr;
}

void URegisterMediaHandleAction::OnMediaOpened(FString OpenedUrl)
{
	Success.Broadcast(MediaHandle, OpenedUrl);
}

void URegisterMediaHandleAction::OnMediaOpenFailed(FString FailedUrl)
{
	Fail.Broadcast();
}
