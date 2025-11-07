// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericMovieSceneInterface.h"

void IGenericMovieSceneInterface::OpenMovieScene()
{
	OnMovieSceneOpened();
}

void IGenericMovieSceneInterface::CloseMovieScene()
{
	OnMovieSceneClosed();
}

bool IGenericMovieSceneInterface::PlayMovieScene()
{
	OnMovieScenePlay();
	return true;
}

bool IGenericMovieSceneInterface::PlayMovieSceneFromStart()
{
	OnMovieScenePlay();
	return true;
}

bool IGenericMovieSceneInterface::PlayLoopingMovieScene(int32 NumLoops)
{
	OnMovieScenePlay();
	return true;
}

bool IGenericMovieSceneInterface::PlayReverseMovieScene()
{
	OnMovieScenePlayReverse();
	return true;
}

bool IGenericMovieSceneInterface::PauseMovieScene()
{
	OnMovieScenePause();
	return true;
}

bool IGenericMovieSceneInterface::StopMovieScene()
{
	OnMovieSceneStop();
	return true;
}

bool IGenericMovieSceneInterface::SeekMovieScene(FTimecode SeekTime)
{
	OnMovieSceneSeek();
	return true;
}
