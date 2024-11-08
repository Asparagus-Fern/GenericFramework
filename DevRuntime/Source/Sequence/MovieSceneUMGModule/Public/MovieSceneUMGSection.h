// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sections/MovieSceneHookSection.h"
#include "MovieSceneUMGSection.generated.h"

class UUserWidgetBlueprint;

/**
 * 
 */
UCLASS()
class MOVIESCENEUMGMODULE_API UMovieSceneUMGSection : public UMovieSceneHookSection
{
	GENERATED_BODY()

public:
	UMovieSceneUMGSection(const FObjectInitializer& ObjInit);

	virtual EMovieSceneChannelProxyType CacheChannelProxy() override;
	virtual void Begin(IMovieScenePlayer* Player, const UE::MovieScene::FEvaluationHookParams& Params) const override;
	virtual void Update(IMovieScenePlayer* Player, const UE::MovieScene::FEvaluationHookParams& Params) const override;
	virtual void End(IMovieScenePlayer* Player, const UE::MovieScene::FEvaluationHookParams& Params) const override;

public:
	UPROPERTY()
	TObjectPtr<UUserWidgetBlueprint> UserWidgetBP;
};
