// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Character/CharacterManager.h"

#include "Character/DevCharacter.h"

bool UCharacterManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UCharacterManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	ADevCharacter::OnCharacterRegister.AddUObject(this, &UCharacterManager::RegisterCharacter);
	ADevCharacter::OnCharacterUnRegister.AddUObject(this, &UCharacterManager::UnRegisterCharacter);
}

void UCharacterManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	ADevCharacter::OnCharacterRegister.RemoveAll(this);
	ADevCharacter::OnCharacterUnRegister.RemoveAll(this);
}

bool UCharacterManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return Super::DoesSupportWorldType(WorldType);
}

void UCharacterManager::RegisterCharacter(ADevCharacter* Character)
{
	if (IsValid(Character) && !Characters.Contains(Character))
	{
		Characters.Add(Character);
	}
}

void UCharacterManager::UnRegisterCharacter(ADevCharacter* Character)
{
	if (IsValid(Character) && Characters.Contains(Character))
	{
		Characters.Remove(Character);
	}
}
