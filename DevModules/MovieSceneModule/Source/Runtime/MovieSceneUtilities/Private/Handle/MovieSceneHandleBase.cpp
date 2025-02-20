// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle/MovieSceneHandleBase.h"

void UMovieSceneHandleBase::OnRegister()
{
	Super::OnRegister();
	OpenMovieScene();
}

void UMovieSceneHandleBase::OnUnRegister()
{
	Super::OnUnRegister();
	CloseMovieScene();
}
