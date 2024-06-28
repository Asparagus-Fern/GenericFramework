// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureHandle.h"

void UProcedureHandle::Handle(const TArray<FProcedureInterfaceHandle>& InHandles)
{
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
	if (!CurrentHandle.Interface)
	{
		OnHandleOnceFinish_Internal();
	}

	if (CurrentHandle.Interface->GetIsAsync())
	{
		if (CurrentHandle.Interface->GetIsActive() != CurrentHandle.bTargetActiveState)
		{
			if (CurrentHandle.bTargetActiveState)
			{
				CurrentHandle.Interface->OnActivedFinish.AddUObject(this, &UProcedureHandle::OnHandleOnceFinish_Internal);
			}
			else
			{
				CurrentHandle.Interface->OnInactivedFinish.AddUObject(this, &UProcedureHandle::OnHandleOnceFinish_Internal);
			}
		}
		else
		{
			OnHandleOnceFinish_Internal();
		}
	}
	else
	{
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
	CurrentHandle.Interface->OnActivedFinish.Clear();
	CurrentHandle.Interface->OnInactivedFinish.Clear();
	
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
	OnHandleFinish.Broadcast();
	MarkAsGarbage();
}
