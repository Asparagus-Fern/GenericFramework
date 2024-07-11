// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayProcedure/ProcedureLoading.h"

#include "LevelStreamingManager.h"
#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"
#include "Manager/ManagerSubsystem.h"
#include "Procedure/ProcedureManager.h"
#include "UserWidget/Base/UserWidgetBase.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureLoading_Default, "Procedure.Loading.Default");

UProcedureLoading::UProcedureLoading()
{
}

void UProcedureLoading::NativeOnActived()
{
	Super::NativeOnActived();

	/* 加载页面 */
	if (bActiveLoadingWidget && DefaultLoadingTag.IsValid())
	{
		for (const auto& LoadingWidget : LoadingWidgets)
		{
			if (LoadingWidget->SelfTag == DefaultLoadingTag)
			{
				GetManager<UScreenWidgetManager>()->OpenUserWidget(LoadingWidget);
				OnLoadingWidgetOpen.Broadcast(LoadingWidget);
			}
		}
	}

	if (bIsWorldPartition)
	{
	}
	else
	{
		if (bIsLoadLevelStreaming)
		{
			if (bIsAutoLoadAllLevelStreaming)
			{
				FOnOnceFinish OnOnceFinish;
				OnOnceFinish.BindDynamic(this, &UProcedureLoading::UProcedureLoading::OnLoadAllLevelStreamingOnceFinish);
				FOnFinish OnFinish;
				OnFinish.BindDynamic(this, &UProcedureLoading::OnLoadAllLevelStreamingFinish);

				GetManager<ULevelStreamingManager>()->LoadCurrentWorldLevelStreaming(OnOnceFinish, OnFinish);
			}
			else
			{
				OnLoadAllLevelStreamingFinish();
			}
		}
	}
}

void UProcedureLoading::NativeOnInactived()
{
	Super::NativeOnInactived();

	if (bIsCloseLoadingWidgetOnInactive && bActiveLoadingWidget && DefaultLoadingTag.IsValid())
	{
		for (const auto& LoadingWidget : LoadingWidgets)
		{
			if (LoadingWidget->SelfTag == DefaultLoadingTag)
			{
				FSimpleMulticastDelegate OnFinish;
				OnFinish.AddLambda([this]()
					{
						RequestProcedureInactived();
					}
				);

				GetManager<UScreenWidgetManager>()->CloseUserWidget(LoadingWidget, OnFinish);
			}
		}
	}
	else
	{
		RequestProcedureInactived();
	}
}

void UProcedureLoading::OnLoadAllLevelStreamingOnceFinish()
{
}

void UProcedureLoading::OnLoadAllLevelStreamingFinish()
{
	FOnOnceFinish OnOnceFinish;
	OnOnceFinish.BindDynamic(this, &UProcedureLoading::UProcedureLoading::OnLevelsToLoadOnceFinish);
	FOnFinish OnFinish;
	OnFinish.BindDynamic(this, &UProcedureLoading::OnLevelsToLoadFinish);

	GetManager<ULevelStreamingManager>()->LoadLevels(LevelsToLoad, true, false, OnOnceFinish, OnFinish);
}

void UProcedureLoading::OnLevelsToLoadOnceFinish()
{
}

void UProcedureLoading::OnLevelsToLoadFinish()
{
	if (bIsCloseLoadingWidgetOnLoadingLevelsFinish && bActiveLoadingWidget && DefaultLoadingTag.IsValid())
	{
		for (const auto& LoadingWidget : LoadingWidgets)
		{
			if (LoadingWidget->SelfTag == DefaultLoadingTag)
			{
				FSimpleMulticastDelegate OnFinish;
				OnFinish.AddLambda([this]()
					{
						RequestProcedureActived();
					}
				);

				GetManager<UScreenWidgetManager>()->CloseUserWidget(LoadingWidget, OnFinish);
			}
		}
	}
	else
	{
		RequestProcedureActived();
	}
}
