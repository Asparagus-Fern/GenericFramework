// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieSceneUMGSection.h"

#include "Channels/MovieSceneChannelProxy.h"

UMovieSceneUMGSection::UMovieSceneUMGSection(const FObjectInitializer& ObjInit)
	: Super(ObjInit)
{
}

EMovieSceneChannelProxyType UMovieSceneUMGSection::CacheChannelProxy()
{
	FMovieSceneChannelProxyData Channels;
	
	ChannelProxy = MakeShared<FMovieSceneChannelProxy>(MoveTemp(Channels));

	return EMovieSceneChannelProxyType::Dynamic;
}

void UMovieSceneUMGSection::Begin(IMovieScenePlayer* Player, const UE::MovieScene::FEvaluationHookParams& Params) const
{
	Super::Begin(Player, Params);
}

void UMovieSceneUMGSection::Update(IMovieScenePlayer* Player, const UE::MovieScene::FEvaluationHookParams& Params) const
{
	Super::Update(Player, Params);
}

void UMovieSceneUMGSection::End(IMovieScenePlayer* Player, const UE::MovieScene::FEvaluationHookParams& Params) const
{
	Super::End(Player, Params);
}
