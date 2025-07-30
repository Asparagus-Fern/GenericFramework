// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ProcedureFlow/Load/ProcedureFlow_LoadLevelStreaming.h"

#include "LevelStreamingManager.h"
#include "ProcedureFlowManager.h"
#include "Manager/ManagerStatics.h"

AProcedureFlow_LoadLevelStreaming::AProcedureFlow_LoadLevelStreaming()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProcedureFlow_LoadLevelStreaming::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();

	if (!GetWorld()->IsPartitionedWorld())
	{
		if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
		{
			if (bLoadCurrentWorldLevels)
			{
				LevelStreamingManager->LoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &AProcedureFlow_LoadLevelStreaming::NativeOnLoadCurrentWorldLevelStreamingOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &AProcedureFlow_LoadLevelStreaming::NativeOnLoadCurrentWorldLevelStreamingFinish));
			}
			else
			{
				LevelStreamingManager->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsFinish));
			}
		}
	}
}

void AProcedureFlow_LoadLevelStreaming::OnProcedureFlowExit_Implementation()
{
	Super::OnProcedureFlowExit_Implementation();
}

void AProcedureFlow_LoadLevelStreaming::OnLoadCurrentWorldLevelStreamingOnceFinish_Implementation()
{
}

void AProcedureFlow_LoadLevelStreaming::NativeOnLoadCurrentWorldLevelStreamingOnceFinish()
{
	OnLoadingOnceFinish();
	OnLoadCurrentWorldLevelStreamingOnceFinish();
}

void AProcedureFlow_LoadLevelStreaming::OnLoadCurrentWorldLevelStreamingFinish_Implementation()
{
}

void AProcedureFlow_LoadLevelStreaming::NativeOnLoadCurrentWorldLevelStreamingFinish()
{
	OnLoadingOnceFinish();
	OnLoadCurrentWorldLevelStreamingFinish();

	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsFinish));
	}
}

void AProcedureFlow_LoadLevelStreaming::OnLoadVisibleLevelsOnceFinish_Implementation()
{
}

void AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsOnceFinish()
{
	OnLoadingOnceFinish();
	OnLoadVisibleLevelsOnceFinish();
}

void AProcedureFlow_LoadLevelStreaming::OnLoadVisibleLevelsFinish_Implementation()
{
}

void AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsFinish()
{
	OnLoadingOnceFinish();
	OnLoadVisibleLevelsFinish();
	SwitchToNextProcedureFlow();
}

int32 AProcedureFlow_LoadLevelStreaming::GetLoadingNum_Implementation()
{
	return bLoadCurrentWorldLevels ? (GetWorld()->GetStreamingLevels().Num() + VisibleLevels.Num()) : VisibleLevels.Num();
}
