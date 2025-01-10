// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaManager.h"

#include "MediaHandle.h"
#include "MediaPlayer.h"
#include "MediaPlaylist.h"
#include "MediaSource.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

bool UMediaManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UMediaManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UMediaManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UMediaManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UMediaManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldBeginPlay(InWorld);
}

void UMediaManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);

	TArray<UMediaHandle*> TempMediaHandles = MediaHandles;
	for (const auto& TempMediaHandle : TempMediaHandles)
	{
		UnRegisterMedia(TempMediaHandle);
	}
}

UMediaHandle* UMediaManager::RegisterMedia(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource)
{
	if (!IsValid(InMediaPlayer) || !IsValid(InMediaSource))
	{
		DLOG(DLogMovieScene, Error, TEXT("InMediaPlayer / InMediaSource Is NULL"))
		return nullptr;
	}

	return RegisterMedia(InMediaPlayer, TArray<UMediaSource*>{InMediaSource});
}

UMediaHandle* UMediaManager::RegisterMedia(UMediaPlayer* InMediaPlayer, TArray<UMediaSource*> InMediaSources)
{
	UMediaPlaylist* MediaPlaylist = NewObject<UMediaPlaylist>(this);

	for (const auto& InMediaSource : InMediaSources)
	{
		MediaPlaylist->Add(InMediaSource);
	}

	return RegisterMedia(InMediaPlayer, MediaPlaylist);
}

UMediaHandle* UMediaManager::RegisterMedia(UMediaPlayer* InMediaPlayer, UMediaPlaylist* InMediaPlayList)
{
	if (!IsValid(InMediaPlayer) || !IsValid(InMediaPlayList))
	{
		DLOG(DLogMovieScene, Error, TEXT("InMediaPlayer / InMediaPlayList Is NULL"))
		return nullptr;
	}

	UMediaHandle* MediaHandle = nullptr;

	if (IsMediaRegister(InMediaPlayer))
	{
		MediaHandle = GetMediaHandle(InMediaPlayer);
		MediaHandle->MediaPlaylist = InMediaPlayList;
		IMovieSceneInterface::Execute_Open(MediaHandle);
	}
	else
	{
		if (UHandleManager* HandleManager = GetManager<UHandleManager>())
		{
			MediaHandle = HandleManager->RegisterHandle<UMediaHandle>(this, FName(InMediaPlayer->GetPackage()->GetName()));
			MediaHandle->MediaPlayer = InMediaPlayer;
			MediaHandle->MediaPlaylist = InMediaPlayList;

			IMovieSceneInterface::Execute_OpenMovieScene(MediaHandle);
			MediaHandles.Add(MediaHandle);
		}
	}

	return MediaHandle;
}

void UMediaManager::UnRegisterMedia(UMediaPlayer* InMediaPlayer)
{
	if (IsMediaRegister(InMediaPlayer))
	{
		if (UMediaHandle* Handle = GetMediaHandle(InMediaPlayer))
		{
			UnRegisterMedia(Handle);
		}
	}
}

void UMediaManager::UnRegisterMedia(UMediaHandle* InMediaHandle)
{
	if (MediaHandles.Contains(InMediaHandle))
	{
		IMovieSceneInterface::Execute_CloseMovieScene(InMediaHandle);
		MediaHandles.Remove(InMediaHandle);

		if (UMediaManager* MediaManager = GetManager<UMediaManager>())
		{
			MediaManager->UnRegisterMedia(InMediaHandle);
		}
	}
}

bool UMediaManager::IsMediaRegister(const UMediaPlayer* InMediaPlayer)
{
	for (const auto& MediaHandle : MediaHandles)
	{
		if (MediaHandle->MediaPlayer == InMediaPlayer)
		{
			return true;
		}
	}
	return false;
}

UMediaHandle* UMediaManager::GetMediaHandle(const UMediaPlayer* InMediaPlayer)
{
	for (const auto& MediaHandle : MediaHandles)
	{
		if (MediaHandle->MediaPlayer == InMediaPlayer)
		{
			return MediaHandle;
		}
	}
	return nullptr;
}
