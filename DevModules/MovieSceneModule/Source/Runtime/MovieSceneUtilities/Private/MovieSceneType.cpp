// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieSceneType.h"

FMovieSceneTime::FMovieSceneTime()
{
}

FMovieSceneTime::FMovieSceneTime(int32 InDay, int32 InHour, int32 InMinute, int32 InSecond, int32 InMicroSecond)
	: Day(InDay),
	  Hour(InHour),
	  Minute(InMinute),
	  Second(InSecond),
	  MicroSecond(InMicroSecond)
{
}

FMovieSceneTime::FMovieSceneTime(FTimespan InTimeSpan)
	: Day(InTimeSpan.GetDays()),
	  Hour(InTimeSpan.GetHours()),
	  Minute(InTimeSpan.GetMinutes()),
	  Second(InTimeSpan.GetSeconds()),
	  MicroSecond(0)
{
}

FMovieSceneSetting::FMovieSceneSetting()
{
	MovieScenePanel = LoadClass<UMovieScenePanel>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/MovieSceneModule/UI/WBP_MediaPanel.WBP_MediaPanel_C'"));
}
