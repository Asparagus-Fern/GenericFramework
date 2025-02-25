// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieSceneInterface.h"

void IMovieSceneInterface::OpenMovieScene()
{
	OnMovieSceneOpened();
}

void IMovieSceneInterface::CloseMovieScene()
{
	OnMovieSceneClosed();
}

bool IMovieSceneInterface::PlayMovieScene()
{
	OnMovieScenePlay();
	return true;
}

bool IMovieSceneInterface::PlayMovieSceneFromStart()
{
	OnMovieScenePlay();
	return true;
}

bool IMovieSceneInterface::PlayLoopingMovieScene(int32 NumLoops)
{
	OnMovieScenePlay();
	return true;
}

bool IMovieSceneInterface::PlayReverseMovieScene()
{
	OnMovieScenePlayReverse();
	return true;
}

bool IMovieSceneInterface::PauseMovieScene()
{
	OnMovieScenePause();
	return true;
}

bool IMovieSceneInterface::StopMovieScene()
{
	OnMovieSceneStop();
	return true;
}

bool IMovieSceneInterface::SeekMovieScene(FTimecode SeekTime)
{
	OnMovieSceneSeek();
	return true;
}
