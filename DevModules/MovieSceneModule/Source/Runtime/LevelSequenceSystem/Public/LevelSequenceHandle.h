// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneInterface.h"
#include "MovieSceneSequencePlayer.h"
#include "Handle/MovieSceneHandleBase.h"
#include "LevelSequenceHandle.generated.h"

class ULevelSequence;
class ULevelSequencePlayer;
class ALevelSequenceActor;

/**
 * 
 */
UCLASS()
class LEVELSEQUENCESYSTEM_API ULevelSequenceHandle : public UMovieSceneHandleBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(HandleName = "DefaultLevelSequenceHandle"))
	static ULevelSequenceHandle* RegisterLevelSequenceHandle(FName HandleName, ULevelSequence* InLevelSequence, FMovieSceneSequencePlaybackSettings InSettings = FMovieSceneSequencePlaybackSettings());

	/* IMovieSceneInterface */
protected:
	virtual void OnMovieSceneOpened() override;
	virtual void OnMovieSceneClosed() override;

public:
	/** Start playback forwards from the current time cursor position, using the current play rate. */
	UFUNCTION(BlueprintCallable)
	virtual bool PlayMovieScene() override;

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

	/** Stop playback and move the cursor to the end (or start, for reversed playback) of the sequence. */
	UFUNCTION(BlueprintCallable)
	virtual bool StopMovieScene() override;

	/**
	 * Set the current time of the player by evaluating from the current time to the specified time, as if the sequence is playing. 
	 * Triggers events that lie within the evaluated range. Does not alter the persistent playback status of the player (IsPlaying).
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SeekMovieScene(FTimecode SeekTime) override;

	/** Changes the direction of playback (go in reverse if it was going forward, or vice versa) */
	UFUNCTION(BlueprintCallable)
	virtual void ChangeMovieSceneDirection() override;

	/** Check whether the sequence is actively playing. */
	UFUNCTION(BlueprintPure)
	virtual bool IsPlaying() override;

	/** Check whether the sequence is Looping. */
	UFUNCTION(BlueprintPure)
	virtual bool IsLooping() override;

	/** Check whether the sequence is paused. */
	UFUNCTION(BlueprintPure)
	virtual bool IsPaused() override;

	/** Check whether playback is reversed. */
	UFUNCTION(BlueprintPure)
	virtual bool IsReversed() override;

	/* Get the current playback position */
	UFUNCTION(BlueprintPure)
	virtual FTimecode GetCurrentTime() override;

	/** Get the total duration of the sequence */
	UFUNCTION(BlueprintPure)
	virtual FTimecode GetDuration() override;

	/* Get this sequence's display rate. */
	UFUNCTION(BlueprintPure)
	virtual FFrameRate GetFrameRate() override;

	/* Set the frame-rate that this player should play with, making all frame numbers in the specified time-space */
	UFUNCTION(BlueprintCallable)
	virtual void SetFrameRate(FFrameRate FrameRate) override;

	/** Get the playback rate of this player. */
	UFUNCTION(BlueprintPure)
	virtual float GetPlayRate() override;

	/* Set the playback rate of this player. Negative values will play the animation in reverse. */
	UFUNCTION(BlueprintCallable)
	virtual void SetPlayRate(float InPlayRate) override;

	/* ULevelSequenceHandle */
public:
	/**
	 * Set the valid play range for this sequence, determined by a starting time  and a duration (in seconds)
	 * @param StartTime       The time to start playing back the sequence in seconds
	 * @param Duration        The length to play for
	 */
	UFUNCTION(BlueprintCallable)
	void SetTimeRange(float StartTime, float Duration);

	UFUNCTION(BlueprintPure)
	bool GetDisableCameraCuts() const;

	/** Set whether to disable camera cuts */
	UFUNCTION(BlueprintCallable)
	void SetDisableCameraCuts(bool bInDisableCameraCuts);

public:
	UFUNCTION(BlueprintPure)
	ALevelSequenceActor* GetLevelSequenceActor() const;

	UFUNCTION(BlueprintPure)
	ULevelSequencePlayer* GetULevelSequencePlayer() const;

	UFUNCTION(BlueprintPure)
	FString GetSequenceName() const;

public:
	/* Get the level sequence being played by this actor. */
	UFUNCTION(BlueprintPure)
	ULevelSequence* GetSequence() const;

	/* Set the level sequence being played by this actor. */
	UFUNCTION(BlueprintCallable)
	void SetSequence(ULevelSequence* InSequence, bool bIsPlay = true);

	UFUNCTION(BlueprintPure)
	FMovieSceneSequencePlaybackSettings GetPlaybackSettings() const;

	/** Assign this player's playback settings */
	UFUNCTION(BlueprintCallable)
	void SetPlaybackSettings(const FMovieSceneSequencePlaybackSettings& InSettings);

private:
	UFUNCTION()
	void OnPlay();

	UFUNCTION()
	void OnPlayReverse();

	UFUNCTION()
	void OnPause();

	UFUNCTION()
	void OnStop();

	UFUNCTION()
	void OnFinished();

public:
	UPROPERTY()
	TObjectPtr<ALevelSequenceActor> LevelSequenceActor = nullptr;

	UPROPERTY()
	TObjectPtr<ULevelSequencePlayer> LevelSequencePlayer = nullptr;

private:
	int32 LoopCount = 0;
};
