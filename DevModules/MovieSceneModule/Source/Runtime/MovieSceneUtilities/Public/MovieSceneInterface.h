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

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void LoadMovieSceneDataSource();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void SetMovieSceneSetting(FMovieSceneSetting InMovieSceneSetting);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void Play();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void Pause();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void Stop();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Base")
	void Seek(FTimespan InTime);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Setter")
	void SetMovieSceneState(EMovieSceneState InMovieSceneState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Setter")
	void SetMovieSceneLoopSetting(FMovieSceneLoopSetting InMovieSceneLoopSetting);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | Delegate")
	void OnMovieSceneFinish();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movie Scene Interface | UI")
	void RefreshMovieScenePanel(EMovieSceneState InMovieSceneState, TSubclassOf<UMovieScenePanel> InMovieScenePanelClass);

	virtual void OpenMovieScenePanel(TSubclassOf<UMovieScenePanel> InMovieScenePanel) { return; }
	virtual void CloseMovieScenePanel() { return; }

public:
	virtual FTimespan GetTime() = 0;
};
