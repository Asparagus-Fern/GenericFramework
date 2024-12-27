// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlow/Load/ProcedureFlow_LoadLevelStreaming.h"

#include "LevelStreamingManager.h"
#include "ProcedureFlowManager.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureFlow_LoadLevelStreaming, "Procedure.Flow.Load.LoadLevelStreaming");

AProcedureFlow_LoadLevelStreaming::AProcedureFlow_LoadLevelStreaming()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProcedureFlow_LoadLevelStreaming::OnProcedureFlowEnter_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	Super::OnProcedureFlowEnter_Implementation(InProcedureFlow);

	if (!GetWorld()->IsPartitionedWorld())
	{
		if (ULevelStreamingManager* LevelStreamingManager = UManagerProxy::Get()->GetManager<ULevelStreamingManager>())
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

void AProcedureFlow_LoadLevelStreaming::OnProcedureFlowExit_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	Super::OnProcedureFlowExit_Implementation(InProcedureFlow);
}

void AProcedureFlow_LoadLevelStreaming::OnLoadCurrentWorldLevelStreamingOnceFinish_Implementation()
{
}

void AProcedureFlow_LoadLevelStreaming::NativeOnLoadCurrentWorldLevelStreamingOnceFinish()
{
	OnLoadCurrentWorldLevelStreamingOnceFinish();
}

void AProcedureFlow_LoadLevelStreaming::OnLoadCurrentWorldLevelStreamingFinish_Implementation()
{
}

void AProcedureFlow_LoadLevelStreaming::NativeOnLoadCurrentWorldLevelStreamingFinish()
{
	OnLoadCurrentWorldLevelStreamingFinish();

	if (ULevelStreamingManager* LevelStreamingManager = UManagerProxy::Get()->GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevels(VisibleLevels, true, false, FOnHandleLevelStreamingOnceFinish::CreateUObject(this, &AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(this, &AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsFinish));
	}
}

void AProcedureFlow_LoadLevelStreaming::OnLoadVisibleLevelsOnceFinish_Implementation()
{
}

void AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsOnceFinish()
{
	OnLoadVisibleLevelsOnceFinish();
}

void AProcedureFlow_LoadLevelStreaming::OnLoadVisibleLevelsFinish_Implementation()
{
}

void AProcedureFlow_LoadLevelStreaming::NativeOnLoadVisibleLevelsFinish()
{
	OnLoadVisibleLevelsFinish();

	if (NextProcedureFlowTag.IsValid())
	{
		if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
		{
			ProcedureFlowManager->EnterProcedureFlow(NextProcedureFlowTag);
		}
	}
}
