// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaHandle.h"

#include "MediaPlayer.h"
#include "MediaPlayerFacade.h"
#include "MediaPlaylist.h"
#include "Manager/ManagerStatics.h"

UMediaHandle::UMediaHandle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  bIsMediaInitialize(false)
{
}

void UMediaHandle::Register(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, FMovieSceneMediaPlaybackSettings InSettings)
{
	MediaPlayer = InMediaPlayer;
	PlaybackSettings = InSettings;

	MediaPlayer->OnMediaOpened.AddUniqueDynamic(this, &UMediaHandle::OnMediaOpened);
	MediaPlayer->OnMediaOpenFailed.AddUniqueDynamic(this, &UMediaHandle::OnMediaOpenFailed);
	MediaPlayer->OnMediaClosed.AddUniqueDynamic(this, &UMediaHandle::OnMediaClosed);
	MediaPlayer->OnEndReached.AddUniqueDynamic(this, &UMediaHandle::OnEndReached);
	MediaPlayer->OnSeekCompleted.AddUniqueDynamic(this, &UMediaHandle::OnSeekCompleted);
	MediaPlayer->OnPlaybackSuspended.AddUniqueDynamic(this, &UMediaHandle::OnPlaybackSuspended);
	MediaPlayer->OnPlaybackResumed.AddUniqueDynamic(this, &UMediaHandle::OnPlaybackResumed);

	FMediaPlayerOptions MediaPlayerOptions;
	MediaPlayerOptions.PlayOnOpen = PlaybackSettings.bAutoPlay ? EMediaPlayerOptionBooleanOverride::Enabled : EMediaPlayerOptionBooleanOverride::Disabled;
	MediaPlayerOptions.Loop = PlaybackSettings.bIsLoop ? EMediaPlayerOptionBooleanOverride::Enabled : EMediaPlayerOptionBooleanOverride::Disabled;

	/* It is meaningless To Set LoopNum == 0 ,So Disable Loop. And LoopNum == 1 Mean Play Only Once, Disable Also */
	if (PlaybackSettings.LoopNum == 0 || PlaybackSettings.LoopNum == 1)
	{
		MediaPlayerOptions.Loop = EMediaPlayerOptionBooleanOverride::Disabled;
	}

	MediaPlayer->OpenSourceWithOptions(InMediaSource, MediaPlayerOptions);

	OpenMovieScene();
}

void UMediaHandle::Register(UMediaPlayer* InMediaPlayer, UMediaPlaylist* InMediaPlaylist, FMovieSceneMediaPlaybackSettings InSettings)
{
	MediaPlayer = InMediaPlayer;
	PlaybackSettings = InSettings;

	MediaPlayer->OnMediaOpened.AddUniqueDynamic(this, &UMediaHandle::OnMediaOpened);
	MediaPlayer->OnMediaOpenFailed.AddUniqueDynamic(this, &UMediaHandle::OnMediaOpenFailed);
	MediaPlayer->OnMediaClosed.AddUniqueDynamic(this, &UMediaHandle::OnMediaClosed);
	MediaPlayer->OnEndReached.AddUniqueDynamic(this, &UMediaHandle::OnEndReached);
	MediaPlayer->OnSeekCompleted.AddUniqueDynamic(this, &UMediaHandle::OnSeekCompleted);
	MediaPlayer->OnPlaybackSuspended.AddUniqueDynamic(this, &UMediaHandle::OnPlaybackSuspended);
	MediaPlayer->OnPlaybackResumed.AddUniqueDynamic(this, &UMediaHandle::OnPlaybackResumed);

	FMediaPlayerOptions MediaPlayerOptions;
	MediaPlayerOptions.PlayOnOpen = PlaybackSettings.bAutoPlay ? EMediaPlayerOptionBooleanOverride::Enabled : EMediaPlayerOptionBooleanOverride::Disabled;
	MediaPlayerOptions.Loop = PlaybackSettings.bIsLoop ? EMediaPlayerOptionBooleanOverride::Enabled : EMediaPlayerOptionBooleanOverride::Disabled;

	/* It is meaningless To Set LoopNum == 0 ,So Disable Loop. And LoopNum == 1 Mean Play Only Once, Disable Also */
	if (PlaybackSettings.LoopNum == 0 || PlaybackSettings.LoopNum == 1)
	{
		MediaPlayerOptions.Loop = EMediaPlayerOptionBooleanOverride::Disabled;
	}

	for (int It = 0; It < InMediaPlaylist->Num(); ++It)
	{
		if (It == 0)
		{
			MediaPlayer->OpenSourceWithOptions(InMediaPlaylist->Get(It), MediaPlayerOptions);
		}
		else
		{
			MediaPlayer->GetPlaylistRef().Add(InMediaPlaylist->Get(It));
		}
	}

	OpenMovieScene();
}

void UMediaHandle::OpenMovieScene()
{
	// Super::OpenMovieScene();
}

void UMediaHandle::CloseMovieScene()
{
	Super::CloseMovieScene();
}

void UMediaHandle::OnMovieSceneOpened()
{
	Super::OnMovieSceneOpened();
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

	MediaPlayer->Close();
	MediaPlayer = nullptr;
}

bool UMediaHandle::PlayMovieScene()
{
	if (!bIsMediaInitialize)
	{
		DLOG(DLogMovieScene, Error, TEXT("Media File To Initialize"))
		return false;
	}

	MediaPlayer->Play();
	return Super::PlayMovieScene();
}

bool UMediaHandle::PlayMovieSceneFromStart()
{
	if (!bIsMediaInitialize)
	{
		DLOG(DLogMovieScene, Error, TEXT("Media File To Initialize"))
		return false;
	}

	MediaPlayer->PlayAndSeek();
	return Super::PlayMovieSceneFromStart();
}

bool UMediaHandle::PlayLoopingMovieScene(int32 NumLoops)
{
	if (!bIsMediaInitialize)
	{
		DLOG(DLogMovieScene, Error, TEXT("Media File To Initialize"))
		return false;
	}

	LoopCount = 0;
	PlaybackSettings.LoopNum = NumLoops;

	MediaPlayer->SetLooping(true);
	MediaPlayer->Play();

	return Super::PlayLoopingMovieScene(NumLoops);
}

bool UMediaHandle::PlayReverseMovieScene()
{
	if (!bIsMediaInitialize)
	{
		DLOG(DLogMovieScene, Error, TEXT("Media File To Initialize"))
		return false;
	}

	/* Crash In UE5.3 While Rate < 0 */
	MediaPlayer->SetRate(MediaPlayer->GetRate() * -1);

	return Super::PlayReverseMovieScene();
}

bool UMediaHandle::PauseMovieScene()
{
	return MediaPlayer->Pause();
}

bool UMediaHandle::StopMovieScene()
{
	MediaPlayer->Pause();
	MediaPlayer->Seek(MediaPlayer->GetDuration());

	return Super::StopMovieScene();
}

bool UMediaHandle::SeekMovieScene(FTimecode SeekTime)
{
	MediaPlayer->Seek(SeekTime.ToTimespan(GetFrameRate()));
	return Super::SeekMovieScene(SeekTime);
}

void UMediaHandle::ChangeMovieSceneDirection()
{
	PlayReverseMovieScene();
}

bool UMediaHandle::IsPlaying()
{
	return MediaPlayer->IsPlaying();
}

bool UMediaHandle::IsLooping()
{
	return MediaPlayer->IsLooping();
}

bool UMediaHandle::IsPaused()
{
	return MediaPlayer->IsPaused();
}

bool UMediaHandle::IsReversed()
{
	return Super::IsReversed();
}

FTimecode UMediaHandle::GetCurrentTime()
{
	return FTimecode::FromTimespan(MediaPlayer->GetTime(), GetFrameRate(), true);
}

FTimecode UMediaHandle::GetDuration()
{
	return FTimecode::FromTimespan(MediaPlayer->GetDuration(), GetFrameRate(), true);
}

FFrameRate UMediaHandle::GetFrameRate()
{
	FString MediaInfo = MediaPlayer->GetPlayerFacade()->GetInfo();
	MediaInfo.Split("Frame Rate:", nullptr, &MediaInfo);
	MediaInfo.Split("fps", &MediaInfo, nullptr);

	const int32 FrameRate = FCString::Atoi(*MediaInfo);

	return FFrameRate(FrameRate, 1);
}

void UMediaHandle::SetFrameRate(FFrameRate FrameRate)
{
	Super::SetFrameRate(FrameRate);
}

float UMediaHandle::GetPlayRate()
{
	return MediaPlayer->GetRate() < 0;
}

void UMediaHandle::SetPlayRate(float InPlayRate)
{
	MediaPlayer->SetRate(InPlayRate);
}

bool UMediaHandle::HasError() const
{
	return MediaPlayer->HasError();
}

bool UMediaHandle::IsBuffering() const
{
	return MediaPlayer->IsBuffering();
}

bool UMediaHandle::IsConnecting() const
{
	return MediaPlayer->IsConnecting();
}

bool UMediaHandle::IsPreparing() const
{
	return MediaPlayer->IsPreparing();
}

bool UMediaHandle::IsClosed() const
{
	return MediaPlayer->IsClosed();
}

bool UMediaHandle::IsReady() const
{
	return MediaPlayer->IsReady();
}

bool UMediaHandle::CanPause() const
{
	return MediaPlayer->CanPause();
}

bool UMediaHandle::CanPlaySource(UMediaSource* InMediaSource) const
{
	return MediaPlayer->CanPlaySource(InMediaSource);
}

bool UMediaHandle::CanPlayUrl(const FString& Url) const
{
	return MediaPlayer->CanPlayUrl(Url);
}

FText UMediaHandle::GetMediaName() const
{
	return MediaPlayer->GetMediaName();
}

FName UMediaHandle::GetPlayerName() const
{
	return MediaPlayer->GetPlayerName();
}

FName UMediaHandle::GetDesiredPlayerName() const
{
	return MediaPlayer->GetDesiredPlayerName();
}

void UMediaHandle::GetSupportedRates(TArray<FFloatRange>& OutRates, bool Unthinned) const
{
	MediaPlayer->GetSupportedRates(OutRates, Unthinned);
}

const FString& UMediaHandle::GetUrl() const
{
	return MediaPlayer->GetUrl();
}

void UMediaHandle::SetBlockOnTime(const FTimespan& Time) const
{
	MediaPlayer->SetBlockOnTime(Time);
}

void UMediaHandle::SetBlockOnTimeRange(const TRange<FTimespan>& TimeRange) const
{
	MediaPlayer->SetBlockOnTimeRange(TimeRange);
}

bool UMediaHandle::SetLooping(bool Looping) const
{
	return MediaPlayer->SetLooping(Looping);
}

bool UMediaHandle::SetNativeVolume(float Volume)
{
	return MediaPlayer->SetNativeVolume(Volume);
}

FTimespan UMediaHandle::GetTimeDelay() const
{
	return MediaPlayer->GetTimeDelay();
}

void UMediaHandle::SetTimeDelay(FTimespan TimeDelay)
{
	return MediaPlayer->SetTimeDelay(TimeDelay);
}

bool UMediaHandle::SupportsRate(float Rate, bool Unthinned) const
{
	return MediaPlayer->SupportsRate(Rate, Unthinned);
}

bool UMediaHandle::SupportsScrubbing() const
{
	return MediaPlayer->SupportsScrubbing();
}

bool UMediaHandle::SupportsSeeking() const
{
	return MediaPlayer->SupportsSeeking();
}

int32 UMediaHandle::GetNumTracks(EMediaPlayerTrack TrackType) const
{
	return MediaPlayer->GetNumTracks(TrackType);
}

int32 UMediaHandle::GetNumTrackFormats(EMediaPlayerTrack TrackType, int32 TrackIndex) const
{
	return MediaPlayer->GetNumTrackFormats(TrackType, TrackIndex);
}

int32 UMediaHandle::GetSelectedTrack(EMediaPlayerTrack TrackType) const
{
	return MediaPlayer->GetSelectedTrack(TrackType);
}

FText UMediaHandle::GetTrackDisplayName(EMediaPlayerTrack TrackType, int32 TrackIndex) const
{
	return MediaPlayer->GetTrackDisplayName(TrackType, TrackIndex);
}

int32 UMediaHandle::GetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex) const
{
	return MediaPlayer->GetTrackFormat(TrackType, TrackIndex);
}

FString UMediaHandle::GetTrackLanguage(EMediaPlayerTrack TrackType, int32 TrackIndex) const
{
	return MediaPlayer->GetTrackLanguage(TrackType, TrackIndex);
}

bool UMediaHandle::SelectTrack(EMediaPlayerTrack TrackType, int32 TrackIndex)
{
	return MediaPlayer->SelectTrack(TrackType, TrackIndex);
}

bool UMediaHandle::SetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex, int32 FormatIndex)
{
	return MediaPlayer->SetTrackFormat(TrackType, TrackIndex, FormatIndex);
}

int32 UMediaHandle::GetAudioTrackChannels(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetAudioTrackChannels(TrackIndex, FormatIndex);
}

FString UMediaHandle::GetAudioTrackType(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetAudioTrackType(TrackIndex, FormatIndex);
}

int32 UMediaHandle::GetAudioTrackSampleRate(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetAudioTrackSampleRate(TrackIndex, FormatIndex);
}

FString UMediaHandle::GetVideoTrackType(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackType(TrackIndex, FormatIndex);
}

float UMediaHandle::GetVideoTrackAspectRatio(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackAspectRatio(TrackIndex, FormatIndex);
}

FIntPoint UMediaHandle::GetVideoTrackDimensions(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackDimensions(TrackIndex, FormatIndex);
}

float UMediaHandle::GetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackFrameRate(TrackIndex, FormatIndex);
}

FFloatRange UMediaHandle::GetVideoTrackFrameRates(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackFrameRates(TrackIndex, FormatIndex);
}

bool UMediaHandle::SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate)
{
	return MediaPlayer->SetVideoTrackFrameRate(TrackIndex, FormatIndex, FrameRate);
}

float UMediaHandle::GetHorizontalFieldOfView() const
{
	return MediaPlayer->GetHorizontalFieldOfView();
}

float UMediaHandle::GetVerticalFieldOfView() const
{
	return MediaPlayer->GetVerticalFieldOfView();
}

FRotator UMediaHandle::GetViewRotation() const
{
	return MediaPlayer->GetViewRotation();
}

bool UMediaHandle::SetViewField(float Horizontal, float Vertical, bool Absolute)
{
	return MediaPlayer->SetViewField(Horizontal, Vertical, Absolute);
}

bool UMediaHandle::SetViewRotation(const FRotator& Rotation, bool Absolute)
{
	return MediaPlayer->SetViewRotation(Rotation, Absolute);
}

UMediaPlayer* UMediaHandle::GetMediaPlayer() const
{
	return MediaPlayer;
}

UMediaSource* UMediaHandle::GetMediaSource() const
{
	return MediaPlayer->GetPlaylist()->Get(MediaPlayer->GetPlaylistIndex());
}

void UMediaHandle::OnMediaOpened(FString OpenedUrl)
{
	bIsMediaInitialize = true;
	OnMovieSceneOpened();

	if (PlaybackSettings.bAutoPlay)
	{
		PlayMovieSceneFromStart();
		MediaPlayer->SetRate(10.f);
	}
}

void UMediaHandle::OnMediaOpenFailed(FString FailedUrl)
{
	DLOG(DLogMovieScene, Error, TEXT("Media Open Fail : %s"), *FailedUrl)
}

void UMediaHandle::OnMediaClosed()
{
	OnMovieSceneStop();
}

void UMediaHandle::OnEndReached()
{
	OnMovieScenePlayFinish();

	if (MediaPlayer->IsLooping() && PlaybackSettings.LoopNum != -1)
	{
		LoopCount++;

		if (PlaybackSettings.LoopNum == LoopCount)
		{
			LoopCount = 0;
			MediaPlayer->SetLooping(false);
		}
	}
}

void UMediaHandle::OnSeekCompleted()
{
	OnMovieSceneSeek();
}

void UMediaHandle::OnPlaybackSuspended()
{
	OnMovieScenePause();
}

void UMediaHandle::OnPlaybackResumed()
{
	OnMovieScenePlay();
}
