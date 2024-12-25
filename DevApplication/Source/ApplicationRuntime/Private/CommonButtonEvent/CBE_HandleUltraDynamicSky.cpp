// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonButtonEvent/CBE_HandleUltraDynamicSky.h"

#include "SceneManager.h"
#include "UltraDynamicSkySubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerStatics.h"

bool UCBE_HandleUltraDynamicSky::CanExecuteButtonEvent_Implementation()
{
	// return !Values.IsEmpty();
	return false;
}

void UCBE_HandleUltraDynamicSky::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (USceneManager* SceneManager = GetManager<USceneManager>())
	{
		if (UUltraDynamicSkySubsystem* UltraDynamicSkySubsystem = SceneManager->GetWorld()->GetSubsystem<UUltraDynamicSkySubsystem>())
		{
			if (AActor* UltraDynamicSkyActor = UltraDynamicSkySubsystem->GetUltraDynamicSky())
			{
				// for (auto& Value : Values)
				// {
					// UBPFunctions_Property
				// }
			}
		}
	}

	if (!bIsAsync)
	{
		MarkAsActivedFinish();
	}
}
