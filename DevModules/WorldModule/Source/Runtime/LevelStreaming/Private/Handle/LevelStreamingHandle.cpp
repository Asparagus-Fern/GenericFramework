// Fill out your copyright notice in the Description page of Project Settings.

#include "Handle/LevelStreamingHandle.h"

FOnLevelStreamingHandleOnceFinish& ULevelStreamingHandle::GetHandleOnceFinishEvent()
{
	return OnOnceFinishEvent;
}

FOnLevelStreamingHandleFinish& ULevelStreamingHandle::GetHandleFinishEvent()
{
	return OnFinishEvent;
}

void ULevelStreamingHandle::Startup()
{
	if (GetLevels().IsValidIndex(LevelIndex))
	{
		ExecuteHandle(LevelIndex);
	}
}

int32 ULevelStreamingHandle::GetLevelIndex() const
{
	return LevelIndex;
}

TSoftObjectPtr<UWorld> ULevelStreamingHandle::GetLevelByIndex(int32 InIndex)
{
	if (GetLevels().IsValidIndex(InIndex))
	{
		return GetLevels()[InIndex];
	}
	return nullptr;
}

int32 ULevelStreamingHandle::GetIndexByLevel(const TSoftObjectPtr<UWorld>& InLevel)
{
	if (GetLevels().Contains(InLevel))
	{
		return GetLevels().Find(InLevel);
	}
	return -1;
}

void ULevelStreamingHandle::OnOnceFinish()
{
	LevelIndex++;
	BroadcastOnceFinish();

	if (GetLevels().IsValidIndex(LevelIndex))
	{
		ExecuteHandle(LevelIndex);
	}
	else
	{
		OnFinish();
	}
}

void ULevelStreamingHandle::OnFinish()
{
	LevelIndex = 0;
	BroadcastFinish();
}

void ULevelStreamingHandle::BroadcastOnceFinish()
{
	OnOnceFinishEvent.Broadcast(this, GetLevelByIndex(LevelIndex));
}

void ULevelStreamingHandle::BroadcastFinish()
{
	OnFinishEvent.Broadcast(this);
}
