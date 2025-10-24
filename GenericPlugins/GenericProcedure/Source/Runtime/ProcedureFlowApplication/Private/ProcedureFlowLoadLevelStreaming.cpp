// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowLoadLevelStreaming.h"

#include "LevelStreamingManager.h"
#include "Manager/ManagerStatics.h"

void UProcedureFlowLoadLevelStreaming::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();

	if (!GetWorld()->IsPartitionedWorld())
	{
		if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
		{
			if (bLoadCurrentWorldLevels)
			{
				LevelStreamingManager->LoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingFinish));
			}
			else
			{
				LevelStreamingManager->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish));
			}
		}
	}
}

void UProcedureFlowLoadLevelStreaming::OnProcedureFlowExit_Implementation()
{
	Super::OnProcedureFlowExit_Implementation();
}

void UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingOnceFinish()
{
}

void UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingFinish()
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish));
	}
}

void UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish()
{
}

void UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish()
{
	SwitchToNextProcedureFlow();
}
