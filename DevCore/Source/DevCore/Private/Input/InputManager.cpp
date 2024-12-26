// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputManager.h"

#include "EnhancedInputSubsystems.h"
#include "Input/InputIdle.h"
#include "Input/InputManagerSetting.h"

#define LOCTEXT_NAMESPACE "UInputManager"

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
	return Super::ShouldCreateSubsystem(Outer);
}

void UInputManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UInputManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UInputManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UInputManager::Tick(float DeltaTime)
{
	FTickableInternalManager::Tick(DeltaTime);
	IdleTime += DeltaTime;

	TArray<FInputIdleInfo>& TempInputIdleInfos = InputIdleInfos;
	for (auto& InputIdleInfo : TempInputIdleInfos)
	{
		InputIdleInfo.SwitchIdleState(IdleTime);
	}
}

void UInputManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

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

void UInputManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);
}

bool UInputManager::RegisterIdleData(UInputIdle* InputIdle, const FInputIdleDelegate& OnIdle, const FInputIdleDelegate& OnContinue)
{
	if (!IsValid(InputIdle))
	{
		DLOG(LogInput, Warning, TEXT("InputIdle Is NULL"))
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
		DLOG(LogInput, Warning, TEXT("InputIdle Is NULL"))
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
