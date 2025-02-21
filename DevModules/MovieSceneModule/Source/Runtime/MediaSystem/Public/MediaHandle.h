// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneInterface.h"
#include "Handle/MovieSceneHandleBase.h"

#include "MediaHandle.generated.h"

class UMediaSource;
class UMediaPlayer;

/**
 * 
 */
UCLASS()
class MEDIASYSTEM_API UMediaHandle : public UMovieSceneHandleBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(HandleName = "DefaultMediaHandle"))
	static UMediaHandle* RegisterMediaHandle(FName HandleName, UMediaSource* InMediaSource);

	/* IMovieSceneInterface */
protected:
	virtual void OnMovieSceneOpened() override;
	virtual void OnMovieSceneClosed() override;

public:
	/** Starts media playback. */
	UFUNCTION(BlueprintCallable)
	virtual void PlayMovieScene() override;

	/* UMediaHandle */
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

public:
	UPROPERTY(Transient)
	TObjectPtr<UMediaPlayer> MediaPlayer = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UMediaSource> MediaSource = nullptr;
};
