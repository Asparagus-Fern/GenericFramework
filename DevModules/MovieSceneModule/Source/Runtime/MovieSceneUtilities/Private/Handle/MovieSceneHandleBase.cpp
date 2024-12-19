// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle/MovieSceneHandleBase.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerStatics.h"
#include "Widget/MovieScenePanel.h"

void UMovieSceneHandleBase::Tick(float DeltaTime)
{
	if (MovieSceneSetting.MovieSceneLoopSetting.bLoopFragment)
	{
		if (PlayNum > MovieSceneSetting.MovieSceneLoopSetting.PlayNumToDelayLoop)
		{
			// if (bSeekingTime)
			// {
			// 	if (GetTime() >= FTimespan::FromSeconds(MovieSceneSetting.MovieSceneLoopSetting.LoopRange.X) && GetTime() <= FTimespan::FromSeconds(MovieSceneSetting.MovieSceneLoopSetting.LoopRange.Y))
			// 	{
			// 		bSeekingTime = false;
			// 	}
			// }
			// else
			// {
			// 	if (GetTime() < FTimespan::FromSeconds(MovieSceneSetting.MovieSceneLoopSetting.LoopRange.X) || GetTime() > FTimespan::FromSeconds(MovieSceneSetting.MovieSceneLoopSetting.LoopRange.Y))
			// 	{
			// 		Execute_Seek(this, FTimespan::FromSeconds(MovieSceneSetting.MovieSceneLoopSetting.LoopRange.X + 0.1f));
			// 		Execute_Play(this);
			// 		bSeekingTime = true;
			// 	}
			// }
		}
	}
}

void UMovieSceneHandleBase::SetMovieSceneSetting_Implementation(FMovieSceneSetting InMovieSceneSetting)
{
	Execute_RefreshMovieScenePanel(this, InMovieSceneSetting.MovieSceneState, InMovieSceneSetting.MovieScenePanel);
	Execute_SetMovieSceneLoopSetting(this, InMovieSceneSetting.MovieSceneLoopSetting);

	Execute_SetMovieSceneState(this, InMovieSceneSetting.MovieSceneState);
	MovieSceneSetting = InMovieSceneSetting;
}

void UMovieSceneHandleBase::RefreshMovieScenePanel_Implementation(EMovieSceneState InMovieSceneState, TSubclassOf<UMovieScenePanel> InMovieScenePanelClass)
{
	if (InMovieSceneState != MovieSceneSetting.MovieSceneState)
	{
		if (InMovieSceneState == EMovieSceneState::Play)
		{
			OpenMovieScenePanel(InMovieScenePanelClass);
		}
		else if (InMovieSceneState == EMovieSceneState::Stop)
		{
			CloseMovieScenePanel();
		}
	}
}

void UMovieSceneHandleBase::OpenMovieScenePanel(TSubclassOf<UMovieScenePanel> InMovieScenePanel)
{
	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		if (!IsValid(MovieScenePanel))
		{
			MovieScenePanel = ScreenWidgetManager->OpenUserWidget<UMovieScenePanel>(InMovieScenePanel);
		}
		else
		{
			if (MovieScenePanel->GetClass() != InMovieScenePanel)
			{
				ScreenWidgetManager->CloseUserWidget(MovieScenePanel);
				MovieScenePanel = ScreenWidgetManager->OpenUserWidget<UMovieScenePanel>(InMovieScenePanel);
			}
			else
			{
				ScreenWidgetManager->OpenUserWidget(MovieScenePanel);
			}
		}
	}
}

void UMovieSceneHandleBase::CloseMovieScenePanel()
{
	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->CloseUserWidget(MovieScenePanel);
	}
}

void UMovieSceneHandleBase::SetMovieSceneState_Implementation(EMovieSceneState InMovieSceneState)
{
	if (InMovieSceneState == EMovieSceneState::Play)
	{
		Execute_Play(this);
		PlayNum++;
	}
	else if (InMovieSceneState == EMovieSceneState::Pause)
	{
		Execute_Pause(this);
	}
	else if (InMovieSceneState == EMovieSceneState::Stop)
	{
		Execute_Stop(this);
	}
}

void UMovieSceneHandleBase::OnMovieSceneFinish_Implementation()
{
	PlayNum++;
}

FTimespan UMovieSceneHandleBase::GetTime()
{
	return FTimespan();
}
