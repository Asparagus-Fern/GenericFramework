// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureHandle.h"

void UProcedureHandle::Handle(const TArray<FProcedureInterfaceHandle>& InHandles)
{
	/* 无处理内容 */
	Handles = InHandles;
	if (Handles.IsEmpty())
	{
		OnHandleFinish_Internal();
		return;
	}

	CurrentHandle = Handles[HandleIndex];
	HandleProcedure();
}

void UProcedureHandle::HandleProcedure()
{
	/* 处理对象为空 */
	if (!CurrentHandle.Interface)
	{
		OnHandleOnceFinish_Internal();
	}

	/* 处理对象是否为异步流程 */
	if (CurrentHandle.Interface->GetIsAsync())
	{
		/* 处理异步流程，异步流程内部使用 RequestActivateFinish/RequestInactivateFinish 标志异步的处理完成 */
		if (CurrentHandle.Interface->GetIsActive() != CurrentHandle.bTargetActiveState)
		{
			if (CurrentHandle.bTargetActiveState)
			{
				CurrentHandle.Interface->GetActivateFinishDelegate().AddUObject(this, &UProcedureHandle::OnHandleOnceFinish_Internal);
			}
			else
			{
				CurrentHandle.Interface->GetInactivateFinishDelegate().AddUObject(this, &UProcedureHandle::OnHandleOnceFinish_Internal);
			}
		}
		else
		{
			OnHandleOnceFinish_Internal();
		}
	}
	else
	{
		/* 处理非异步流程 */
		if (CurrentHandle.Interface->GetIsActive() != CurrentHandle.bTargetActiveState)
		{
			if (CurrentHandle.bTargetActiveState)
			{
				CurrentHandle.Interface->NativeOnActived();
			}
			else
			{
				CurrentHandle.Interface->NativeOnInactived();
			}
		}

		OnHandleOnceFinish_Internal();
	}
}

void UProcedureHandle::OnHandleOnceFinish_Internal()
{
	/* 流程的单次完成 */
	CurrentHandle.Interface->GetActivateFinishDelegate().Clear();
	CurrentHandle.Interface->GetInactivateFinishDelegate().Clear();

	HandleIndex++;
	if (Handles.IsValidIndex(HandleIndex))
	{
		CurrentHandle = Handles[HandleIndex];
		HandleProcedure();
	}
	else
	{
		OnHandleFinish_Internal();
	}
}

void UProcedureHandle::OnHandleFinish_Internal()
{
	Handles.Reset();
	HandleIndex = 0;
	GetHandleFinishDelegate().Broadcast();
	MarkAsGarbage();
}
