// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/SceneManager.h"

#include "Kismet/GameplayStatics.h"

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

bool FHandleActor::GetIsValid() const
{
	TSet<EHandleActorMethod> ValidHandleActorMethods;
	for (auto& HandleActorMethod : HandleActorMethods)
	{
		if (HandleActorMethod != EHandleActorMethod::None)
		{
			ValidHandleActorMethods.Add(HandleActorMethod);
		}
	}

	return !ValidHandleActorMethods.IsEmpty();
}

void USceneManager::NativeOnActived()
{
	Super::NativeOnActived();
}

void USceneManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}

TArray<AActor*> USceneManager::FindActors(const FFindActorHandle& FindActorHandle, const bool bUpdate)
{
	auto FindActorInternal = [this](const FFindActorHandle& InFindActorHandle)
	{
		TArray<AActor*> Actors;

		switch (InFindActorHandle.FindActorMethod)
		{
		case EFindActorMethod::Class:
			UGameplayStatics::GetAllActorsOfClass(this, InFindActorHandle.ActorClass, Actors);
			break;

		case EFindActorMethod::Tag:
			UGameplayStatics::GetAllActorsWithTag(this, InFindActorHandle.ActorTag, Actors);
			break;

		case EFindActorMethod::ClassAndTag:
			UGameplayStatics::GetAllActorsOfClassWithTag(this, InFindActorHandle.ActorClass, InFindActorHandle.ActorTag, Actors);
			break;

		case EFindActorMethod::Interface:
			UGameplayStatics::GetAllActorsWithInterface(this, InFindActorHandle.ActorInterface, Actors);
			break;
		}

		return Actors;
	};

	/* 查找缓存 */
	if (FFoundActorHandle* FoundActorHandle = FoundActorHandles.FindByKey(FindActorHandle))
	{
		/* 是否更新 */
		if (bUpdate)
		{
			FoundActorHandle->FoundActors = FindActorInternal(FindActorHandle);
		}

		return FoundActorHandle->FoundActors;
	}
	else
	{
		FFoundActorHandle NewFoundActorHandle;
		NewFoundActorHandle.FindActorHandle = FindActorHandle;
		NewFoundActorHandle.FoundActors = FindActorInternal(FindActorHandle);

		FoundActorHandles.AddUnique(NewFoundActorHandle);
		return FoundActorHandle->FoundActors;
	}
}
