// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MediaPlayer.h"
#include "MovieSceneMediaPlaybackSettings.h"
#include "Handle/MovieSceneHandleBase.h"

#include "MediaHandle.generated.h"

class UMediaSource;
class UMediaPlayer;

/**
 * 
 */
UCLASS(MinimalAPI)
class UMediaHandle : public UMovieSceneHandleBase
{
	GENERATED_UCLASS_BODY()

public:
	void Register(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, FMovieSceneMediaPlaybackSettings InSettings = FMovieSceneMediaPlaybackSettings());
	void Register(UMediaPlayer* InMediaPlayer, UMediaPlaylist* InMediaPlaylist, FMovieSceneMediaPlaybackSettings InSettings = FMovieSceneMediaPlaybackSettings());

	/* IMovieSceneInterface */
public:
	virtual void OpenMovieScene() override;
	virtual void CloseMovieScene() override;

protected:
	virtual void OnMovieSceneOpened() override;
	virtual void OnMovieSceneClosed() override;

public:
	/** Starts media playback. */
	UFUNCTION(BlueprintCallable)
	virtual bool PlayMovieScene() override;

	/* Starts playback from the media opened event */
	UFUNCTION(BlueprintCallable)
	virtual bool PlayMovieSceneFromStart() override;

	/**
	 * Start playback from the current time cursor position, looping the specified number of times.
	 * @param NumLoops - The number of loops to play. -1 indicates infinite looping.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool PlayLoopingMovieScene(int32 NumLoops = -1) override;

	/** Reverse playback. */
	UFUNCTION(BlueprintCallable)
	virtual bool PlayReverseMovieScene() override;

	/** Pause playback. */
	UFUNCTION(BlueprintCallable)
	virtual bool PauseMovieScene() override;

	/** Stop playback and move the cursor to the end of the media. */
	UFUNCTION(BlueprintCallable)
	virtual bool StopMovieScene() override;

	/* Seeks to the specified playback time. */
	UFUNCTION(BlueprintCallable)
	virtual bool SeekMovieScene(FTimecode SeekTime) override;

	/** Changes the direction of playback (go in reverse if it was going forward, or vice versa) */
	UFUNCTION(BlueprintCallable)
	virtual void ChangeMovieSceneDirection() override;

	/** Check whether playback has started. */
	UFUNCTION(BlueprintPure)
	virtual bool IsPlaying() override;

	/** Check whether playback is Looping. */
	UFUNCTION(BlueprintPure)
	virtual bool IsLooping() override;

	/** Check whether playback is currently paused. */
	UFUNCTION(BlueprintPure)
	virtual bool IsPaused() override;

	/** Check whether playback is reversed. */
	UFUNCTION(BlueprintPure)
	virtual bool IsReversed() override;

	/* Get the media's current playback time. */
	UFUNCTION(BlueprintPure)
	virtual FTimecode GetCurrentTime() override;

	/** Get the media's duration. */
	UFUNCTION(BlueprintPure)
	virtual FTimecode GetDuration() override;

	/* Get this media's display rate. */
	UFUNCTION(BlueprintPure)
	virtual FFrameRate GetFrameRate() override;

	/* !!! Media can not set frame rate. !!! */
	UFUNCTION(BlueprintCallable)
	virtual void SetFrameRate(FFrameRate FrameRate) override;

	/** Get the media's current playback rate. */
	UFUNCTION(BlueprintPure)
	virtual float GetPlayRate() override;

	/* Changes the media's playback rate. todo:If Set a High PlayRate,The Media Is Already Play Finish,But The Delegate OnEndReached May Not Called */
	UFUNCTION(BlueprintCallable)
	virtual void SetPlayRate(float InPlayRate) override;

	/* UMediaHandle */
public:
	/* Check whether the player is in an error state. */
	UFUNCTION(BlueprintPure)
	bool HasError() const;

	/* Check whether playback is buffering data. */
	UFUNCTION(BlueprintPure)
	bool IsBuffering() const;

	/* Check whether the player is currently connecting to a media source. */
	UFUNCTION(BlueprintPure)
	bool IsConnecting() const;

	/* Check whether the media is currently opening or buffering. */
	UFUNCTION(BlueprintPure)
	bool IsPreparing() const;

	/* Whether media is currently closed. */
	UFUNCTION(BlueprintPure)
	bool IsClosed() const;

	UFUNCTION(BlueprintPure)
	bool IsReady() const;

	/* Check whether media playback can be paused right now. */
	UFUNCTION(BlueprintPure)
	bool CanPause() const;

	/* Check whether the specified media source can be played by this player. */
	UFUNCTION(BlueprintPure)
	bool CanPlaySource(UMediaSource* InMediaSource) const;

	/* Check whether the specified URL can be played by this player. */
	UFUNCTION(BlueprintPure)
	bool CanPlayUrl(const FString& Url) const;

	/* Get the human readable name of the currently loaded media source. */
	UFUNCTION(BlueprintPure)
	virtual FText GetMediaName() const;

	UFUNCTION(BlueprintPure)
	FName GetPlayerName() const;

	/* Get the name of the current desired native player. */
	UFUNCTION(BlueprintPure)
	FName GetDesiredPlayerName() const;

	/**
	 * Get the supported playback rates.
	 *
	 * @param OutRates contain the the ranges of supported rates.
	 * @param Unthinned Whether the rates are for unthinned playback.
	 */
	UFUNCTION(BlueprintPure)
	void GetSupportedRates(TArray<FFloatRange>& OutRates, bool Unthinned) const;

	/* Get the URL of the currently loaded media, if any. */
	UFUNCTION(BlueprintPure)
	const FString& GetUrl() const;

	/**
	 * Set the time on which to block.
	 *
	 * If set, this player will block in TickInput or TickFetch until the video sample
	 * for the specified time are actually available.
	 *
	 * @param Time The time to block on, or FTimespan::MinValue to disable.
	 */
	UFUNCTION(BlueprintCallable)
	void SetBlockOnTime(const FTimespan& Time) const;

	/**
	 * Set the time range on which to block.
	 *
	 * If set, this player will block in TickInput or TickFetch until the video sample
	 * for the specified time are actually available.
	 *
	 * @param TimeRange The time range to block on, or empty range to disable.
	 */
	void SetBlockOnTimeRange(const TRange<FTimespan>& TimeRange) const;

	/**
	 * Enables or disables playback looping.
	 *
	 * @param Looping Whether playback should be looped.
	 * @return true on success, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	bool SetLooping(bool Looping) const;

	/**
	 * Set the volume on the native player if not mixing with Sound Wave asset.
	 *
	 * The SetNativeVolume can be used to change the audio output volume at runtime. Note that
	 * not all media player plug-ins may support native audio output on all platforms.
	 *
	 * @param Volume The volume to set.
	 * @return true on success, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool SetNativeVolume(float Volume);

	/**
	 * Delay of the player's time.
	 *
	 * @return Delay added to the player's time used to manually sync multiple sources.
	 */
	UFUNCTION(BlueprintPure)
	FTimespan GetTimeDelay() const;

	/**
	 * Delay of the player's time.
	 *
	 * This setting can be used to manually sync multiple sources.
	 * Set to 1 seconds, if you would like that Player to play 1 second behind its current time.
	 * If the value is too big, it is possible that the player would not hold that frame for that long.
	 * @return true on success, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	void SetTimeDelay(FTimespan TimeDelay);

	/**
	 * Check whether the specified playback rate is supported.
	 *
	 * @param Rate The playback rate to check.
	 * @param Unthinned Whether no frames should be dropped at the given rate.
	 */
	UFUNCTION(BlueprintPure)
	bool SupportsRate(float Rate, bool Unthinned) const;

	/**
	 * Check whether the currently loaded media supports scrubbing.
	 *
	 * @return true if scrubbing is supported, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	bool SupportsScrubbing() const;

	/**
	 * Check whether the currently loaded media can jump to a certain position.
	 *
	 * @return true if seeking is supported, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	bool SupportsSeeking() const;

public:
	/**
	 * Get the number of tracks of the given type.
	 *
	 * @param TrackType The type of media tracks.
	 * @return Number of tracks.
	 */
	UFUNCTION(BlueprintPure)
	int32 GetNumTracks(EMediaPlayerTrack TrackType) const;

	/**
	 * Get the number of formats of the specified track.
	 *
	 * @param TrackType The type of media tracks.
	 * @param TrackIndex The index of the track.
	 * @return Number of formats.
	 */
	UFUNCTION(BlueprintPure)
	int32 GetNumTrackFormats(EMediaPlayerTrack TrackType, int32 TrackIndex) const;

	/**
	 * Get the index of the currently selected track of the given type.
	 *
	 * @param TrackType The type of track to get.
	 * @return The index of the selected track, or INDEX_NONE if no track is active.
	 */
	UFUNCTION(BlueprintPure)
	int32 GetSelectedTrack(EMediaPlayerTrack TrackType) const;

	/**
	 * Get the human readable name of the specified track.
	 *
	 * @param TrackType The type of track.
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @return Display name.
	 */
	UFUNCTION(BlueprintPure)
	FText GetTrackDisplayName(EMediaPlayerTrack TrackType, int32 TrackIndex) const;

	/**
	 * Get the index of the active format of the specified track type.
	 *
	 * @param TrackType The type of track.
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @return The index of the selected format.
	 */
	UFUNCTION(BlueprintPure)
	int32 GetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex) const;

	/**
	 * Get the language tag of the specified track.
	 *
	 * @param TrackType The type of track.
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @return Language tag, i.e. "en-US" for English, or "und" for undefined.
	 */
	UFUNCTION(BlueprintPure)
	FString GetTrackLanguage(EMediaPlayerTrack TrackType, int32 TrackIndex) const;

	/**
	 * Select the active track of the given type.
	 *
	 * The selected track will use its currently active format. Active formats will
	 * be remembered on a per track basis. The first available format is active by
	 * default. To switch the track format, use SetTrackFormat instead.
	 *
	 * @param TrackType The type of track to select.
	 * @param TrackIndex The index of the track to select, or INDEX_NONE to deselect.
	 * @return true if the track was selected, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool SelectTrack(EMediaPlayerTrack TrackType, int32 TrackIndex);

	/**
	 * Set the format on the specified track.
	 *
	 * Selecting the format will not switch to the specified track. To switch
	 * tracks, use SelectTrack instead. If the track is already selected, the
	 * format change will be applied immediately.
	 *
	 * @param TrackType The type of track to update.
	 * @param TrackIndex The index of the track to update.
	 * @param FormatIndex The index of the format to select (must be valid).
	 * @return true if the track was selected, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool SetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex, int32 FormatIndex);

	/**
	 * Get the number of channels in the specified audio track.
	 *
	 * @param TrackIndex Index of the audio track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @return Number of channels.
	 */
	UFUNCTION(BlueprintPure)
	int32 GetAudioTrackChannels(int32 TrackIndex, int32 FormatIndex) const;

	/**
	 * Get the type of the specified audio track format.
	 *
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @return Audio format type string.
	 */
	UFUNCTION(BlueprintPure)
	FString GetAudioTrackType(int32 TrackIndex, int32 FormatIndex) const;

	/**
	 * Get the sample rate of the specified audio track.
	 *
	 * @param TrackIndex Index of the audio track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @return Samples per second.
	 */
	UFUNCTION(BlueprintPure)
	int32 GetAudioTrackSampleRate(int32 TrackIndex, int32 FormatIndex) const;

	/**
	 * Get the type of the specified video track format.
	 *
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @return Video format type string.
	 * @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackFrameRates
	 */
	UFUNCTION(BlueprintPure)
	FString GetVideoTrackType(int32 TrackIndex, int32 FormatIndex) const;

	/**
	 * Get the aspect ratio of the specified video track.
	 *
	 * @param TrackIndex Index of the video track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @return Aspect ratio.
	 */
	UFUNCTION(BlueprintPure)
	float GetVideoTrackAspectRatio(int32 TrackIndex, int32 FormatIndex) const;

	/**
	 * Get the current dimensions of the specified video track.
	 *
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @return Video dimensions (in pixels).
	 */
	UFUNCTION(BlueprintPure)
	FIntPoint GetVideoTrackDimensions(int32 TrackIndex, int32 FormatIndex) const;

	/**
	 * Get the frame rate of the specified video track.
	 *
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @return Frame rate (in frames per second).
	 */
	UFUNCTION(BlueprintPure)
	float GetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex) const;

	/**
	 * Get the supported range of frame rates of the specified video track.
	 *
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @return Frame rate range (in frames per second).
	 */
	UFUNCTION(BlueprintPure)
	FFloatRange GetVideoTrackFrameRates(int32 TrackIndex, int32 FormatIndex) const;

	/**
	 * Set the frame rate of the specified video track.
	 *
	 * @param TrackIndex The index of the track, or INDEX_NONE for the selected one.
	 * @param FormatIndex Index of the track format, or INDEX_NONE for the selected one.
	 * @param FrameRate The frame rate to set (must be in range of format's supported frame rates).
	 * @return true on success, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate);

public:
	/* Only for 360 videos : Get the current horizontal field of view (in Euler degrees). */
	UFUNCTION(BlueprintPure)
	float GetHorizontalFieldOfView() const;

	/* Only for 360 videos : Get the current vertical field of view (in Euler degrees). */
	UFUNCTION(BlueprintPure)
	float GetVerticalFieldOfView() const;

	/* Only for 360 videos : Get the current view rotation. */
	UFUNCTION(BlueprintPure)
	FRotator GetViewRotation() const;

	/**
	 * Only for 360 videos : Set the field of view.
	 *
	 * @param Horizontal Horizontal field of view (in Euler degrees).
	 * @param Vertical Vertical field of view (in Euler degrees).
	 * @param Absolute the field of view change should be absolute (true) or relative (false).
	 * @return true on success, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool SetViewField(float Horizontal, float Vertical, bool Absolute);

	/**
	 * Set the view's rotation (only for 360 videos).
	 *
	 * @param Rotation The desired view rotation.
	 * @param Absolute the rotation change should be absolute (true) or relative (false).
	 * @return true on success, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool SetViewRotation(const FRotator& Rotation, bool Absolute);

public:
	UFUNCTION(BlueprintPure)
	UMediaPlayer* GetMediaPlayer() const;

	UFUNCTION(BlueprintPure)
	UMediaSource* GetMediaSource() const;

private:
	UFUNCTION()
	void OnMediaOpened(FString OpenedUrl);

	UFUNCTION()
	void OnMediaOpenFailed(FString FailedUrl);

	UFUNCTION()
	void OnMediaClosed();

	UFUNCTION()
	void OnEndReached();

	UFUNCTION()
	void OnSeekCompleted();

	UFUNCTION()
	void OnPlaybackSuspended();

	UFUNCTION()
	void OnPlaybackResumed();

public:
	UPROPERTY(Transient)
	TObjectPtr<UMediaPlayer> MediaPlayer = nullptr;

private:
	UPROPERTY()
	FMovieSceneMediaPlaybackSettings PlaybackSettings;

	uint8 bIsMediaInitialize : 1;
	int32 LoopCount = 0;
};
