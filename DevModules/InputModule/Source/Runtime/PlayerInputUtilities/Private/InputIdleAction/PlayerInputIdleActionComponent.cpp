// Copyright ChenTaiye 2025. All Rights Reserved.

#include "InputIdleAction/PlayerInputIdleActionComponent.h"

#include "EnhancedInputComponent.h"
#include "PlayerInputManager.h"
#include "InputIdleAction/PlayerInputIdleAction.h"

UPlayerInputIdleActionComponent::UPlayerInputIdleActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	RefreshInputIdleAction = LoadObject<UInputAction>(nullptr,TEXT("/Script/EnhancedInput.InputAction'/DevCore/Input/MiscellaneousActions/IA_RefreshInputIdleAction.IA_RefreshInputIdleAction'"));
}

void UPlayerInputIdleActionComponent::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputComponent* EnhancedInputComponent = GetOwnerEnhancedInputComponent();
	if (RefreshInputIdleAction && IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(RefreshInputIdleAction, ETriggerEvent::Started, this, &UPlayerInputIdleActionComponent::HandleRefreshInputIdleAction);
	}

	if (RefreshMethod == EIdleActionMethod::All)
	{
		for (const auto& PlayerInputIdleInfo : PlayerInputIdleActions)
		{
			PlayerInputIdleInfo->Start();
		}
	}
	else if (RefreshMethod == EIdleActionMethod::Random)
	{
	}
	else if (RefreshMethod == EIdleActionMethod::Sequence)
	{
	}
}

void UPlayerInputIdleActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UPlayerInputIdleActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerInputIdleActionComponent::HandleRefreshInputIdleAction(const FInputActionInstance& Value)
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

	ResetInputIdleAction();
}

void UPlayerInputIdleActionComponent::ResetInputIdleAction()
{
	if (RefreshMethod == EIdleActionMethod::All)
	{
		for (const auto& PlayerInputIdleInfo : PlayerInputIdleActions)
		{
			PlayerInputIdleInfo->Stop();
		}
	}
	else
	{
		if (PlayerInputIdleActions.IsValidIndex(CurrentActionIndex))
		{
			PlayerInputIdleActions[CurrentActionIndex]->Stop();
		}

		if (RefreshMethod == EIdleActionMethod::Random)
		{
			CurrentActionIndex = FMath::RandRange(0, PlayerInputIdleActions.Num() - 1);
		}
		else if (RefreshMethod == EIdleActionMethod::Sequence)
		{
			const int32 NextIndex = CurrentActionIndex + 1;
			CurrentActionIndex = NextIndex == PlayerInputIdleActions.Num() ? 0 : NextIndex;
		}

		PlayerInputIdleActions[CurrentActionIndex]->Start();
	}
}

APlayerController* UPlayerInputIdleActionComponent::GetOwnerPlayerController() const
{
	if (GetOwner()->IsA(APlayerController::StaticClass()))
	{
		return Cast<APlayerController>(GetOwner());
	}
	else if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (Pawn->IsPlayerControlled())
		{
			return Pawn->GetController<APlayerController>();
		}
	}

	return nullptr;
}

UEnhancedInputComponent* UPlayerInputIdleActionComponent::GetOwnerEnhancedInputComponent() const
{
	if (const APlayerController* PC = GetOwnerPlayerController())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			return EnhancedInputComponent;
		}
	}
	return nullptr;
}
