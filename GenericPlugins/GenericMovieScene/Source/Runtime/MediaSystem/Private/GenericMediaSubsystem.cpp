// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "GenericMediaSubsystem.h"

#include "GenericMediaHandle.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "MovieSceneType.h"
#include "Type/DebugType.h"

UGenericMediaSubsystem* UGenericMediaSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

UGenericMediaHandle* UGenericMediaSubsystem::RegisterMediaHandle(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, const FMediaPlayerOptions& InOptions)
{
	if (!IsValid(InMediaPlayer))
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("InMediaPlayer Is InValid"))
		return nullptr;
	}

	if (!IsValid(InMediaSource))
	{
		GenericLOG(GenericLogMovieScene, Error, TEXT("InMediaSource Is InValid"))
		return nullptr;
	}

	UGenericMediaHandle* NewHandle = NewObject<UGenericMediaHandle>(this);
	NewHandle->Register(InMediaPlayer, InMediaSource, InOptions);
	MediaHandles.Add(NewHandle);

	return NewHandle;
}

void UGenericMediaSubsystem::UnRegisterMediaHandle(UGenericMediaHandle* InHandle)
{
	if (MediaHandles.Contains(InHandle))
	{
		if (InHandle->IsPlaying())
		{
			InHandle->CloseMovieScene();
		}

		MediaHandles.Remove(InHandle);
	}
}
