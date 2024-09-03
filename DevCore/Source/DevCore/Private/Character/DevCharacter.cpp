// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DevCharacter.h"

#include "Manager/ManagerGlobal.h"
#include "Pawn/PawnManager.h"


ADevCharacter::ADevCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADevCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADevCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
