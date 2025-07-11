// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneInterface.h"
#include "Handle/HandleBase.h"

#include "MovieSceneHandleBase.generated.h"

class UGenericWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMovieSceneEvent);

/**
 * 
 */
UCLASS(Abstract)
class MOVIESCENEUTILITIES_API UMovieSceneHandleBase : public UHandleBase, public IMovieSceneInterface
{
	GENERATED_BODY()

	/* UHandleBase */
protected:
	virtual void OnRegister() override;
	virtual void OnUnRegister() override;

	/* IMovieSceneInterface */
public:
	DECLARE_EVENT_OneParam(UMovieSceneHandleBase, FLevelSequenceEvent, UMovieSceneHandleBase*)

	FLevelSequenceEvent OnMovieScenePlayEvent;
	FLevelSequenceEvent OnMovieScenePlayReverseEvent;
	FLevelSequenceEvent OnMovieScenePauseEvent;
	FLevelSequenceEvent OnMovieSceneStopEvent;
	FLevelSequenceEvent OnMovieSceneSeekEvent;
	FLevelSequenceEvent OnMovieScenePlayFinishEvent;

protected:
	virtual void OnMovieScenePlay() override;
	virtual void OnMovieScenePlayReverse() override;
	virtual void OnMovieScenePause() override;
	virtual void OnMovieSceneStop() override;
	virtual void OnMovieSceneSeek() override;
	virtual void OnMovieScenePlayFinish() override;

protected:
	UPROPERTY(BlueprintAssignable)
	FMovieSceneEvent HandleOnMovieScenePlay;

	UPROPERTY(BlueprintAssignable)
	FMovieSceneEvent HandleOnMovieScenePlayReverse;

	UPROPERTY(BlueprintAssignable)
	FMovieSceneEvent HandleOnMovieScenePause;

	UPROPERTY(BlueprintAssignable)
	FMovieSceneEvent HandleOnMovieSceneStop;

	UPROPERTY(BlueprintAssignable)
	FMovieSceneEvent HandleOnMovieSceneSeek;

	UPROPERTY(BlueprintAssignable)
	FMovieSceneEvent HandleOnMovieScenePlayFinish;
};
