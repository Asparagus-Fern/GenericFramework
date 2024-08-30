// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayProcedure/ProcedureLoading.h"

#include "CameraManager.h"
#include "LevelStreamingManager.h"
#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"
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
	if (bActiveLoadingWidget)
	{
		for (const auto& LoadingWidget : LoadingWidgets)
		{
			// GetManager<UScreenWidgetManager>()->OpenUserWidget(LoadingWidget);
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
				// FOnHandleLevelStreamingOnceFinish OnOnceFinish;
				// OnOnceFinish.BindDynamic(this, &UProcedureLoading::UProcedureLoading::OnLoadAllLevelStreamingOnceFinish);
				// FOnHandleLevelStreamingFinish OnFinish;
				// OnFinish.BindDynamic(this, &UProcedureLoading::OnLoadAllLevelStreamingFinish);

				// GetManager<ULevelStreamingManager>()->LoadCurrentWorldLevelStreaming(OnOnceFinish, OnFinish);
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

	if (bIsCloseLoadingWidgetOnInactive && bActiveLoadingWidget)
	{
		for (const auto& LoadingWidget : LoadingWidgets)
		{
			// FSimpleMulticastDelegate OnFinish;
			// OnFinish.AddLambda([this]()
			// 	{
			// 		RequestProcedureInactived();
			// 	}
			// );
			//
			// GetManager<UScreenWidgetManager>()->CloseUserWidget(LoadingWidget, OnFinish);
		}
	}

	// RequestProcedureInactived();
}

void UProcedureLoading::OnLoadAllLevelStreamingOnceFinish()
{
}

void UProcedureLoading::OnLoadAllLevelStreamingFinish()
{
	TArray<TSoftObjectPtr<UWorld>> HiddenLevels;
	for (const auto StreamingLevel : GetWorld()->GetStreamingLevels())
	{
		if (StreamingLevel->IsLevelVisible())
		{
			HiddenLevels.Add(StreamingLevel->GetWorldAsset());
		}
	}

	if (HiddenLevels.IsEmpty())
	{
		if (!LevelsToLoad.IsEmpty())
		{
			// FOnHandleLevelStreamingOnceFinish OnOnceFinish;
			// OnOnceFinish.BindDynamic(this, &UProcedureLoading::UProcedureLoading::OnLevelsToLoadOnceFinish);
			// FOnHandleLevelStreamingFinish OnFinish;
			// OnFinish.BindDynamic(this, &UProcedureLoading::OnLevelsToLoadFinish);

			// GetManager<ULevelStreamingManager>()->LoadLevels(LevelsToLoad, true, false, OnOnceFinish, OnFinish);
		}
		else
		{
			OnLevelsToLoadFinish();
		}
	}
	else
	{
		// FOnHandleLevelStreamingOnceFinish OnOnceFinish;
		// OnOnceFinish.BindDynamic(this, &UProcedureLoading::UProcedureLoading::OnSetLevelsVisibilityOnceFinish);
		// FOnHandleLevelStreamingFinish OnFinish;
		// OnFinish.BindDynamic(this, &UProcedureLoading::OnSetLevelsVisibilityFinish);

		// GetManager<ULevelStreamingManager>()->SetLevelsVisibility(HiddenLevels, false, OnOnceFinish, OnFinish);
	}
}

void UProcedureLoading::OnSetLevelsVisibilityOnceFinish()
{
}

void UProcedureLoading::OnSetLevelsVisibilityFinish()
{
	if (!LevelsToLoad.IsEmpty())
	{
		// FOnHandleLevelStreamingOnceFinish OnOnceFinish;
		// OnOnceFinish.BindDynamic(this, &UProcedureLoading::UProcedureLoading::OnLevelsToLoadOnceFinish);
		// FOnHandleLevelStreamingFinish OnFinish;
		// OnFinish.BindDynamic(this, &UProcedureLoading::OnLevelsToLoadFinish);

		// GetManager<ULevelStreamingManager>()->LoadLevels(LevelsToLoad, true, false, OnOnceFinish, OnFinish);
	}
	else
	{
		OnLevelsToLoadFinish();
	}
}

void UProcedureLoading::OnLevelsToLoadOnceFinish()
{
}

void UProcedureLoading::OnLevelsToLoadFinish()
{
	if (StartupCameraTag.IsValid())
	{
		// GetManager<UCameraManager>()->SwitchToCamera(StartupCameraTag, NewObject<UCameraHandle_Teleport>(this));
	}
	
	if (bIsCloseLoadingWidgetOnLoadingLevelsFinish && bActiveLoadingWidget)
	{
		// for (const auto& LoadingWidget : LoadingWidgets)
		// {
		// 	FSimpleMulticastDelegate OnFinish;
		// 	OnFinish.AddLambda([this]()
		// 		{
		// 			RequestProcedureActived();
		// 		}
		// 	);
		//
		// 	GetManager<UScreenWidgetManager>()->CloseUserWidget(LoadingWidget, OnFinish);
		// }
	}

	// RequestProcedureActived();
}
