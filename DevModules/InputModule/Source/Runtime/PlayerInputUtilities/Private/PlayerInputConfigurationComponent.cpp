// Copyright ChenTaiye 2025. All Rights Reserved.


#include "PlayerInputConfigurationComponent.h"

#include "PlayerInputManager.h"

UPlayerInputConfigurationComponent::UPlayerInputConfigurationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITOR
	if (UInputMappingContext* BasicMappingContext = LoadObject<UInputMappingContext>(nullptr,TEXT("/Script/EnhancedInput.InputMappingContext'/DevCore/Input/IMC_Basic.IMC_Basic'")))
	{
		if (!EnhancedInputMappingContexts.Contains(BasicMappingContext))
		{
			FEnhancedInputMappingContext BasicControlInputMappingContext;
			BasicControlInputMappingContext.InputMappingContext = BasicMappingContext;

			EnhancedInputMappingContexts.Add(BasicControlInputMappingContext);
		}
	}
#endif
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
	if (UPlayerInputManager* PlayerInputManager = GetOwnerPlayerInputManager())
	{
		for (auto& EnhanceInputMappingContext : EnhancedInputMappingContexts)
		{
			PlayerInputManager->AddMappingContext(EnhanceInputMappingContext.InputMappingContext, EnhanceInputMappingContext.Priority, EnhanceInputMappingContext.ModifyContextOptions);
		}
	}
}

void UPlayerInputConfigurationComponent::RemovePlayerInput_Implementation()
{
	if (UPlayerInputManager* PlayerInputManager = GetOwnerPlayerInputManager())
	{
		for (const auto& EnhanceInputMappingContext : EnhancedInputMappingContexts)
		{
			PlayerInputManager->RemoveMappingContext(EnhanceInputMappingContext.InputMappingContext);
		}
	}
}

UPlayerInputManager* UPlayerInputConfigurationComponent::GetOwnerPlayerInputManager() const
{
	if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		const APlayerController* PC = Cast<APlayerController>(Pawn->Controller);
		if (IsValid(PC))
		{
			if (UPlayerInputManager* PlayerInputManager = PC->GetLocalPlayer()->GetSubsystem<UPlayerInputManager>())
			{
				return PlayerInputManager;
			}
		}
	}

	return nullptr;
}
