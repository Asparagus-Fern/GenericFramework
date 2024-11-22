// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_SetLevelLocation.h"

#include "Kismet/GameplayStatics.h"

bool UCBE_SetLevelLocation::CanExecuteButtonEvent_Implementation()
{
	return !Level.IsNull();
}

void UCBE_SetLevelLocation::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	const FString PackageName = FPackageName::ObjectPathToPackageName(Level.ToString());
	ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(this, FName(*PackageName));
	
	// LevelStreaming->LevelTransform.SetLocation(NewLocation);
	
	// if (UWorld* LevelStreamingWorld = LevelStreaming->GetWorld())
	// {
	// 	FString A = LevelStreamingWorld->GetName();
	// 	LevelStreamingWorld->RequestNewWorldOrigin(NewLocation);
	// }

	if (bIsAsync)
		MarkAsActivedFinish();
}
