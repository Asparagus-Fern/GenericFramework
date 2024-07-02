// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/SmartCityPawn.h"


ASmartCityPawn::ASmartCityPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASmartCityPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASmartCityPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASmartCityPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
