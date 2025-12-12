// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowLoadLevelStreaming.h"

#include "LevelStreamingSubsystem.h"

int32 UProcedureFlowLoadLevelStreaming::GetLoadCount()
{
	int32 Count = 0;

	if (!GetWorld()->IsPartitionedWorld())
	{
		if (bLoadCurrentWorldLevels)
		{
			if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(this))
			{
				Count += LevelStreamingSubsystem->GetCurrentWorldLevelStreamingList().Num();
			}
		}

		Count += VisibleLevels.Num();
	}

	return Count;
}

void UProcedureFlowLoadLevelStreaming::StartLoading()
{
	Super::StartLoading();

	if (!GetWorld()->IsPartitionedWorld())
	{
		if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(this))
		{
			if (bLoadCurrentWorldLevels)
			{
				LevelStreamingSubsystem->LoadCurrentWorldLevelStreaming
				(
					FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingOnceFinish),
					FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingFinish)
				);
			}
			else
			{
				LevelStreamingSubsystem->LoadLevels
				(
					VisibleLevels,
					true,
					false,
					FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish),
					FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish)
				);
			}
		}
	}
}

void UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingOnceFinish()
{
	OnLoadOnceFinish();
}

void UProcedureFlowLoadLevelStreaming::OnLoadCurrentWorldLevelStreamingFinish()
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(this))
	{
		LevelStreamingSubsystem->SetLevelsVisibility
		(
			VisibleLevels,
			true,
			FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish),
			FOnHandleLevelStreamingFinish::CreateUObject(this, &UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish)
		);
	}
}

void UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsOnceFinish()
{
	OnLoadOnceFinish();
}

void UProcedureFlowLoadLevelStreaming::OnLoadVisibleLevelsFinish()
{
	OnLoadFinish();
}
