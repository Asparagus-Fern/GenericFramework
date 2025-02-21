// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaHandle.h"

#include "MediaPlayer.h"
#include "MediaSource.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

UMediaHandle* UMediaHandle::RegisterMediaHandle(FName HandleName, UMediaSource* InMediaSource)
{
	UMediaHandle* NewHandle = nullptr;

	if (HandleName == NAME_None)
	{
		DLOG(DLogMovieScene, Error, TEXT("HandleName Is InValid"))
		return NewHandle;
	}

	if (!IsValid(InMediaSource))
	{
		DLOG(DLogMovieScene, Error, TEXT("InMediaSource Is InValid"))
		return NewHandle;
	}

	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		if (HandleManager->IsHandleRegister(HandleName))
		{
			NewHandle = HandleManager->GetHandle<UMediaHandle>(HandleName);
			NewHandle->CloseMovieScene();
		}
		else
		{
			NewHandle = HandleManager->RegisterHandle<UMediaHandle>(HandleName);
		}

		NewHandle->MediaPlayer = NewObject<UMediaPlayer>(NewHandle);
		NewHandle->MediaSource = InMediaSource;

		NewHandle->OpenMovieScene();
	}
	return NewHandle;
}

void UMediaHandle::OnMovieSceneOpened()
{
	Super::OnMovieSceneOpened();

	MediaPlayer->OnMediaOpened.AddUniqueDynamic(this, &UMediaHandle::OnMediaOpened);
	MediaPlayer->OnMediaOpenFailed.AddUniqueDynamic(this, &UMediaHandle::OnMediaOpenFailed);
	MediaPlayer->OnMediaClosed.AddUniqueDynamic(this, &UMediaHandle::OnMediaClosed);
	MediaPlayer->OnEndReached.AddUniqueDynamic(this, &UMediaHandle::OnEndReached);
	MediaPlayer->OnSeekCompleted.AddUniqueDynamic(this, &UMediaHandle::OnSeekCompleted);
}

void UMediaHandle::OnMovieSceneClosed()
{
	Super::OnMovieSceneClosed();

	if (IsPlaying())
	{
		StopMovieScene();
	}

	MediaPlayer->OnMediaOpened.RemoveAll(this);
	MediaPlayer->OnMediaOpenFailed.RemoveAll(this);
	MediaPlayer->OnMediaClosed.RemoveAll(this);
	MediaPlayer->OnEndReached.RemoveAll(this);
	MediaPlayer->OnSeekCompleted.RemoveAll(this);

	MediaPlayer = nullptr;
	MediaSource = nullptr;
}

void UMediaHandle::PlayMovieScene()
{
	MediaPlayer->Play();
	Super::PlayMovieScene();
}

void UMediaHandle::OnMediaOpened(FString OpenedUrl)
{
	OnMovieScenePlay();
}

void UMediaHandle::OnMediaOpenFailed(FString FailedUrl)
{
}

void UMediaHandle::OnMediaClosed()
{
	OnMovieSceneStop();
}

void UMediaHandle::OnEndReached()
{
	OnMovieScenePlayFinish();
}

void UMediaHandle::OnSeekCompleted()
{
	OnMovieSceneSeek();
}
