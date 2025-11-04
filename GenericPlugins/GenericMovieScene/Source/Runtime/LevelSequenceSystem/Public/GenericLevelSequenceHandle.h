// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericMovieSceneHandle.h"
#include "MovieSceneSequencePlayer.h"
#include "GenericLevelSequenceHandle.generated.h"

class ULevelSequence;
class ULevelSequencePlayer;
class ALevelSequenceActor;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericLevelSequenceHandle : public UGenericMovieSceneHandle
{
	GENERATED_BODY()
	
	/* IMovieSceneInterface */
protected:
	LEVELSEQUENCESYSTEM_API virtual void OnMovieSceneOpened() override;
	LEVELSEQUENCESYSTEM_API virtual void OnMovieSceneClosed() override;

public:
	/* Start playback forwards from the current time cursor position, using the current play rate. */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual bool PlayMovieScene() override;

	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual bool PlayMovieSceneFromStart() override;

	/**
	 * Start playback from the current time cursor position, looping the specified number of times.
	 * @param NumLoops - The number of loops to play. -1 indicates infinite looping.
	 */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual bool PlayLoopingMovieScene(int32 NumLoops = -1) override;

	/* Reverse playback. */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual bool PlayReverseMovieScene() override;

	/* Pause playback. */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual bool PauseMovieScene() override;

	/* Stop playback and move the cursor to the end (or start, for reversed playback) of the sequence. */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual bool StopMovieScene() override;

	/**
	 * Set the current time of the player by evaluating from the current time to the specified time, as if the sequence is playing. 
	 * Triggers events that lie within the evaluated range. Does not alter the persistent playback status of the player (IsPlaying).
	 */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual bool SeekMovieScene(FTimecode SeekTime) override;

	/* Changes the direction of playback (go in reverse if it was going forward, or vice versa) */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual void ChangeMovieSceneDirection() override;

	/* Check whether the sequence is actively playing. */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API virtual bool IsPlaying() override;

	/* Check whether the sequence is Looping. */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API virtual bool IsLooping() override;

	/* Check whether the sequence is paused. */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API virtual bool IsPaused() override;

	/* Check whether playback is reversed. */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API virtual bool IsReversed() override;

	/* Get the current playback position */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API virtual FTimecode GetCurrentTime() override;

	/* Get the total duration of the sequence */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API virtual FTimecode GetDuration() override;

	/* Get this sequence's display rate. */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API virtual FFrameRate GetFrameRate() override;

	/* Set the frame-rate that this player should play with, making all frame numbers in the specified time-space */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual void SetFrameRate(FFrameRate FrameRate) override;

	/* Get the playback rate of this player. */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API virtual float GetPlayRate() override;

	/* Set the playback rate of this player. Negative values will play the animation in reverse. */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API virtual void SetPlayRate(float InPlayRate) override;

	/* ULevelSequenceHandle */
public:
	/**
	 * Set the valid play range for this sequence, determined by a starting time  and a duration (in seconds)
	 * @param StartTime       The time to start playing back the sequence in seconds
	 * @param Duration        The length to play for
	 */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API void SetTimeRange(float StartTime, float Duration);

	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API bool GetDisableCameraCuts() const;

	/* Set whether to disable camera cuts */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API void SetDisableCameraCuts(bool bInDisableCameraCuts);

public:
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API ALevelSequenceActor* GetLevelSequenceActor() const;

	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API ULevelSequencePlayer* GetULevelSequencePlayer() const;

	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API FString GetSequenceName() const;

public:
	/* Get the level sequence being played by this actor. */
	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API ULevelSequence* GetSequence() const;

	/* Set the level sequence being played by this actor. */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API void SetSequence(ULevelSequence* InSequence, bool bIsPlay = true);

	UFUNCTION(BlueprintPure)
	LEVELSEQUENCESYSTEM_API FMovieSceneSequencePlaybackSettings GetPlaybackSettings() const;

	/* Assign this player's playback settings */
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API void SetPlaybackSettings(const FMovieSceneSequencePlaybackSettings& InSettings);

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
