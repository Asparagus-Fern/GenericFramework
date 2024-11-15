// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleLevelStreaming.h"

#include "LevelStreamingManager.h"
#include "Manager/ManagerProxy.h"

UCBE_HandleLevelStreaming::UCBE_HandleLevelStreaming()
{
	bIsAsync = true;
}

bool UCBE_HandleLevelStreaming::CanExecuteButtonEvent_Implementation()
{
	return !Levels.IsEmpty();
}

void UCBE_HandleLevelStreaming::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (ULevelStreamingManager* LevelStreamingManager = UManagerProxy::Get()->GetManager<ULevelStreamingManager>())
	{
		switch (HandleLevelStreamingMethod)
		{
		case EHandleLevelStreamingMethod::UseLoad:
			if (bLoad)
			{
				if (bIsAsync)
					LevelStreamingManager->LoadLevels(Levels, true, false, FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish::CreateUObject(this, &UCBE_HandleLevelStreaming::OnHandleLevelsFinish));
				else
					LevelStreamingManager->LoadLevels(Levels, true, false, FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish());
			}
			else
			{
				if (bIsAsync)
					LevelStreamingManager->UnloadLevels(Levels, false, FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish::CreateUObject(this, &UCBE_HandleLevelStreaming::OnHandleLevelsFinish));
				else
					LevelStreamingManager->UnloadLevels(Levels, false, FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish());
			}

			break;

		case EHandleLevelStreamingMethod::UseVisible:
			if (bIsAsync)
				LevelStreamingManager->SetLevelsVisibility(Levels, bVisible, FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish::CreateUObject(this, &UCBE_HandleLevelStreaming::OnHandleLevelsFinish));
			else
				LevelStreamingManager->SetLevelsVisibility(Levels, bVisible, FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish());
			break;
		}
	}
}

void UCBE_HandleLevelStreaming::OnHandleLevelsFinish()
{
	MarkAsActivedFinish();
}
