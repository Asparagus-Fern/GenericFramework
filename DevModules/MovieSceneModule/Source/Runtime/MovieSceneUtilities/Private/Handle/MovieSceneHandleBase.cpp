// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle/MovieSceneHandleBase.h"

#include "ScreenWidgetManager.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"
#include "Widget/MovieScenePanel.h"

void UMovieSceneHandleBase::Tick(float DeltaTime)
{
	if (MovieSceneSetting.MovieSceneLoopSetting.bLoopFragment)
	{
		// if (GetMovieSceneCurrentTime() > FTimespan(0, 0, MovieSceneSetting.MovieSceneLoopSetting.LoopRange.Y))
		// {
		// 	bEnableLoopFragmentSeek = true;
		// }
		//
		// if (PlayNum >= MovieSceneSetting.MovieSceneLoopSetting.PlayNumToDelayLoop && !bIsSeeking && bEnableLoopFragmentSeek)
		// {
		// 	bEnableLoopFragmentSeek = false;
		// 	bIsSeeking = true;
		// 	Execute_Seek(this, 0, 0, 0, MovieSceneSetting.MovieSceneLoopSetting.LoopRange.X, 0);
		// }
	}
}

void UMovieSceneHandleBase::OpenMovieScene_Implementation()
{
	IMovieSceneInterface::OpenMovieScene_Implementation();
}

void UMovieSceneHandleBase::CloseMovieScene_Implementation()
{
	IMovieSceneInterface::CloseMovieScene_Implementation();

	// if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	// {
	// 	HandleManager->UnRegisterHandle(this);
	// }
}

void UMovieSceneHandleBase::SetMovieSceneSetting_Implementation(FMovieSceneSetting InMovieSceneSetting)
{
	// Execute_RefreshMovieScenePanel(this, InMovieSceneSetting.MovieSceneState, InMovieSceneSetting.MovieScenePanel);
	Execute_SetMovieSceneLoopSetting(this, InMovieSceneSetting.MovieSceneLoopSetting);

	Execute_SetMovieSceneState(this, InMovieSceneSetting.MovieSceneState);
	MovieSceneSetting = InMovieSceneSetting;
}

void UMovieSceneHandleBase::OpenMovieScenePanel(TSubclassOf<UMovieScenePanel> InMovieScenePanel)
{
	if (!InMovieScenePanel)
	{
		return;
	}

	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		MovieScenePanel = ScreenWidgetManager->OpenUserWidget<UMovieScenePanel>(InMovieScenePanel, FOnWidgetActiveStateChanged::CreateUObject(this, &UMovieSceneHandleBase::OnOpenMovieScenePanelFinish));
	}
}

void UMovieSceneHandleBase::OnOpenMovieScenePanelFinish(UUserWidgetBase* InWidget)
{
}

void UMovieSceneHandleBase::CloseMovieScenePanel()
{
	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->CloseUserWidget(MovieScenePanel, FOnWidgetActiveStateChanged::CreateUObject(this, &UMovieSceneHandleBase::OnCloseMovieScenePanelFinish));
	}
}

void UMovieSceneHandleBase::OnCloseMovieScenePanelFinish(UUserWidgetBase* InWidget)
{
}

void UMovieSceneHandleBase::SetMovieSceneState_Implementation(EMovieSceneState InMovieSceneState)
{
	if (InMovieSceneState == EMovieSceneState::Play)
	{
		Execute_Play(this);
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

void UMovieSceneHandleBase::OnMovieSceneOpenFinish_Implementation()
{
	IMovieSceneInterface::OnMovieSceneOpenFinish_Implementation();

	OpenMovieScenePanel(MovieSceneSetting.MovieScenePanel);
	OnOpenFinish.Broadcast();
}

void UMovieSceneHandleBase::OnMovieScenePlayFinish_Implementation()
{
	PlayNum++;
	bEnableLoopFragmentSeek = true;
	OnPlayFinish.Broadcast();
}

void UMovieSceneHandleBase::OnMovieSceneSeekFinish_Implementation()
{
	bIsSeeking = false;
	OnSeekFinish.Broadcast();
}

void UMovieSceneHandleBase::OnMovieSceneCloseFinish_Implementation()
{
	IMovieSceneInterface::OnMovieSceneCloseFinish_Implementation();

	CloseMovieScenePanel();
	OnCloseFinish.Broadcast();
}

FTimespan UMovieSceneHandleBase::GetMovieSceneCurrentTime_Implementation()
{
	return FTimespan();
}
