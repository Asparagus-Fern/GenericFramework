// Copyright ChenTaiye 2025. All Rights Reserved.

#include "LevelSequenceHandle.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

ULevelSequenceHandle* ULevelSequenceHandle::RegisterLevelSequenceHandle(FName HandleName, ULevelSequence* InLevelSequence, FMovieSceneSequencePlaybackSettings InSettings)
{
	ULevelSequenceHandle* NewHandle = nullptr;

	if (HandleName == NAME_None)
	{
		DLOG(DLogMovieScene, Error, TEXT("HandleName Is InValid"))
		return NewHandle;
	}

	if (!IsValid(InLevelSequence))
	{
		DLOG(DLogMovieScene, Error, TEXT("InLevelSequence Is InValid"))
		return NewHandle;
	}

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

void ULevelSequenceHandle::OnMovieSceneOpened()
{
	Super::OnMovieSceneOpened();

	LoopCount = 0;

	LevelSequencePlayer->OnPlay.AddUniqueDynamic(this, &ULevelSequenceHandle::OnPlay);
	LevelSequencePlayer->OnPlayReverse.AddUniqueDynamic(this, &ULevelSequenceHandle::OnPlayReverse);
	LevelSequencePlayer->OnPause.AddUniqueDynamic(this, &ULevelSequenceHandle::OnPause);
	LevelSequencePlayer->OnStop.AddUniqueDynamic(this, &ULevelSequenceHandle::OnStop);
	LevelSequencePlayer->OnFinished.AddUniqueDynamic(this, &ULevelSequenceHandle::OnFinished);
}

void ULevelSequenceHandle::OnMovieSceneClosed()
{
	Super::OnMovieSceneClosed();

	if (IsPlaying())
	{
		StopMovieScene();
	}

	LevelSequencePlayer->OnPlay.RemoveAll(this);
	LevelSequencePlayer->OnPlayReverse.RemoveAll(this);
	LevelSequencePlayer->OnPause.RemoveAll(this);
	LevelSequencePlayer->OnStop.RemoveAll(this);
	LevelSequencePlayer->OnFinished.RemoveAll(this);

	LevelSequenceActor->Destroy();

	LoopCount = 0;
	LevelSequencePlayer = nullptr;
	LevelSequenceActor = nullptr;
}

bool ULevelSequenceHandle::PlayMovieScene()
{
	LevelSequencePlayer->Play();
	return Super::PlayMovieScene();
}

bool ULevelSequenceHandle::PlayMovieSceneFromStart()
{
	LevelSequencePlayer->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(0, EUpdatePositionMethod::Play));
	return Super::PlayMovieSceneFromStart();
}

bool ULevelSequenceHandle::PlayLoopingMovieScene(int32 NumLoops)
{
	LoopCount = 0;
	LevelSequencePlayer->PlayLooping(NumLoops);
	return Super::PlayLoopingMovieScene(NumLoops);
}

bool ULevelSequenceHandle::PlayReverseMovieScene()
{
	LevelSequencePlayer->PlayReverse();
	return Super::PlayReverseMovieScene();
}

bool ULevelSequenceHandle::PauseMovieScene()
{
	LevelSequencePlayer->Pause();
	return Super::PauseMovieScene();
}

bool ULevelSequenceHandle::StopMovieScene()
{
	LevelSequencePlayer->Stop();
	return Super::StopMovieScene();
}

bool ULevelSequenceHandle::SeekMovieScene(FTimecode SeekTime)
{
	const FMovieSceneSequencePlaybackParams SeekParams = FMovieSceneSequencePlaybackParams(FFrameTime(SeekTime.ToFrameNumber(LevelSequencePlayer->GetFrameRate())), EUpdatePositionMethod::Jump);
	LevelSequencePlayer->SetPlaybackPosition(SeekParams);

	return Super::SeekMovieScene(SeekTime);
}

void ULevelSequenceHandle::ChangeMovieSceneDirection()
{
	LevelSequencePlayer->ChangePlaybackDirection();
}

bool ULevelSequenceHandle::IsPlaying()
{
	return LevelSequencePlayer->IsPlaying();
}

bool ULevelSequenceHandle::IsLooping()
{
	return GetPlaybackSettings().LoopCount.Value < 0 || LoopCount != 0;
}

bool ULevelSequenceHandle::IsPaused()
{
	return LevelSequencePlayer->IsPaused();
}

bool ULevelSequenceHandle::IsReversed()
{
	return LevelSequencePlayer->IsReversed();
}

FTimecode ULevelSequenceHandle::GetCurrentTime()
{
	return LevelSequencePlayer->GetCurrentTime().ToTimecode();
}

FTimecode ULevelSequenceHandle::GetDuration()
{
	return LevelSequencePlayer->GetDuration().ToTimecode();
}

FFrameRate ULevelSequenceHandle::GetFrameRate()
{
	return LevelSequencePlayer->GetFrameRate();
}

void ULevelSequenceHandle::SetFrameRate(FFrameRate FrameRate)
{
	LevelSequencePlayer->SetFrameRate(FrameRate);
}

float ULevelSequenceHandle::GetPlayRate()
{
	return LevelSequencePlayer->GetPlayRate();
}

void ULevelSequenceHandle::SetPlayRate(float InPlayRate)
{
	LevelSequencePlayer->SetPlayRate(InPlayRate);
}

void ULevelSequenceHandle::SetTimeRange(float StartTime, float Duration)
{
	LevelSequencePlayer->SetTimeRange(StartTime, Duration);
}

bool ULevelSequenceHandle::GetDisableCameraCuts() const
{
	return LevelSequencePlayer->GetDisableCameraCuts();
}

void ULevelSequenceHandle::SetDisableCameraCuts(bool bInDisableCameraCuts)
{
	LevelSequencePlayer->SetDisableCameraCuts(bInDisableCameraCuts);
}

ALevelSequenceActor* ULevelSequenceHandle::GetLevelSequenceActor() const
{
	return LevelSequenceActor;
}

ULevelSequencePlayer* ULevelSequenceHandle::GetULevelSequencePlayer() const
{
	return LevelSequencePlayer;
}

FString ULevelSequenceHandle::GetSequenceName() const
{
	return LevelSequencePlayer->GetSequenceName();
}

ULevelSequence* ULevelSequenceHandle::GetSequence() const
{
	return LevelSequenceActor->GetSequence();
}

void ULevelSequenceHandle::SetSequence(ULevelSequence* InSequence, bool bIsPlay)
{
	LevelSequencePlayer->Stop();
	LevelSequenceActor->SetSequence(InSequence);

	if (bIsPlay)
	{
		LevelSequencePlayer->Play();
	}
}

FMovieSceneSequencePlaybackSettings ULevelSequenceHandle::GetPlaybackSettings() const
{
	return LevelSequenceActor->PlaybackSettings;
}

void ULevelSequenceHandle::SetPlaybackSettings(const FMovieSceneSequencePlaybackSettings& InSettings)
{
	LevelSequenceActor->PlaybackSettings = InSettings;
	LevelSequencePlayer->SetPlaybackSettings(InSettings);
}

void ULevelSequenceHandle::OnPlay()
{
	OnMovieScenePlay();
}

void ULevelSequenceHandle::OnPlayReverse()
{
	OnMovieScenePlayReverse();
}

void ULevelSequenceHandle::OnPause()
{
	OnMovieScenePause();
}

void ULevelSequenceHandle::OnStop()
{
	OnMovieSceneStop();
}

void ULevelSequenceHandle::OnFinished()
{
	LoopCount++;

	if (LoopCount == GetPlaybackSettings().LoopCount.Value)
	{
		LoopCount = 0;
	}

	OnMovieScenePlayFinish();
}
