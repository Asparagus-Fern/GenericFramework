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
	virtual void LoadMovieSceneDataSource_Implementation() override;
	virtual void Play_Implementation() override;
	virtual void Pause_Implementation() override;
	virtual void Stop_Implementation() override;
	virtual void Seek_Implementation(FTimespan InTime) override;

	virtual void SetMovieSceneLoopSetting_Implementation(FMovieSceneLoopSetting InMovieSceneLoopSetting) override;

	virtual FTimespan GetTime() override;

	/* UMediaHandle */
protected:
	UFUNCTION()
	void OnEndReached();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	UMediaPlayer* MediaPlayer = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	UMediaPlaylist* MediaPlaylist = nullptr;

protected:
	FSimpleMulticastDelegate OnOpened;
	FSimpleMulticastDelegate OnOpenFailed;
};
