// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneType.h"
#include "MovieSceneInterface.generated.h"

class UMovieScenePanel;

UINTERFACE(MinimalAPI)
class UMovieSceneInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOVIESCENEUTILITIES_API IMovieSceneInterface
{
	GENERATED_BODY()

	/* Base */
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void OpenMovieScene();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void CloseMovieScene();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void SetMovieSceneSetting(FMovieSceneSetting InMovieSceneSetting);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void Play();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void Pause();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void Stop();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void Seek(int32 InDays, int32 InHours, int32 InMinutes, int32 InSeconds, int32 InMicroSeconds);

	/* Setter */
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Setter")
	void SetMovieSceneState(EMovieSceneState InMovieSceneState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Setter")
	void SetMovieSceneLoopSetting(FMovieSceneLoopSetting InMovieSceneLoopSetting);

	/* Delegate */
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Delegate")
	void OnMovieSceneOpenFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Delegate")
	void OnMovieScenePlayFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Delegate")
	void OnMovieSceneSeekFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Delegate")
	void OnMovieSceneCloseFinish();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | UI")
	void RefreshMovieScenePanel(EMovieSceneState InMovieSceneState, TSubclassOf<UMovieScenePanel> InMovieScenePanelClass);

protected:
	virtual void OpenMovieScenePanel(TSubclassOf<UMovieScenePanel> InMovieScenePanel) { return; }
	virtual void CloseMovieScenePanel() { return; }
};
