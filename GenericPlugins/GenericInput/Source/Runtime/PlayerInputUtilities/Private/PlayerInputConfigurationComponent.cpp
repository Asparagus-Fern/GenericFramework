// Copyright ChenTaiye 2025. All Rights Reserved.


#include "PlayerInputConfigurationComponent.h"

#include "EnhancedInputSubsystems.h"

UPlayerInputConfigurationComponent::UPlayerInputConfigurationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

// #if WITH_EDITOR
// 	if (UInputMappingContext* BasicMappingContext = LoadObject<UInputMappingContext>(nullptr,TEXT("/Script/EnhancedInput.InputMappingContext'/DevCore/Input/IMC_Basic.IMC_Basic'")))
// 	{
// 		if (!EnhancedInputMappingContexts.Contains(BasicMappingContext))
// 		{
// 			FEnhancedInputMappingContext BasicControlInputMappingContext;
// 			BasicControlInputMappingContext.InputMappingContext = BasicMappingContext;
//
// 			EnhancedInputMappingContexts.Add(BasicControlInputMappingContext);
// 		}
// 	}
// #endif
}

void UPlayerInputConfigurationComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInput();
}

void UPlayerInputConfigurationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	RemovePlayerInput();
}

void UPlayerInputConfigurationComponent::SetupPlayerInput_Implementation()
{
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem())
	{
		for (auto& EnhanceInputMappingContext : EnhancedInputMappingContexts)
		{
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(EnhanceInputMappingContext.InputMappingContext, EnhanceInputMappingContext.Priority, EnhanceInputMappingContext.ModifyContextOptions);
		}
	}
}

void UPlayerInputConfigurationComponent::RemovePlayerInput_Implementation()
{
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem())
	{
		for (const auto& EnhanceInputMappingContext : EnhancedInputMappingContexts)
		{
			EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(EnhanceInputMappingContext.InputMappingContext);
		}
	}
}

UEnhancedInputLocalPlayerSubsystem* UPlayerInputConfigurationComponent::GetEnhancedInputLocalPlayerSubsystem()
{
	const ULocalPlayer* LocalPlayer = nullptr;

	if (const APlayerController* PC = Cast<APlayerController>(GetOwner()))
	{
		LocalPlayer = PC->GetLocalPlayer();
	}
	else if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (const APlayerController* PawnController = Cast<APlayerController>(Pawn->GetController()))
		{
			LocalPlayer = PawnController->GetLocalPlayer();
		}
	}

	if (!IsValid(LocalPlayer))
	{
		return nullptr;
	}

	return LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
}
