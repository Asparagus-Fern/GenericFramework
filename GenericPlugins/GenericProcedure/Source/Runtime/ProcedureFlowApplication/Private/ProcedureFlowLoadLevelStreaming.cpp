// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowLoadLevelStreaming.h"

#include "LevelStreamingSubsystem.h"

void UProcedureFlowLoadLevelStreaming::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();

	if (!GetWorld()->IsPartitionedWorld())
	{
		if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(this))
		{
			if (bLoadCurrentWorldLevels)
			{
				LevelStreamingSubsystem->LoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingFinish));
			}
			else
			{
				LevelStreamingSubsystem->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish));
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
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(this))
	{
		LevelStreamingSubsystem->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish));
	}
}

void UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish()
{
}

void UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish()
{
	SwitchToNextProcedureFlow();
}
