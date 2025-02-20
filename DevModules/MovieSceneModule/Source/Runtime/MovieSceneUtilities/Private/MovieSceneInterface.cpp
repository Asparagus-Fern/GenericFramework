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
