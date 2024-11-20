// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PickableDetectionComponent.h"

#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Debug/DebugType.h"


UPickableDetectionComponent::UPickableDetectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPickableDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		OwnerPawn->GetController()->OnPossessedPawnChanged.AddDynamic(this, &UPickableDetectionComponent::OnPossessedPawnChanged);

		if (UBPFunctions_Gameplay::GetIsPlayerPossessPawn(OwnerPawn))
		{
		}
	}
}

void UPickableDetectionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UPickableDetectionComponent::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (GetOwner() == OldPawn)
	{
	}
	else if (GetOwner() == NewPawn)
	{
	}
}
