// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericMovieSceneHandle.h"

void UGenericMovieSceneHandle::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();
}

void UGenericMovieSceneHandle::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();
	CloseMovieScene();
}

void UGenericMovieSceneHandle::OnMovieScenePlay()
{
	IGenericMovieSceneInterface::OnMovieScenePlay();
	HandleOnMovieScenePlay.Broadcast(this);
}

void UGenericMovieSceneHandle::OnMovieScenePlayReverse()
{
	IGenericMovieSceneInterface::OnMovieScenePlayReverse();
	HandleOnMovieScenePlayReverse.Broadcast(this);
}

void UGenericMovieSceneHandle::OnMovieScenePause()
{
	IGenericMovieSceneInterface::OnMovieScenePause();
	HandleOnMovieScenePause.Broadcast(this);
}

void UGenericMovieSceneHandle::OnMovieSceneStop()
{
	IGenericMovieSceneInterface::OnMovieSceneStop();
	HandleOnMovieSceneStop.Broadcast(this);
}

void UGenericMovieSceneHandle::OnMovieSceneSeek()
{
	IGenericMovieSceneInterface::OnMovieSceneSeek();
	HandleOnMovieSceneSeek.Broadcast(this);
}

void UGenericMovieSceneHandle::OnMovieScenePlayFinish()
{
	IGenericMovieSceneInterface::OnMovieScenePlayFinish();
	HandleOnMovieScenePlayFinish.Broadcast(this);
}
