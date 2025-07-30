// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Pawn/SmartCityPawn.h"

#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Camera/CameraComponent.h"
#include "Component/PawnSpringArmComponent.h"
#include "InputIdleAction/PlayerInputIdleActionComponent.h"

ASmartCityPawn::ASmartCityPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerInputIdleActionComponent = CreateDefaultSubobject<UPlayerInputIdleActionComponent>("PlayerInputIdleActionComponent");
}

bool ASmartCityPawn::ReassessmentFocus_Implementation()
{
	Super::ReassessmentFocus_Implementation();

	const bool Collision = SpringArmComponent->bDoCollisionTest;
	SpringArmComponent->bDoCollisionTest = false;

	FHitResult HitResult;
	if (UBPFunctions_Gameplay::GetComponentForwardHitResult(GetActiveCameraComponent(), HitResult, ECC_Pawn))
	{
		if (Collision)
		{
			Execute_SetLocation(this, (GetActiveCameraComponent()->GetForwardVector() * (HitResult.Distance - 20.f) + GetActiveCameraComponent()->GetComponentLocation()));
			Execute_SetZoom(this, (HitResult.Distance - 20.f));
		}
		else
		{
			Execute_SetLocation(this, HitResult.Location);
			Execute_SetZoom(this, HitResult.Distance);
		}

		SpringArmComponent->bDoCollisionTest = Collision;
		return true;
	}

	SpringArmComponent->bDoCollisionTest = Collision;
	return false;
}
