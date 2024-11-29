#include "SceneType.h"

FFindActorHandle::FFindActorHandle()
	: ID(FGuid::NewGuid())
{
}

bool FFindActorHandle::GetIsValid() const
{
	return (FindActorMethod == EFindActorMethod::Class && IsValid(ActorClass))
		|| (FindActorMethod == EFindActorMethod::Tag && !ActorTag.IsNone())
		|| (FindActorMethod == EFindActorMethod::ClassAndTag && IsValid(ActorClass) && !ActorTag.IsNone())
		|| (FindActorMethod == EFindActorMethod::Interface && IsValid(ActorInterface));
}

bool UHandleActorLocation::CanExecuteHandle()
{
	return bHandleActorLocation || bHandleActorLocationOffset;
}

void UHandleActorLocation::ExecuteHandle(TArray<AActor*> InActors)
{
	for (const auto& InActor : InActors)
	{
		if (bHandleActorLocation)
		{
			InActor->SetActorLocation(NewActorLocation);
		}
		if (bHandleActorLocationOffset)
		{
			InActor->SetActorLocation(InActor->GetActorLocation() + NewActorLocationOffset);
		}
	}
}

bool UHandleActorRotation::CanExecuteHandle()
{
	return bHandleActorRotation || bHandleActorRotationOffset;
}

void UHandleActorRotation::ExecuteHandle(TArray<AActor*> InActors)
{
	for (const auto& InActor : InActors)
	{
		if (bHandleActorRotation)
		{
			InActor->SetActorRotation(NewActorRotation);
		}
		if (bHandleActorRotationOffset)
		{
			InActor->SetActorRotation(InActor->GetActorRotation() + NewActorRotationOffset);
		}
	}
}

bool UHandleActorScale::CanExecuteHandle()
{
	return bHandleActorScale || bHandleActorScaleOffset;
}

void UHandleActorScale::ExecuteHandle(TArray<AActor*> InActors)
{
	for (const auto& InActor : InActors)
	{
		if (bHandleActorScale)
		{
			InActor->SetActorScale3D(NewActorScale);
		}
		if (bHandleActorScaleOffset)
		{
			InActor->SetActorScale3D(InActor->GetActorScale3D() + NewActorScaleOffset);
		}
	}
}

bool UHandleActorHiddenInGame::CanExecuteHandle()
{
	return bHandleActorHiddenInGame;
}

void UHandleActorHiddenInGame::ExecuteHandle(TArray<AActor*> InActors)
{
	for (const auto& InActor : InActors)
	{
		if (bHandleActorHiddenInGame)
		{
			InActor->SetActorHiddenInGame(NewActorHiddenInGame);
		}
	}
}
