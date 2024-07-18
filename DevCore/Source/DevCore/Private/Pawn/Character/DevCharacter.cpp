// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Character/DevCharacter.h"

#include "Manager/ManagerGlobal.h"
#include "Pawn/PawnManager.h"


ADevCharacter::ADevCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADevCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetManager<UPawnManager>()->RegisterPawn(this);
}

void ADevCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetManager<UPawnManager>()->UnRegisterPawn(this);
	Super::EndPlay(EndPlayReason);
}

APawn* ADevCharacter::GetPawn()
{
	return this;
}

FGameplayTag ADevCharacter::GetPawnTag()
{
	return PawnTag;
}
