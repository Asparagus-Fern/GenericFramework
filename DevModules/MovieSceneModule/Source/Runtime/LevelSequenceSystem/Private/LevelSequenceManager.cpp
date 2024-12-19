// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceManager.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

ULevelSequenceManager::ULevelSequenceManager(const FObjectInitializer& ObjectInitializer)
{
}

bool ULevelSequenceManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void ULevelSequenceManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	FGuid A;
}

void ULevelSequenceManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool ULevelSequenceManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

/* ==================== ULevelSequenceManager ==================== */

ULevelSequenceHandle* ULevelSequenceManager::RegisterLevelSequence(ULevelSequence* InLevelSequence)
{
	if (!IsValid(InLevelSequence))
	{
		DLOG(DLogMovieScene, Error, TEXT("InSequence Is NULL"))
		return nullptr;
	}

	if (IsLevelSequenceRegister(InLevelSequence))
	{
		DLOG(DLogMovieScene, Log, TEXT("InSequence Is Already Register"))
		return GetLevelSequenceHandle(InLevelSequence);
	}

	ALevelSequenceActor* LevelSequenceActor = nullptr;
	ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(this, InLevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

	if (!IsValid(LevelSequenceActor) || !IsValid(LevelSequencePlayer))
	{
		DLOG(DLogMovieScene, Error, TEXT("CreateLevelSequencePlayer Fail"))
		return nullptr;
	}

	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		if (ULevelSequenceHandle* NewHandle = HandleManager->RegisterHandle<ULevelSequenceHandle>(this, FName(InLevelSequence->GetPackage()->GetName())))
		{
			NewHandle->LevelSequenceActor = LevelSequenceActor;
			NewHandle->LevelSequencePlayer = LevelSequencePlayer;

			IMovieSceneInterface::Execute_LoadMovieSceneDataSource(NewHandle);

			LevelSequenceHandles.Add(NewHandle);
			return NewHandle;
		}
	}

	return nullptr;
}

void ULevelSequenceManager::UnRegisterLevelSequence(ULevelSequence* InLevelSequence)
{
	if (IsLevelSequenceRegister(InLevelSequence))
	{
		if (ULevelSequenceHandle* Handle = GetLevelSequenceHandle(InLevelSequence))
		{
			UnRegisterLevelSequence(Handle);
		}
	}
}

void ULevelSequenceManager::UnRegisterLevelSequence(ULevelSequenceHandle* InLevelSequenceHandle)
{
	if (LevelSequenceHandles.Contains(InLevelSequenceHandle))
	{
		LevelSequenceHandles.Remove(InLevelSequenceHandle);

		if (UHandleManager* HandleManager = GetManager<UHandleManager>())
		{
			HandleManager->UnRegisterHandle(InLevelSequenceHandle);
		}
	}
}

bool ULevelSequenceManager::IsLevelSequenceRegister(const ULevelSequence* InLevelSequence)
{
	for (const auto& LevelSequenceHandle : LevelSequenceHandles)
	{
		if (LevelSequenceHandle->LevelSequenceActor->GetSequence() == InLevelSequence)
		{
			return true;
		}
	}
	return false;
}

ULevelSequenceHandle* ULevelSequenceManager::GetLevelSequenceHandle(const ULevelSequence* InLevelSequence)
{
	for (const auto& LevelSequenceHandle : LevelSequenceHandles)
	{
		if (LevelSequenceHandle->LevelSequenceActor->GetSequence() == InLevelSequence)
		{
			return LevelSequenceHandle;
		}
	}
	return nullptr;
}
