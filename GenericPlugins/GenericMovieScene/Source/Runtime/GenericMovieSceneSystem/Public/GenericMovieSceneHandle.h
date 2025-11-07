// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneType.h"
#include "Interface/StateInterface.h"
#include "GenericMovieSceneInterface.h"
#include "Obect/GenericObject.h"

#include "GenericMovieSceneHandle.generated.h"

class UGenericMovieSceneHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovieSceneEvent, UGenericMovieSceneHandle*, InHandle);

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericMovieSceneHandle : public UGenericObject, public IStateInterface, public IGenericMovieSceneInterface
{
	GENERATED_BODY()

	/* IStateInterface */
protected:
	GENERICMOVIESCENESYSTEM_API virtual void NativeOnCreate() override;
	GENERICMOVIESCENESYSTEM_API virtual void NativeOnDestroy() override;

	/* IMovieSceneInterface */
protected:
	GENERICMOVIESCENESYSTEM_API virtual void OnMovieScenePlay() override;
	GENERICMOVIESCENESYSTEM_API virtual void OnMovieScenePlayReverse() override;
	GENERICMOVIESCENESYSTEM_API virtual void OnMovieScenePause() override;
	GENERICMOVIESCENESYSTEM_API virtual void OnMovieSceneStop() override;
	GENERICMOVIESCENESYSTEM_API virtual void OnMovieSceneSeek() override;
	GENERICMOVIESCENESYSTEM_API virtual void OnMovieScenePlayFinish() override;

public:
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
