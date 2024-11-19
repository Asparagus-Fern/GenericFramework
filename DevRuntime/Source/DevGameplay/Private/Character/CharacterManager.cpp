// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterManager.h"

#include "Character/CharacterManagerSetting.h"
#include "Character/DevCharacter.h"

bool UCharacterManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UCharacterManagerSetting::Get()->GetEnableManager();
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
