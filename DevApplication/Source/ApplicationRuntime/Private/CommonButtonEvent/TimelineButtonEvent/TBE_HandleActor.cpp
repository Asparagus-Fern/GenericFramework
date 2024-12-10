// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/TimelineButtonEvent/TBE_HandleActor.h"

#include "SceneManager.h"
#include "Manager/ManagerProxy.h"

bool UTBE_HandleActor::CanExecuteButtonEvent_Implementation()
{
	return FindActorHandle.GetIsValid() && !HandleActors.IsEmpty();
}

void UTBE_HandleActor::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (const USceneManager* SceneManager = UManagerProxy::Get()->GetManager<USceneManager>())
	{
		Actors = SceneManager->FindActors(FindActorHandle);
	}

	for (const auto& HandleActor : HandleActors)
	{
		if (HandleActor->CanExecuteHandle())
		{
			HandleActor->PreExecuteHandle(Actors);
		}
	}

	if (bIsAsync)
	{
		MarkAsActivedFinish();
	}
}

void UTBE_HandleActor::HandleTimelineUpdate_Implementation(float Alpha)
{
	Super::HandleTimelineUpdate_Implementation(Alpha);

	for (const auto& HandleActor : HandleActors)
	{
		if (HandleActor->CanExecuteHandle())
		{
			HandleActor->ExecuteHandle(Actors, Alpha);
		}
	}
}

void UTBE_HandleActor::HandleTimelineFinish_Implementation(float Alpha)
{
	Super::HandleTimelineFinish_Implementation(Alpha);

	for (const auto& HandleActor : HandleActors)
	{
		if (HandleActor->CanExecuteHandle())
		{
			HandleActor->PostExecuteHandle(Actors);
		}
	}

	Actors.Reset();
}
