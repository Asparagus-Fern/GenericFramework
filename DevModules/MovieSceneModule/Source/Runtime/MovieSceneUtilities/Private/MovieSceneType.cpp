// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieSceneType.h"

FMovieSceneSetting::FMovieSceneSetting()
{
	MovieScenePanel = LoadClass<UMovieScenePanel>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/MovieSceneModule/UI/WBP_MediaPanel.WBP_MediaPanel_C'"));
}
