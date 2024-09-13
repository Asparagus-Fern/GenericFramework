// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/PlayerInputComponent.h"

#include "EnhancedInputSubsystems.h"

UPlayerInputComponent::UPlayerInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInputComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UPlayerInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerInputComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UPlayerInputComponent::SetupPlayerInput_Implementation(UInputComponent* PlayerInputComponent)
{
	if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		const APlayerController* PC = Cast<APlayerController>(Pawn->Controller);
		if (IsValid(PC))
		{
			if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				for (auto& EnhanceInputMappingContext : EnhanceInputMappingContexts)
				{
					EnhancedInputLocalPlayerSubsystem->AddMappingContext(EnhanceInputMappingContext.InputMappingContext, EnhanceInputMappingContext.Priority, EnhanceInputMappingContext.ModifyContextOptions);
				}
			}
		}
	}
}

void UPlayerInputComponent::RemovePlayerInput_Implementation(UInputComponent* PlayerInputComponent)
{
	if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		const APlayerController* PC = Cast<APlayerController>(Pawn->Controller);
		if (IsValid(PC))
		{
			if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				for (const auto& EnhanceInputMappingContext : EnhanceInputMappingContexts)
				{
					EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(EnhanceInputMappingContext.InputMappingContext);
				}
			}
		}
	}
}
