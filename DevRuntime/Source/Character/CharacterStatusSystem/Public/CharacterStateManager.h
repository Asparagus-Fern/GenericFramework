// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreManager.h"
#include "CharacterStateManager.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERSTATUSSYSTEM_API UCharacterStateManager : public UCoreManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};
