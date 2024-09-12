// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputManager.h"

#include "EnhancedInputSubsystems.h"
#include "Input/CommonInputComponent.h"
#include "Input/InputIdle.h"
#include "Input/InputManagerSetting.h"
#include "Input/PlayerInputBinding.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "UInputManager"

UInputManager::UInputManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickable = true;
}

FInputIdleInfo::FInputIdleInfo()
{
}

FInputIdleInfo::FInputIdleInfo(UInputIdle* InInputIdle, const FInputIdleDelegate& InIdle, const FInputIdleDelegate& InContinue)
	: InputIdle(InInputIdle),
	  OnIdle(InIdle),
	  OnContinue(InContinue)
{
}

bool FInputIdleInfo::SwitchIdleState(const float IdleTime)
{
	if (IdleTime < InputIdle->IdleTime)
	{
		if (bIsIdle)
		{
			bIsIdle = false;
			OnContinue.ExecuteIfBound(InputIdle);
			return true;
		}
	}
	else
	{
		if (!bIsIdle)
		{
			bIsIdle = true;
			OnIdle.ExecuteIfBound(InputIdle);
			return true;
		}
	}

	return false;
}

void FInputIdleInfo::Invalid() const
{
	if (bIsIdle)
		OnContinue.ExecuteIfBound(InputIdle);
}

bool UInputManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UInputManagerSetting::Get()->bEnableSubsystem;
}

void UInputManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IdleTime += DeltaTime;

	TArray<FInputIdleInfo>& TempInputIdleInfos = InputIdleInfos;
	for (auto& InputIdleInfo : TempInputIdleInfos)
	{
		InputIdleInfo.SwitchIdleState(IdleTime);
	}
}

void UInputManager::NativeOnActived()
{
	Super::NativeOnActived();

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		const APlayerController* PC = Iterator->Get();
		if (IsValid(PC))
		{
			if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				for (auto& EnhanceInputMappingContext : UInputManagerSetting::Get()->EnhanceInputMappingContexts)
				{
					EnhancedInputLocalPlayerSubsystem->AddMappingContext(EnhanceInputMappingContext.InputMappingContext, EnhanceInputMappingContext.Priority, EnhanceInputMappingContext.ModifyContextOptions);
				}
			}
		}
	}
}

void UInputManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}

void UInputManager::RegisterPlayerInputHandle(UPlayerInputBinding* PlayerInputBinding)
{
	if (!IsValid(PlayerInputBinding))
	{
		LOG(Debug_Input, Warning, TEXT("PlayerInputBinding Is NULL"))
		return;
	}

	if (PlayerInputBindings.Contains(PlayerInputBinding))
	{
		LOG(Debug_Input, Warning, TEXT("PlayerInputBinding Is Alrealy Register"))
		return;
	}

	if (const APlayerController* PC = UGameplayStatics::GetPlayerController(this, PlayerInputBinding->PlayerIndex))
	{
		if (UCommonInputComponent* InputComponent = Cast<UCommonInputComponent>(PC->InputComponent))
		{
			PlayerInputBinding->SetupBinding(InputComponent);
			PlayerInputBindings.Add(PlayerInputBinding);
		}
	}
}

void UInputManager::UnRegisterPlayerInputHandle(UPlayerInputBinding* PlayerInputBinding)
{
	if (!IsValid(PlayerInputBinding))
	{
		LOG(Debug_Input, Warning, TEXT("PlayerInputBinding Is NULL"))
		return;
	}

	if (!PlayerInputBindings.Contains(PlayerInputBinding))
	{
		LOG(Debug_Input, Warning, TEXT("PlayerInputBinding Is Not Register"))
		return;
	}

	if (const APlayerController* PC = UGameplayStatics::GetPlayerController(this, PlayerInputBinding->PlayerIndex))
	{
		if (UCommonInputComponent* InputComponent = Cast<UCommonInputComponent>(PC->InputComponent))
		{
			PlayerInputBinding->ClearupBinding(InputComponent);
			PlayerInputBindings.Remove(PlayerInputBinding);
		}
	}
}

bool UInputManager::RegisterIdleData(UInputIdle* InputIdle, const FInputIdleDelegate& OnIdle, const FInputIdleDelegate& OnContinue)
{
	if (!IsValid(InputIdle))
	{
		LOG(Debug_Input, Warning, TEXT("InputIdle Is NULL"))
		return false;
	}

	if (InputIdleInfos.Contains(InputIdle))
	{
		return false;
	}

	InputIdleInfos.Add(FInputIdleInfo(InputIdle, OnIdle, OnContinue));
	return true;
}

void UInputManager::UnRegisterIdleData(UInputIdle* InputIdle)
{
	if (!IsValid(InputIdle))
	{
		LOG(Debug_Input, Warning, TEXT("InputIdle Is NULL"))
		return;
	}

	if (!InputIdleInfos.Contains(InputIdle))
	{
		return;
	}

	const FInputIdleInfo InputIdleInfo = *InputIdleInfos.FindByKey(InputIdle);
	InputIdleInfo.Invalid();
	InputIdleInfos.Remove(InputIdleInfo);
}

bool UInputManager::IsIdle(UInputIdle* InputIdle, bool& Idle)
{
	if (IsValid(InputIdle) && InputIdleInfos.Contains(InputIdle))
	{
		const FInputIdleInfo InputIdleInfo = *InputIdleInfos.FindByKey(InputIdle);
		Idle = InputIdleInfo.bIsIdle;
		return true;
	}

	return false;
}

void UInputManager::RefreshIdleTime()
{
	IdleTime = 0.f;
}

#undef LOCTEXT_NAMESPACE
