// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Character/CharacterManager.h"

#include "Character/GenericCharacter.h"

bool UCharacterManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UCharacterManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	AGenericCharacter::OnCharacterRegister.AddUObject(this, &UCharacterManager::RegisterCharacter);
	AGenericCharacter::OnCharacterUnRegister.AddUObject(this, &UCharacterManager::UnRegisterCharacter);
}

void UCharacterManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	AGenericCharacter::OnCharacterRegister.RemoveAll(this);
	AGenericCharacter::OnCharacterUnRegister.RemoveAll(this);
}

bool UCharacterManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return Super::DoesSupportWorldType(WorldType);
}

void UCharacterManager::RegisterCharacter(AGenericCharacter* Character)
{
	if (IsValid(Character) && !Characters.Contains(Character))
	{
		Characters.Add(Character);
	}
}

void UCharacterManager::UnRegisterCharacter(AGenericCharacter* Character)
{
	if (IsValid(Character) && Characters.Contains(Character))
	{
		Characters.Remove(Character);
	}
}
