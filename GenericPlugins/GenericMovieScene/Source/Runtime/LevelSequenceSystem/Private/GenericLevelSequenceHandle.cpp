// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericLevelSequenceHandle.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void UGenericLevelSequenceHandle::OnMovieSceneOpened()
{
	Super::OnMovieSceneOpened();

	LoopCount = 0;

	LevelSequencePlayer->OnPlay.AddUniqueDynamic(this, &UGenericLevelSequenceHandle::OnPlay);
	LevelSequencePlayer->OnPlayReverse.AddUniqueDynamic(this, &UGenericLevelSequenceHandle::OnPlayReverse);
	LevelSequencePlayer->OnPause.AddUniqueDynamic(this, &UGenericLevelSequenceHandle::OnPause);
	LevelSequencePlayer->OnStop.AddUniqueDynamic(this, &UGenericLevelSequenceHandle::OnStop);
	LevelSequencePlayer->OnFinished.AddUniqueDynamic(this, &UGenericLevelSequenceHandle::OnFinished);
}

void UGenericLevelSequenceHandle::OnMovieSceneClosed()
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

bool UGenericLevelSequenceHandle::PlayMovieScene()
{
	LevelSequencePlayer->Play();
	return Super::PlayMovieScene();
}

bool UGenericLevelSequenceHandle::PlayMovieSceneFromStart()
{
	LevelSequencePlayer->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(0, EUpdatePositionMethod::Play));
	return Super::PlayMovieSceneFromStart();
}

bool UGenericLevelSequenceHandle::PlayLoopingMovieScene(int32 NumLoops)
{
	LoopCount = 0;
	LevelSequencePlayer->PlayLooping(NumLoops);
	return Super::PlayLoopingMovieScene(NumLoops);
}

bool UGenericLevelSequenceHandle::PlayReverseMovieScene()
{
	LevelSequencePlayer->PlayReverse();
	return Super::PlayReverseMovieScene();
}

bool UGenericLevelSequenceHandle::PauseMovieScene()
{
	LevelSequencePlayer->Pause();
	return Super::PauseMovieScene();
}

bool UGenericLevelSequenceHandle::StopMovieScene()
{
	LevelSequencePlayer->Stop();
	return Super::StopMovieScene();
}

bool UGenericLevelSequenceHandle::SeekMovieScene(FTimecode SeekTime)
{
	const FMovieSceneSequencePlaybackParams SeekParams = FMovieSceneSequencePlaybackParams(FFrameTime(SeekTime.ToFrameNumber(LevelSequencePlayer->GetFrameRate())), EUpdatePositionMethod::Jump);
	LevelSequencePlayer->SetPlaybackPosition(SeekParams);

	return Super::SeekMovieScene(SeekTime);
}

void UGenericLevelSequenceHandle::ChangeMovieSceneDirection()
{
	LevelSequencePlayer->ChangePlaybackDirection();
}

bool UGenericLevelSequenceHandle::IsPlaying()
{
	return LevelSequencePlayer->IsPlaying();
}

bool UGenericLevelSequenceHandle::IsLooping()
{
	return GetPlaybackSettings().LoopCount.Value < 0 || LoopCount != 0;
}

bool UGenericLevelSequenceHandle::IsPaused()
{
	return LevelSequencePlayer->IsPaused();
}

bool UGenericLevelSequenceHandle::IsReversed()
{
	return LevelSequencePlayer->IsReversed();
}

FTimecode UGenericLevelSequenceHandle::GetCurrentTime()
{
	return LevelSequencePlayer->GetCurrentTime().ToTimecode();
}

FTimecode UGenericLevelSequenceHandle::GetDuration()
{
	return LevelSequencePlayer->GetDuration().ToTimecode();
}

FFrameRate UGenericLevelSequenceHandle::GetFrameRate()
{
	return LevelSequencePlayer->GetFrameRate();
}

void UGenericLevelSequenceHandle::SetFrameRate(FFrameRate FrameRate)
{
	LevelSequencePlayer->SetFrameRate(FrameRate);
}

float UGenericLevelSequenceHandle::GetPlayRate()
{
	return LevelSequencePlayer->GetPlayRate();
}

void UGenericLevelSequenceHandle::SetPlayRate(float InPlayRate)
{
	LevelSequencePlayer->SetPlayRate(InPlayRate);
}

void UGenericLevelSequenceHandle::SetTimeRange(float StartTime, float Duration)
{
	LevelSequencePlayer->SetTimeRange(StartTime, Duration);
}

bool UGenericLevelSequenceHandle::GetDisableCameraCuts() const
{
	return LevelSequencePlayer->GetDisableCameraCuts();
}

void UGenericLevelSequenceHandle::SetDisableCameraCuts(bool bInDisableCameraCuts)
{
	LevelSequencePlayer->SetDisableCameraCuts(bInDisableCameraCuts);
}

ALevelSequenceActor* UGenericLevelSequenceHandle::GetLevelSequenceActor() const
{
	return LevelSequenceActor;
}

ULevelSequencePlayer* UGenericLevelSequenceHandle::GetULevelSequencePlayer() const
{
	return LevelSequencePlayer;
}

FString UGenericLevelSequenceHandle::GetSequenceName() const
{
	return LevelSequencePlayer->GetSequenceName();
}

ULevelSequence* UGenericLevelSequenceHandle::GetSequence() const
{
	return LevelSequenceActor->GetSequence();
}

void UGenericLevelSequenceHandle::SetSequence(ULevelSequence* InSequence, bool bIsPlay)
{
	LevelSequencePlayer->Stop();
	LevelSequenceActor->SetSequence(InSequence);

	if (bIsPlay)
	{
		LevelSequencePlayer->Play();
	}
}

FMovieSceneSequencePlaybackSettings UGenericLevelSequenceHandle::GetPlaybackSettings() const
{
	return LevelSequenceActor->PlaybackSettings;
}

void UGenericLevelSequenceHandle::SetPlaybackSettings(const FMovieSceneSequencePlaybackSettings& InSettings)
{
	LevelSequenceActor->PlaybackSettings = InSettings;
	LevelSequencePlayer->SetPlaybackSettings(InSettings);
}

void UGenericLevelSequenceHandle::OnPlay()
{
	OnMovieScenePlay();
}

void UGenericLevelSequenceHandle::OnPlayReverse()
{
	OnMovieScenePlayReverse();
}

void UGenericLevelSequenceHandle::OnPause()
{
	OnMovieScenePause();
}

void UGenericLevelSequenceHandle::OnStop()
{
	OnMovieSceneStop();
}

void UGenericLevelSequenceHandle::OnFinished()
{
	LoopCount++;

	if (LoopCount == GetPlaybackSettings().LoopCount.Value)
	{
		LoopCount = 0;
	}

	OnMovieScenePlayFinish();
}
