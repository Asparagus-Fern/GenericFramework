// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_HandleCommonTimeline.h"

void UCBE_HandleCommonTimeline::NativeOnActived()
{
	Super::NativeOnActived();

	/* 处理同步类型 */
	for (const auto& ActiveCommonButtonHandle : GetSyncCommonButtonHandles(ActiveCommonButtonHandles))
	{
		ActiveCommonButtonHandle->UpdateHandle();
	}

	/* 处理异步类型 */
	if (GetAsyncCommonButtonHandles(ActiveCommonButtonHandles).IsEmpty())
	{
		OnActivateHandleFinish();
	}
	else
	{
		FSimpleMulticastDelegate OnFinish;
		OnFinish.AddUObject(this, &UCBE_HandleCommonTimeline::OnActivateHandleOnceFinish);
		GetAsyncCommonButtonHandles(ActiveCommonButtonHandles)[ActivateIndex]->UpdateHandle(OnFinish);
	}
}

void UCBE_HandleCommonTimeline::NativeOnInactived()
{
	Super::NativeOnInactived();

	/* 处理同步类型 */
	for (const auto& ActiveCommonButtonHandle : GetSyncCommonButtonHandles(InactiveCommonButtonHandles))
	{
		ActiveCommonButtonHandle->UpdateHandle();
	}

	/* 处理异步类型 */
	if (GetAsyncCommonButtonHandles(InactiveCommonButtonHandles).IsEmpty())
	{
		OnInactivateHandleFinish();
	}
	else
	{
		FSimpleMulticastDelegate OnFinish;
		OnFinish.AddUObject(this, &UCBE_HandleCommonTimeline::OnInactivateHandleOnceFinish);
		GetAsyncCommonButtonHandles(InactiveCommonButtonHandles)[InactivateIndex]->UpdateHandle(OnFinish);
	}
}

TArray<UCommonButtonHandle*> UCBE_HandleCommonTimeline::GetSyncCommonButtonHandles(TArray<UCommonButtonHandle*> InCommonButtonHandles)
{
	TArray<UCommonButtonHandle*> Result;

	for (auto& CommonButtonHandle : InCommonButtonHandles)
	{
		if (!CommonButtonHandle->GetIsAsync())
		{
			Result.Add(CommonButtonHandle);
		}
	}

	return Result;
}

TArray<UCommonButtonHandle*> UCBE_HandleCommonTimeline::GetAsyncCommonButtonHandles(TArray<UCommonButtonHandle*> InCommonButtonHandles)
{
	TArray<UCommonButtonHandle*> Result;

	for (auto& CommonButtonHandle : InCommonButtonHandles)
	{
		if (CommonButtonHandle->GetIsAsync())
		{
			Result.Add(CommonButtonHandle);
		}
	}

	return Result;
}

void UCBE_HandleCommonTimeline::OnActivateHandleOnceFinish()
{
	ActivateIndex++;
	if (GetAsyncCommonButtonHandles(ActiveCommonButtonHandles).IsValidIndex(ActivateIndex))
	{
		FSimpleMulticastDelegate OnFinish;
		OnFinish.AddUObject(this, &UCBE_HandleCommonTimeline::OnActivateHandleOnceFinish);
		GetAsyncCommonButtonHandles(ActiveCommonButtonHandles)[ActivateIndex]->UpdateHandle(OnFinish);
	}
	else
	{
		OnActivateHandleFinish();
	}
}

void UCBE_HandleCommonTimeline::OnActivateHandleFinish()
{
	ActivateIndex = 0;
	RequestActivateFinish();
}

void UCBE_HandleCommonTimeline::OnInactivateHandleOnceFinish()
{
	InactivateIndex++;
	if (GetAsyncCommonButtonHandles(InactiveCommonButtonHandles).IsValidIndex(InactivateIndex))
	{
		FSimpleMulticastDelegate OnFinish;
		OnFinish.AddUObject(this, &UCBE_HandleCommonTimeline::OnInactivateHandleOnceFinish);
		GetAsyncCommonButtonHandles(InactiveCommonButtonHandles)[InactivateIndex]->UpdateHandle(OnFinish);
	}
	else
	{
		OnInactivateHandleFinish();
	}
}

void UCBE_HandleCommonTimeline::OnInactivateHandleFinish()
{
	InactivateIndex = 0;
	RequestInactivateFinish();
}
