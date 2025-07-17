// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Pawn/PawnManager.h"

#include "Pawn/GenericPawn.h"

#define LOCTEXT_NAMESPACE "UPawnManager"

bool UPawnManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UPawnManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	AGenericPawn::OnPawnRegister.AddUObject(this, &UPawnManager::RegisterPawn);
	AGenericPawn::OnPawnUnRegister.AddUObject(this, &UPawnManager::UnRegisterPawn);
}

void UPawnManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	AGenericPawn::OnPawnRegister.RemoveAll(this);
	AGenericPawn::OnPawnUnRegister.RemoveAll(this);
}

bool UPawnManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UPawnManager::RegisterPawn(AGenericPawn* Pawn)
{
	if (IsValid(Pawn) && !Pawns.Contains(Pawn))
	{
		Pawns.Add(Pawn);
	}
}

void UPawnManager::UnRegisterPawn(AGenericPawn* Pawn)
{
	if (IsValid(Pawn) && Pawns.Contains(Pawn))
	{
		Pawns.Remove(Pawn);
	}
}

#undef LOCTEXT_NAMESPACE
