// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterManager.h"

#include "Character/CharacterManagerSetting.h"
#include "Character/DevCharacter.h"

bool UCharacterManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UCharacterManagerSetting::Get()->bEnableSubsystem;
}

void UCharacterManager::NativeOnActived()
{
	Super::NativeOnActived();

	ADevCharacter::OnCharacterRegister.AddUObject(this, &UCharacterManager::RegisterCharacter);
	ADevCharacter::OnCharacterUnRegister.AddUObject(this, &UCharacterManager::UnRegisterCharacter);
}

void UCharacterManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	ADevCharacter::OnCharacterRegister.RemoveAll(this);
	ADevCharacter::OnCharacterUnRegister.RemoveAll(this);
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
