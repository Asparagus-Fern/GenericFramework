// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode/ActiveNode_LevelStreamingLoad.h"

#include "ActiveNodeSubsystem.h"
#include "LevelStreamingManager.h"
#include "ScreenWidgetManager.h"
#include "Manager/ManagerProxy.h"
#include "UserWidget/Loading/Loading.h"

AActiveNode_LevelStreamingLoad::AActiveNode_LevelStreamingLoad()
{
}

void AActiveNode_LevelStreamingLoad::Login()
{
	Super::Login();

	if (!GetWorld()->IsPartitionedWorld())
	{
		/* 创建加载页面 */
		if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
		{
			if (LoadingClass)
			{
				if (UUserWidgetBase* Widget = ScreenWidgetManager->OpenUserWidget(LoadingClass))
				{
					LoadingUI = Cast<ULoading>(Widget);
				}
			}
		}

		if (IsValid(LoadingUI))
			LoadingUI->NativeOnLoadingBegin(GetLoadingNum());

		/* 加载关卡 */
		if (ULevelStreamingManager* LevelStreamingManager = UManagerProxy::Get()->GetManager<ULevelStreamingManager>())
		{
			/* 是否加载当前世界所有关卡 */
			if (bLoadCurrentWorldLevels)
			{
				LevelStreamingManager->LoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &AActiveNode_LevelStreamingLoad::NativeOnLoadCurrentWorldLevelStreamingOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &AActiveNode_LevelStreamingLoad::NativeOnLoadCurrentWorldLevelStreamingFinish));
			}
			else
			{
				LevelStreamingManager->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &AActiveNode_LevelStreamingLoad::NativeOnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &AActiveNode_LevelStreamingLoad::NativeOnLoadVisibleLevelsFinish));
			}

			return;
		}

		if (IsValid(LoadingUI))
			LoadingUI->NativeOnLoadingEnd();
	}
}

void AActiveNode_LevelStreamingLoad::Logout()
{
	Super::Logout();
}

void AActiveNode_LevelStreamingLoad::OnLoadCurrentWorldLevelStreamingOnceFinish_Implementation()
{
}

void AActiveNode_LevelStreamingLoad::NativeOnLoadCurrentWorldLevelStreamingOnceFinish()
{
	if (IsValid(LoadingUI))
		LoadingUI->NativeOnLoadingOnceFinish();

	OnLoadCurrentWorldLevelStreamingOnceFinish();
}

void AActiveNode_LevelStreamingLoad::OnLoadCurrentWorldLevelStreamingFinish_Implementation()
{
}

void AActiveNode_LevelStreamingLoad::NativeOnLoadCurrentWorldLevelStreamingFinish()
{
	if (IsValid(LoadingUI))
		LoadingUI->NativeOnLoadingOnceFinish();

	OnLoadCurrentWorldLevelStreamingFinish();

	if (ULevelStreamingManager* LevelStreamingManager = UManagerProxy::Get()->GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &AActiveNode_LevelStreamingLoad::NativeOnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &AActiveNode_LevelStreamingLoad::NativeOnLoadVisibleLevelsFinish));
	}
}

void AActiveNode_LevelStreamingLoad::OnLoadVisibleLevelsOnceFinish_Implementation()
{
}

void AActiveNode_LevelStreamingLoad::NativeOnLoadVisibleLevelsOnceFinish()
{
	if (IsValid(LoadingUI))
		LoadingUI->NativeOnLoadingOnceFinish();

	OnLoadVisibleLevelsOnceFinish();
}

void AActiveNode_LevelStreamingLoad::OnLoadVisibleLevelsFinish_Implementation()
{
}

void AActiveNode_LevelStreamingLoad::NativeOnLoadVisibleLevelsFinish()
{
	if (IsValid(LoadingUI))
		LoadingUI->NativeOnLoadingOnceFinish();

	if (IsValid(LoadingUI))
	{
		LoadingUI->NativeOnLoadingEnd();
		UManagerProxy::Get()->GetManager<UScreenWidgetManager>()->CloseUserWidget(LoadingUI->SlotTag);
	}

	OnLoadVisibleLevelsFinish();

	if (ChangeNodeTag.IsValid())
	{
		bool bSuccess;
		UActiveNodeSubsystem::ChangeActiveNodeTo(this, ChangeNodeTag, bSuccess, AActiveNode::StaticClass(), false);
	}
}

int32 AActiveNode_LevelStreamingLoad::GetLoadingNum() const
{
	return bLoadCurrentWorldLevels ? (GetWorld()->GetNumLevels() + VisibleLevels.Num()) : VisibleLevels.Num();
}
