// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneInterface.h"
#include "Handle/MovieSceneHandleBase.h"

#include "MediaHandle.generated.h"

class UMediaPlaylist;
class UMediaSource;
class UMediaPlayer;

/**
 * 
 */
UCLASS()
class MEDIASYSTEM_API UMediaHandle : public UMovieSceneHandleBase
{
	GENERATED_BODY()

	/* UHandleBase */
public:
	virtual void ClearHandle_Implementation() override;

	/* FMovieSceneInterface */
public:
	virtual void OpenMovieScene_Implementation() override;
	virtual void CloseMovieScene_Implementation() override;

	virtual void Open_Implementation() override;
	virtual void Play_Implementation() override;
	virtual void Pause_Implementation() override;
	virtual void Stop_Implementation() override;
	virtual void Seek_Implementation(int32 InDays, int32 InHours, int32 InMinutes, int32 InSeconds, int32 InMicroSeconds) override;

	virtual void SetMovieSceneLoopSetting_Implementation(FMovieSceneLoopSetting InMovieSceneLoopSetting) override;

	virtual void OnOpenMovieScenePanelFinish(UUserWidgetBase* InWidget) override;
	virtual void OnCloseMovieScenePanelFinish(UUserWidgetBase* InWidget) override;
	
	/* UMovieSceneHandleBase */
public:
	virtual FTimespan GetMovieSceneCurrentTime_Implementation() override;

	/* UMediaHandle */
protected:
	UFUNCTION()
	void OnMediaOpened(FString OpenedUrl);

	UFUNCTION()
	void OnEndReached();

	UFUNCTION()
	void OnPlaybackSuspended();
	
	UFUNCTION()
	void OnSeekCompleted();

	UFUNCTION()
	void OnMediaClosed();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	UMediaPlayer* MediaPlayer = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	UMediaPlaylist* MediaPlaylist = nullptr;

protected:
	FSimpleMulticastDelegate OnOpened;
	FSimpleMulticastDelegate OnOpenFailed;
};
