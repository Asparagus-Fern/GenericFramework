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
UCLASS(Abstract, MinimalAPI)
class UMovieSceneHandleBase : public UHandleBase, public IMovieSceneInterface
{
	GENERATED_BODY()

	/* UHandleBase */
protected:
	MOVIESCENEUTILITIES_API virtual void OnRegister() override;
	MOVIESCENEUTILITIES_API virtual void OnUnRegister() override;

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
	MOVIESCENEUTILITIES_API virtual void OnMovieScenePlay() override;
	MOVIESCENEUTILITIES_API virtual void OnMovieScenePlayReverse() override;
	MOVIESCENEUTILITIES_API virtual void OnMovieScenePause() override;
	MOVIESCENEUTILITIES_API virtual void OnMovieSceneStop() override;
	MOVIESCENEUTILITIES_API virtual void OnMovieSceneSeek() override;
	MOVIESCENEUTILITIES_API virtual void OnMovieScenePlayFinish() override;

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
