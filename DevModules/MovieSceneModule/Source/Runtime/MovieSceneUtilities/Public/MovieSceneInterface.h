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

public:
	virtual void OpenMovieScene();
	virtual void CloseMovieScene();

	virtual bool PlayMovieScene();
	virtual bool PlayMovieSceneFromStart();
	virtual bool PlayLoopingMovieScene(int32 NumLoops = -1);
	virtual bool PlayReverseMovieScene();
	virtual bool PauseMovieScene();
	virtual bool StopMovieScene();
	virtual bool SeekMovieScene(FTimecode SeekTime);

	virtual void ChangeMovieSceneDirection() { return; }

	virtual bool IsPlaying() { return false; }
	virtual bool IsLooping() { return false; }
	virtual bool IsPaused() { return false; }
	virtual bool IsReversed() { return false; }
	
	virtual FTimecode GetCurrentTime() { return FTimecode(); }
	virtual FTimecode GetDuration() { return FTimecode(); }

	virtual FFrameRate GetFrameRate() { return FFrameRate(); }
	virtual void SetFrameRate(FFrameRate FrameRate) { return; }

	virtual float GetPlayRate() { return 1.f; }
	virtual void SetPlayRate(float InPlayRate) { return; }

protected:
	virtual void OnMovieSceneOpened() { return; }
	virtual void OnMovieSceneClosed() { return; }

	virtual void OnMovieScenePlay() { return; }
	virtual void OnMovieScenePlayReverse() { return; }
	virtual void OnMovieScenePause() { return; }
	virtual void OnMovieSceneStop() { return; }
	virtual void OnMovieSceneSeek() { return; }
	virtual void OnMovieScenePlayFinish() { return; }
};
