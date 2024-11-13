// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreManager.h"
#include "CharacterManager.generated.h"

class ADevCharacter;
/**
 * 
 */
UCLASS()
class DEVGAMEPLAY_API UCharacterManager : public UCoreManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UCharacterManager */
protected:
	UPROPERTY(Transient)
	TArray<ADevCharacter*> Characters;

protected:
	void RegisterCharacter(ADevCharacter* Character);
	void UnRegisterCharacter(ADevCharacter* Character);
};
