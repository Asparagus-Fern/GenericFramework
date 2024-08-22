// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleActorVisibility.h"

#include "Kismet/GameplayStatics.h"

void UCBE_HandleActorVisibility::NativeOnActived()
{
	Super::NativeOnActived();

	for (auto& ActiveVisibilityHandle : ActiveVisibilityHandles)
	{
		TArray<AActor*> Actors;

		if (ActiveVisibilityHandle.ActorClass && ActiveVisibilityHandle.ActorTag != NAME_None)
		{
			UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ActiveVisibilityHandle.ActorClass, ActiveVisibilityHandle.ActorTag, Actors);

			for (const auto& Actor : Actors)
			{
				Actor->SetActorHiddenInGame(ActiveVisibilityHandle.bIsHiddenInGame);
			}
		}
		else if (ActiveVisibilityHandle.ActorClass)
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActiveVisibilityHandle.ActorClass, Actors);
			for (const auto& Actor : Actors)
			{
				Actor->SetActorHiddenInGame(ActiveVisibilityHandle.bIsHiddenInGame);
			}
		}
		else if (ActiveVisibilityHandle.ActorTag != NAME_None)
		{
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), ActiveVisibilityHandle.ActorTag, Actors);
			for (const auto& Actor : Actors)
			{
				Actor->SetActorHiddenInGame(ActiveVisibilityHandle.bIsHiddenInGame);
			}
		}
	}
}

void UCBE_HandleActorVisibility::NativeOnInactived()
{
	Super::NativeOnInactived();

	for (auto& InactiveVisibilityHandle : InactiveVisibilityHandles)
	{
		TArray<AActor*> Actors;

		if (InactiveVisibilityHandle.ActorClass && InactiveVisibilityHandle.ActorTag != NAME_None)
		{
			UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), InactiveVisibilityHandle.ActorClass, InactiveVisibilityHandle.ActorTag, Actors);
			for (const auto& Actor : Actors)
			{
				Actor->SetActorHiddenInGame(InactiveVisibilityHandle.bIsHiddenInGame);
			}
		}
		else if (InactiveVisibilityHandle.ActorClass)
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), InactiveVisibilityHandle.ActorClass, Actors);
			for (const auto& Actor : Actors)
			{
				Actor->SetActorHiddenInGame(InactiveVisibilityHandle.bIsHiddenInGame);
			}
		}
		else if (InactiveVisibilityHandle.ActorTag != NAME_None)
		{
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), InactiveVisibilityHandle.ActorTag, Actors);
			for (const auto& Actor : Actors)
			{
				Actor->SetActorHiddenInGame(InactiveVisibilityHandle.bIsHiddenInGame);
			}
		}
	}
}
