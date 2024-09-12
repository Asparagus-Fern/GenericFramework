// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "CharacterStateManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERSTATUSSYSTEM_API UCharacterStateManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
};
