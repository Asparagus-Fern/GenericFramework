// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnManager.h"

#include "Kismet/GameplayStatics.h"
#include "Pawn/DevPawn.h"
#include "Pawn/PawnManagerSetting.h"

#define LOCTEXT_NAMESPACE "UPawnManager"

bool UPawnManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UPawnManagerSetting::Get()->GetEnableManager();
}

void UPawnManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	ADevPawn::OnPawnRegister.AddUObject(this, &UPawnManager::RegisterPawn);
	ADevPawn::OnPawnUnRegister.AddUObject(this, &UPawnManager::UnRegisterPawn);
}

void UPawnManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	ADevPawn::OnPawnRegister.RemoveAll(this);
	ADevPawn::OnPawnUnRegister.RemoveAll(this);
}

bool UPawnManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UPawnManager::RegisterPawn(ADevPawn* Pawn)
{
	if (IsValid(Pawn) && !Pawns.Contains(Pawn))
	{
		Pawns.Add(Pawn);
	}
}

void UPawnManager::UnRegisterPawn(ADevPawn* Pawn)
{
	if (IsValid(Pawn) && Pawns.Contains(Pawn))
	{
		Pawns.Remove(Pawn);
	}
}

#undef LOCTEXT_NAMESPACE
