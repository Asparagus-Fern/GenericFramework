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
	HandleActors.Reset();
}

bool UCBE_HandleActor::CanExecuteButtonEvent_Implementation()
{
	return FindActorHandle.GetIsValid() && HandleActor.GetIsValid();
}

void UCBE_HandleActor::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	TArray<AActor*> Actors = UManagerProxy::Get()->GetManager<USceneManager>()->FindActors(FindActorHandle);
	for (const auto& HandleActorMethod : HandleActor.HandleActorMethods)
	{
		switch (HandleActorMethod)
		{
		case EHandleActorMethod::None:
			break;

		case EHandleActorMethod::HandleActorLocation:
			for (const auto& Actor : Actors)
			{
				Actor->SetActorLocation(HandleActor.NewActorLocation);
			}
			break;

		case EHandleActorMethod::HandleActorRotation:
			for (const auto& Actor : Actors)
			{
				Actor->SetActorRotation(HandleActor.NewActorRotation);
			}
			break;

		case EHandleActorMethod::HandleActorScale:
			for (const auto& Actor : Actors)
			{
				Actor->SetActorScale3D(HandleActor.NewActorScale);
			}
			break;

		case EHandleActorMethod::HandleActorHiddenInGame:
			for (const auto& Actor : Actors)
			{
				Actor->SetActorHiddenInGame(HandleActor.NewActorHiddenInGame);
			}
			break;
		}
	}
}