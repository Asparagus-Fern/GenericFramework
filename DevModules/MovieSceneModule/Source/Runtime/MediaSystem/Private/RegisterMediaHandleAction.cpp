// Copyright ChenTaiye 2025. All Rights Reserved.


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
		GenericLOG(GenericLogMovieScene, Error, TEXT("HandleName Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaPlayer))
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("InMediaPlayer Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaSource))
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("InMediaSource Is InValid"))
		return nullptr;
	}

	if (UHandleManager* HandleManager = GetManagerOwner<UHandleManager>())
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
		GenericLOG(GenericLogMovieScene, Error, TEXT("HandleName Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaPlayer))
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("InMediaPlayer Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaPlaylist))
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("InMediaSource Is InValid"))
		return nullptr;
	}

	if (UHandleManager* HandleManager = GetManagerOwner<UHandleManager>())
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
