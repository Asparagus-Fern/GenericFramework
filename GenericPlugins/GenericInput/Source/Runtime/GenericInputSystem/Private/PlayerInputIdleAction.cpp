// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PlayerInputIdleAction.h"

#include "PlayerInputIdleActionComponent.h"

TStatId UPlayerInputIdleAction::GetStatId() const
{
	return GetStatID();
}

UWorld* UPlayerInputIdleAction::GetTickableGameObjectWorld() const
{
	return GetWorld();
}

void UPlayerInputIdleAction::Tick(float DeltaTime)
{
	if (bIsActionStart && bEnableReverse)
	{
		ReverseTime = bIsActionReverse ? ReverseTime - DeltaTime : ReverseTime + DeltaTime;
	}

	OnActionToggle(DeltaTime, bEnableReverse ? (ReverseTime / ReverseDuration) : 1.f);
}

void UPlayerInputIdleAction::Start()
{
	WaitingTimerHandle.Invalidate();
	ReverseMovementTimerHandle.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(WaitingTimerHandle, this, &UPlayerInputIdleAction::HandleStartAction, ActionWaitTime);
}

void UPlayerInputIdleAction::Stop()
{
	if (const APlayerController* PC = GetOwnerPlayerController())
	{
		for (const auto& ExcludeKey : ExcludeKeysWhenRefresh)
		{
			if (PC->IsInputKeyDown(ExcludeKey))
			{
				return;
			}
		}
	}

	HandleStopAction();

	WaitingTimerHandle.Invalidate();
	ReverseMovementTimerHandle.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(WaitingTimerHandle, this, &UPlayerInputIdleAction::HandleStartAction, ActionWaitTime);
}

void UPlayerInputIdleAction::HandleStartAction()
{
	bIsActionStart = true;
	OnActionStart();

	if (bEnableReverse)
	{
		GetWorld()->GetTimerManager().SetTimer(ReverseMovementTimerHandle, this, &UPlayerInputIdleAction::HandleStartAction, ReverseDuration);
	}
}

void UPlayerInputIdleAction::HandleStopAction()
{
	bIsActionStart = false;
	OnActionStop();
}

void UPlayerInputIdleAction::HandleReverseAction()
{
	bIsActionReverse = !bIsActionReverse;

	if (!ReverseMovementTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(ReverseMovementTimerHandle, this, &UPlayerInputIdleAction::HandleReverseAction, ReverseDuration, true);
	}
}

APlayerController* UPlayerInputIdleAction::GetOwnerPlayerController() const
{
	if (const UPlayerInputIdleActionComponent* PlayerInputIdleActionComponent = Cast<UPlayerInputIdleActionComponent>(GetOuter()))
	{
		return PlayerInputIdleActionComponent->GetOwnerPlayerController();
	}

	return nullptr;
}

bool UPlayerInputIdleAction::GetIsActionStart() const
{
	return bIsActionStart;
}

bool UPlayerInputIdleAction::GetIsActionReverse() const
{
	return bIsActionReverse;
}
