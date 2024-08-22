// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureProxy.h"

#include "Procedure/ProcedureObject.h"

void UProcedureProxy::Pause()
{
	ProcedureState = EProcedureState::Pause;
	ProcedureHandleGroup.OnPause.ExecuteIfBound();
	FProcedureDelegates::OnProxyHandlePause.Broadcast(this);
}

void UProcedureProxy::Continue()
{
	ProcedureState = EProcedureState::Continue;
	ProcedureHandleGroup.OnContinue.ExecuteIfBound();
	FProcedureDelegates::OnProxyHandleContinue.Broadcast(this);
	OnHandleOnceFinish();
}

void UProcedureProxy::Stop()
{
	ProcedureState = EProcedureState::Stop;
	ProcedureHandleGroup.OnStop.ExecuteIfBound();
	FProcedureDelegates::OnProxyHandleStop.Broadcast(this);
}

void UProcedureProxy::Handle(const FProcedureHandleGroup& InHandles)
{
	ProcedureHandleGroup = InHandles;
	ProcedureHandleGroup.CheckHandles();
	if (ProcedureHandleGroup.CanHandle())
	{
		ProcedureHandleGroup.OnBegin.ExecuteIfBound();
		FProcedureDelegates::OnProxyHandleBegin.Broadcast(this);
		CurrentProcedureHandle = ProcedureHandleGroup.ProcedureHandles[HandleIndex];
		HandleInternal();
	}
	else
	{
		OnHandleFinish();
	}
}

void UProcedureProxy::HandleInternal()
{
	if (CurrentProcedureHandle.bTargetActiveState)
	{
		if (CurrentProcedureHandle.ProcedureObject->bIsAsync && !CurrentProcedureHandle.ProcedureObject->NativeOnActivedFinish.IsBound())
		{
			CurrentProcedureHandle.ProcedureObject->NativeOnActivedFinish.BindUObject(this, &UProcedureProxy::OnHandleOnceFinish);
		}
		CurrentProcedureHandle.ProcedureObject->NativeOnActived();
	}
	else
	{
		if (CurrentProcedureHandle.ProcedureObject->bIsAsync && !CurrentProcedureHandle.ProcedureObject->NativeOnInactivedFinish.IsBound())
		{
			CurrentProcedureHandle.ProcedureObject->NativeOnInactivedFinish.BindUObject(this, &UProcedureProxy::OnHandleOnceFinish);
		}
		CurrentProcedureHandle.ProcedureObject->NativeOnInactived();
	}

	if (!CurrentProcedureHandle.ProcedureObject->bIsAsync)
	{
		OnHandleOnceFinish();
	}
}

void UProcedureProxy::OnHandleOnceFinish()
{
	CurrentProcedureHandle.ProcedureObject->NativeOnActivedFinish.Unbind();
	CurrentProcedureHandle.ProcedureObject->NativeOnInactivedFinish.Unbind();

	if (ProcedureState == EProcedureState::Pause)
	{
		return;
	}
	else if (ProcedureState == EProcedureState::Continue)
	{
		HandleIndex++;
		if (ProcedureHandleGroup.ProcedureHandles.IsValidIndex(HandleIndex))
		{
			CurrentProcedureHandle = ProcedureHandleGroup.ProcedureHandles[HandleIndex];
			HandleInternal();
		}
		else
		{
			OnHandleFinish();
		}
	}
	else if (ProcedureState == EProcedureState::Stop)
	{
		OnHandleFinish();
	}
}

void UProcedureProxy::OnHandleFinish()
{
	HandleIndex = 0;
	ProcedureHandleGroup.OnFinish.ExecuteIfBound();
	FProcedureDelegates::OnProxyHandleFinish.Broadcast(this);
}
