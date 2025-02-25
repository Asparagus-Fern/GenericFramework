// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneMediaPlaybackSettings.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RegisterMediaHandleAction.generated.h"

class UMediaHandle;
class UMediaSource;
class UMediaPlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRegisterMediaHandleDelegate, UMediaHandle*, MediaHandle, FString, MediaURL);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRegisterMediaHandleFailDelegate);

/**
 * 
 */
UCLASS()
class MEDIASYSTEM_API URegisterMediaHandleAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(HandleName = "DefaultMediaHandle", BlueprintInternalUseOnly = "true"), DisplayName="RegisterMediaHandle (MediaSourse)")
	static URegisterMediaHandleAction* RegisterMediaHandleByMediaSourse(FName HandleName, UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, FMovieSceneMediaPlaybackSettings InSettings = FMovieSceneMediaPlaybackSettings());

	UFUNCTION(BlueprintCallable, meta=(HandleName = "DefaultMediaHandle", BlueprintInternalUseOnly = "true"), DisplayName="RegisterMediaHandle (MediaPlaylist)")
	static URegisterMediaHandleAction* RegisterMediaHandleByMediaPlaylist(FName HandleName, UMediaPlayer* InMediaPlayer, UMediaSource* InMediaPlaylist, FMovieSceneMediaPlaybackSettings InSettings = FMovieSceneMediaPlaybackSettings());

private:
	UPROPERTY()
	UMediaHandle* MediaHandle;

	UPROPERTY(BlueprintAssignable)
	FRegisterMediaHandleDelegate Success;

	UPROPERTY(BlueprintAssignable)
	FRegisterMediaHandleFailDelegate Fail;

	UFUNCTION()
	void OnMediaOpened(FString OpenedUrl);

	UFUNCTION()
	void OnMediaOpenFailed(FString FailedUrl);
};
