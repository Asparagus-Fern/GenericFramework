// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/SmartCityPawn.h"

#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Camera/CameraComponent.h"
#include "InputIdleAction/PlayerInputIdleActionComponent.h"
#include "Pawn/Component/PawnSpringArmComponent.h"

ASmartCityPawn::ASmartCityPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnName = "SmartCityPawn";

	PlayerInputIdleActionComponent = CreateDefaultSubobject<UPlayerInputIdleActionComponent>("PlayerInputIdleActionComponent");
}

bool ASmartCityPawn::ReassessmentTargetArmLength_Implementation()
{
	Super::ReassessmentTargetArmLength_Implementation();

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
