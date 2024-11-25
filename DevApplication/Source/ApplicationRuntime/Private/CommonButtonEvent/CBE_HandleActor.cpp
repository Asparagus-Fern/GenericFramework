// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleActor.h"

#include "SceneManager.h"
#include "Manager/ManagerProxy.h"

void UCBE_HandleActor::NativeOnCreate()
{
	Super::NativeOnCreate();
}

void UCBE_HandleActor::NativeOnDestroy()
{
	Super::NativeOnDestroy();
}

bool UCBE_HandleActor::CanExecuteButtonEvent_Implementation()
{
	return FindActorHandle.GetIsValid() && !HandleActors.IsEmpty();
}

void UCBE_HandleActor::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (const USceneManager* SceneManager = UManagerProxy::Get()->GetManager<USceneManager>())
	{
		const TArray<AActor*> Actors = SceneManager->FindActors(FindActorHandle);
		for (const auto& HandleActor : HandleActors)
		{
			if (HandleActor->CanExecuteHandle())
			{
				HandleActor->ExecuteHandle(Actors);
			}
		}
	}
}
