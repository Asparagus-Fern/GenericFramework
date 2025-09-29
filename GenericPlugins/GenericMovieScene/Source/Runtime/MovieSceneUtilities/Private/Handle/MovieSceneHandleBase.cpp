// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Handle/MovieSceneHandleBase.h"

void UMovieSceneHandleBase::OnRegister()
{
	Super::OnRegister();
}

void UMovieSceneHandleBase::OnUnRegister()
{
	Super::OnUnRegister();
	CloseMovieScene();
}

void UMovieSceneHandleBase::OnMovieScenePlay()
{
	IMovieSceneInterface::OnMovieScenePlay();
	OnMovieScenePlayEvent.Broadcast(this);
	HandleOnMovieScenePlay.Broadcast();
}

void UMovieSceneHandleBase::OnMovieScenePlayReverse()
{
	IMovieSceneInterface::OnMovieScenePlayReverse();
	OnMovieScenePlayReverseEvent.Broadcast(this);
	HandleOnMovieScenePlayReverse.Broadcast();
}

void UMovieSceneHandleBase::OnMovieScenePause()
{
	IMovieSceneInterface::OnMovieScenePause();
	OnMovieScenePauseEvent.Broadcast(this);
	HandleOnMovieScenePause.Broadcast();
}

void UMovieSceneHandleBase::OnMovieSceneStop()
{
	IMovieSceneInterface::OnMovieSceneStop();
	OnMovieSceneStopEvent.Broadcast(this);
	HandleOnMovieSceneStop.Broadcast();
}

void UMovieSceneHandleBase::OnMovieSceneSeek()
{
	IMovieSceneInterface::OnMovieSceneSeek();
	OnMovieSceneSeekEvent.Broadcast(this);
	HandleOnMovieSceneSeek.Broadcast();
}

void UMovieSceneHandleBase::OnMovieScenePlayFinish()
{
	IMovieSceneInterface::OnMovieScenePlayFinish();
	OnMovieScenePlayFinishEvent.Broadcast(this);
	HandleOnMovieScenePlayFinish.Broadcast();
}
