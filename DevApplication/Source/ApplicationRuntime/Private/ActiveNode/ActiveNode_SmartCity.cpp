// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode/ActiveNode_SmartCity.h"

#include "ScreenWidgetManager.h"
#include "DataAsset/GameWidgetSetting.h"

AActiveNode_SmartCity::AActiveNode_SmartCity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AActiveNode_SmartCity::LoginNode_Implementation()
{
	Super::LoginNode_Implementation();

	/* Loading界面 */
	if (IsValid(GameWidgetSetting))
	{
		for (const auto OpenUserWidgetOnLoading : GameWidgetSetting->OpenUserWidgetsOnLoading)
		{
			GetManager<UScreenWidgetManager>()->OpenUserWidget(OpenUserWidgetOnLoading);
		}
	}
}

void AActiveNode_SmartCity::LogoutNode_Implementation()
{
	Super::LogoutNode_Implementation();
}

void AActiveNode_SmartCity::OnLoadCurrentWorldLevelStreamingFinish()
{
	Super::OnLoadCurrentWorldLevelStreamingFinish();
}

void AActiveNode_SmartCity::OnSetProjectLevelsVisibleFinish()
{
	Super::OnSetProjectLevelsVisibleFinish();

	/* 移除Loading界面 */
	if (IsValid(GameWidgetSetting))
	{
		for (const auto OpenUserWidgetOnLoading : GameWidgetSetting->OpenUserWidgetsOnLoading)
		{
			GetManager<UScreenWidgetManager>()->CloseUserWidget(OpenUserWidgetOnLoading);
		}

		GetManager<UScreenWidgetManager>()->SwitchGameMenu(GameWidgetSetting->GameMenu);

		for (const auto& DefaultOpenUserWidget : GameWidgetSetting->DefaultOpenUserWidgets)
		{
			GetManager<UScreenWidgetManager>()->OpenUserWidget(DefaultOpenUserWidget);
		}
	}
}
