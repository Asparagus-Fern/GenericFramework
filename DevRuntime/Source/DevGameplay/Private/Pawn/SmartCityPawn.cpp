// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/SmartCityPawn.h"

#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Camera/CameraComponent.h"
#include "Pawn/Component/PawnSpringArmComponent.h"

ASmartCityPawn::ASmartCityPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnName = "SmartCityPawn";
}

void ASmartCityPawn::AddZoom_Implementation(float InValue)
{
	/* 当前可评估，且弹簧臂进入评估范围时 */
	if (bEnableReassessment && SpringArmComponent->GetIsReassessment(InValue))
	{
		const bool Collision = SpringArmComponent->bDoCollisionTest;
		SpringArmComponent->bDoCollisionTest = false;

		FHitResult HitResult;
		if (UBPFunctions_Gameplay::GetComponentForwardHitResult(GetActiveCameraComponent(), HitResult, ECC_Pawn))
		{
			bEnableReassessment = false;

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
		}

		SpringArmComponent->bDoCollisionTest = Collision;
		return;
	}

	Super::AddZoom_Implementation(InValue);

	/* 当已经评估过一次，且弹簧臂离开评估范围时，启用下一次评估 */
	if (!bEnableReassessment && !SpringArmComponent->GetIsReassessment(InValue))
	{
		bEnableReassessment = true;
	}
}
