// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneType.h"
#include "MovieSceneInterface.generated.h"

class UUserWidgetBase;
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

protected:
	virtual void OpenMovieScene();
	virtual void CloseMovieScene();

	virtual void OnMovieSceneOpened() { return; }
	virtual void OnMovieSceneClosed() { return; }

public:
	virtual void PlayMovieScene() { return; }
	virtual void PlayReverseMovieScene() { return; }
	virtual void PauseMovieScene() { return; }
	virtual void StopMovieScene() { return; }
	virtual void SeekMovieScene(int32 InDays, int32 InHours, int32 InMinutes, int32 InSeconds, int32 InMicroSeconds) { return; }

protected:
};
