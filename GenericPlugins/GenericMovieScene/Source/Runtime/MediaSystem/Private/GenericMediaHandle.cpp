// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericMediaHandle.h"

#include "MediaPlayer.h"
#include "MediaPlayerFacade.h"
#include "MediaPlaylist.h"
#include "MovieSceneType.h"


UGenericMediaHandle::UGenericMediaHandle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  bIsMediaInitialize(false)
{
}

void UGenericMediaHandle::Register(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, const FMediaPlayerOptions& InOptions)
{
	MediaPlayer = InMediaPlayer;
	Options = InOptions;

	MediaPlayer->OnMediaOpened.AddUniqueDynamic(this, &UGenericMediaHandle::OnMediaOpened);
	MediaPlayer->OnMediaOpenFailed.AddUniqueDynamic(this, &UGenericMediaHandle::OnMediaOpenFailed);
	MediaPlayer->OnMediaClosed.AddUniqueDynamic(this, &UGenericMediaHandle::OnMediaClosed);
	MediaPlayer->OnEndReached.AddUniqueDynamic(this, &UGenericMediaHandle::OnEndReached);
	MediaPlayer->OnSeekCompleted.AddUniqueDynamic(this, &UGenericMediaHandle::OnSeekCompleted);
	MediaPlayer->OnPlaybackSuspended.AddUniqueDynamic(this, &UGenericMediaHandle::OnPlaybackSuspended);
	MediaPlayer->OnPlaybackResumed.AddUniqueDynamic(this, &UGenericMediaHandle::OnPlaybackResumed);

	MediaPlayer->OpenSourceWithOptions(InMediaSource, InOptions);
	OpenMovieScene();
}

void UGenericMediaHandle::OpenMovieScene()
{
	// Super::OpenMovieScene();
}

void UGenericMediaHandle::CloseMovieScene()
{
	Super::CloseMovieScene();
}

void UGenericMediaHandle::OnMovieSceneOpened()
{
	Super::OnMovieSceneOpened();
}

void UGenericMediaHandle::OnMovieSceneClosed()
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

bool UGenericMediaHandle::PlayMovieScene()
{
	if (!bIsMediaInitialize)
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("Media File To Initialize"))
		return false;
	}

	MediaPlayer->Play();
	return Super::PlayMovieScene();
}

bool UGenericMediaHandle::PlayMovieSceneFromStart()
{
	if (!bIsMediaInitialize)
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("Media File To Initialize"))
		return false;
	}

	MediaPlayer->PlayAndSeek();
	return Super::PlayMovieSceneFromStart();
}

bool UGenericMediaHandle::PlayLoopingMovieScene(int32 NumLoops)
{
	if (!bIsMediaInitialize)
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("Media File To Initialize"))
		return false;
	}
	
	MediaPlayer->SetLooping(true);
	MediaPlayer->Play();

	return Super::PlayLoopingMovieScene(NumLoops);
}

bool UGenericMediaHandle::PlayReverseMovieScene()
{
	if (!bIsMediaInitialize)
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("Media File To Initialize"))
		return false;
	}

	/* Crash In UE5.3 While Rate < 0 */
	MediaPlayer->SetRate(MediaPlayer->GetRate() * -1);

	return Super::PlayReverseMovieScene();
}

bool UGenericMediaHandle::PauseMovieScene()
{
	return MediaPlayer->Pause();
}

bool UGenericMediaHandle::StopMovieScene()
{
	MediaPlayer->Pause();
	MediaPlayer->Seek(MediaPlayer->GetDuration());

	return Super::StopMovieScene();
}

bool UGenericMediaHandle::SeekMovieScene(FTimecode SeekTime)
{
	MediaPlayer->Seek(SeekTime.ToTimespan(GetFrameRate()));
	return Super::SeekMovieScene(SeekTime);
}

void UGenericMediaHandle::ChangeMovieSceneDirection()
{
	PlayReverseMovieScene();
}

bool UGenericMediaHandle::IsPlaying()
{
	return MediaPlayer->IsPlaying();
}

bool UGenericMediaHandle::IsLooping()
{
	return MediaPlayer->IsLooping();
}

bool UGenericMediaHandle::IsPaused()
{
	return MediaPlayer->IsPaused();
}

bool UGenericMediaHandle::IsReversed()
{
	return Super::IsReversed();
}

FTimecode UGenericMediaHandle::GetCurrentTime()
{
	return FTimecode::FromTimespan(MediaPlayer->GetTime(), GetFrameRate(), true);
}

FTimecode UGenericMediaHandle::GetDuration()
{
	return FTimecode::FromTimespan(MediaPlayer->GetDuration(), GetFrameRate(), true);
}

FFrameRate UGenericMediaHandle::GetFrameRate()
{
	FString MediaInfo = MediaPlayer->GetPlayerFacade()->GetInfo();
	MediaInfo.Split("Frame Rate:", nullptr, &MediaInfo);
	MediaInfo.Split("fps", &MediaInfo, nullptr);

	const int32 FrameRate = FCString::Atoi(*MediaInfo);

	return FFrameRate(FrameRate, 1);
}

void UGenericMediaHandle::SetFrameRate(FFrameRate FrameRate)
{
	Super::SetFrameRate(FrameRate);
}

float UGenericMediaHandle::GetPlayRate()
{
	return MediaPlayer->GetRate() < 0;
}

void UGenericMediaHandle::SetPlayRate(float InPlayRate)
{
	MediaPlayer->SetRate(InPlayRate);
}

bool UGenericMediaHandle::HasError() const
{
	return MediaPlayer->HasError();
}

bool UGenericMediaHandle::IsBuffering() const
{
	return MediaPlayer->IsBuffering();
}

bool UGenericMediaHandle::IsConnecting() const
{
	return MediaPlayer->IsConnecting();
}

bool UGenericMediaHandle::IsPreparing() const
{
	return MediaPlayer->IsPreparing();
}

bool UGenericMediaHandle::IsClosed() const
{
	return MediaPlayer->IsClosed();
}

bool UGenericMediaHandle::IsReady() const
{
	return MediaPlayer->IsReady();
}

bool UGenericMediaHandle::CanPause() const
{
	return MediaPlayer->CanPause();
}

bool UGenericMediaHandle::CanPlaySource(UMediaSource* InMediaSource) const
{
	return MediaPlayer->CanPlaySource(InMediaSource);
}

bool UGenericMediaHandle::CanPlayUrl(const FString& Url) const
{
	return MediaPlayer->CanPlayUrl(Url);
}

FText UGenericMediaHandle::GetMediaName() const
{
	return MediaPlayer->GetMediaName();
}

FName UGenericMediaHandle::GetPlayerName() const
{
	return MediaPlayer->GetPlayerName();
}

FName UGenericMediaHandle::GetDesiredPlayerName() const
{
	return MediaPlayer->GetDesiredPlayerName();
}

void UGenericMediaHandle::GetSupportedRates(TArray<FFloatRange>& OutRates, bool Unthinned) const
{
	MediaPlayer->GetSupportedRates(OutRates, Unthinned);
}

const FString& UGenericMediaHandle::GetUrl() const
{
	return MediaPlayer->GetUrl();
}

void UGenericMediaHandle::SetBlockOnTime(const FTimespan& Time) const
{
	MediaPlayer->SetBlockOnTime(Time);
}

void UGenericMediaHandle::SetBlockOnTimeRange(const TRange<FTimespan>& TimeRange) const
{
	MediaPlayer->SetBlockOnTimeRange(TimeRange);
}

bool UGenericMediaHandle::SetLooping(bool Looping) const
{
	return MediaPlayer->SetLooping(Looping);
}

bool UGenericMediaHandle::SetNativeVolume(float Volume)
{
	return MediaPlayer->SetNativeVolume(Volume);
}

FTimespan UGenericMediaHandle::GetTimeDelay() const
{
	return MediaPlayer->GetTimeDelay();
}

void UGenericMediaHandle::SetTimeDelay(FTimespan TimeDelay)
{
	return MediaPlayer->SetTimeDelay(TimeDelay);
}

bool UGenericMediaHandle::SupportsRate(float Rate, bool Unthinned) const
{
	return MediaPlayer->SupportsRate(Rate, Unthinned);
}

bool UGenericMediaHandle::SupportsScrubbing() const
{
	return MediaPlayer->SupportsScrubbing();
}

bool UGenericMediaHandle::SupportsSeeking() const
{
	return MediaPlayer->SupportsSeeking();
}

int32 UGenericMediaHandle::GetNumTracks(EMediaPlayerTrack TrackType) const
{
	return MediaPlayer->GetNumTracks(TrackType);
}

int32 UGenericMediaHandle::GetNumTrackFormats(EMediaPlayerTrack TrackType, int32 TrackIndex) const
{
	return MediaPlayer->GetNumTrackFormats(TrackType, TrackIndex);
}

int32 UGenericMediaHandle::GetSelectedTrack(EMediaPlayerTrack TrackType) const
{
	return MediaPlayer->GetSelectedTrack(TrackType);
}

FText UGenericMediaHandle::GetTrackDisplayName(EMediaPlayerTrack TrackType, int32 TrackIndex) const
{
	return MediaPlayer->GetTrackDisplayName(TrackType, TrackIndex);
}

int32 UGenericMediaHandle::GetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex) const
{
	return MediaPlayer->GetTrackFormat(TrackType, TrackIndex);
}

FString UGenericMediaHandle::GetTrackLanguage(EMediaPlayerTrack TrackType, int32 TrackIndex) const
{
	return MediaPlayer->GetTrackLanguage(TrackType, TrackIndex);
}

bool UGenericMediaHandle::SelectTrack(EMediaPlayerTrack TrackType, int32 TrackIndex)
{
	return MediaPlayer->SelectTrack(TrackType, TrackIndex);
}

bool UGenericMediaHandle::SetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex, int32 FormatIndex)
{
	return MediaPlayer->SetTrackFormat(TrackType, TrackIndex, FormatIndex);
}

int32 UGenericMediaHandle::GetAudioTrackChannels(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetAudioTrackChannels(TrackIndex, FormatIndex);
}

FString UGenericMediaHandle::GetAudioTrackType(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetAudioTrackType(TrackIndex, FormatIndex);
}

int32 UGenericMediaHandle::GetAudioTrackSampleRate(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetAudioTrackSampleRate(TrackIndex, FormatIndex);
}

FString UGenericMediaHandle::GetVideoTrackType(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackType(TrackIndex, FormatIndex);
}

float UGenericMediaHandle::GetVideoTrackAspectRatio(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackAspectRatio(TrackIndex, FormatIndex);
}

FIntPoint UGenericMediaHandle::GetVideoTrackDimensions(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackDimensions(TrackIndex, FormatIndex);
}

float UGenericMediaHandle::GetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackFrameRate(TrackIndex, FormatIndex);
}

FFloatRange UGenericMediaHandle::GetVideoTrackFrameRates(int32 TrackIndex, int32 FormatIndex) const
{
	return MediaPlayer->GetVideoTrackFrameRates(TrackIndex, FormatIndex);
}

bool UGenericMediaHandle::SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate)
{
	return MediaPlayer->SetVideoTrackFrameRate(TrackIndex, FormatIndex, FrameRate);
}

float UGenericMediaHandle::GetHorizontalFieldOfView() const
{
	return MediaPlayer->GetHorizontalFieldOfView();
}

float UGenericMediaHandle::GetVerticalFieldOfView() const
{
	return MediaPlayer->GetVerticalFieldOfView();
}

FRotator UGenericMediaHandle::GetViewRotation() const
{
	return MediaPlayer->GetViewRotation();
}

bool UGenericMediaHandle::SetViewField(float Horizontal, float Vertical, bool Absolute)
{
	return MediaPlayer->SetViewField(Horizontal, Vertical, Absolute);
}

bool UGenericMediaHandle::SetViewRotation(const FRotator& Rotation, bool Absolute)
{
	return MediaPlayer->SetViewRotation(Rotation, Absolute);
}

UMediaPlayer* UGenericMediaHandle::GetMediaPlayer() const
{
	return MediaPlayer;
}

UMediaSource* UGenericMediaHandle::GetMediaSource() const
{
	return MediaPlayer->GetPlaylist()->Get(MediaPlayer->GetPlaylistIndex());
}

void UGenericMediaHandle::OnMediaOpened(FString OpenedUrl)
{
	bIsMediaInitialize = true;
	OnMovieSceneOpened();

	PlayMovieSceneFromStart();
	MediaPlayer->SetRate(10.f);
}

void UGenericMediaHandle::OnMediaOpenFailed(FString FailedUrl)
{
	GenericLOG(GenericLogMovieScene, Error, TEXT("Media Open Fail : %s"), *FailedUrl)
}

void UGenericMediaHandle::OnMediaClosed()
{
	OnMovieSceneStop();
}

void UGenericMediaHandle::OnEndReached()
{
	OnMovieScenePlayFinish();
}

void UGenericMediaHandle::OnSeekCompleted()
{
	OnMovieSceneSeek();
}

void UGenericMediaHandle::OnPlaybackSuspended()
{
	OnMovieScenePause();
}

void UGenericMediaHandle::OnPlaybackResumed()
{
	OnMovieScenePlay();
}
