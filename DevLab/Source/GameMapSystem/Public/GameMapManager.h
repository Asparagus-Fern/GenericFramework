// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMapManager.generated.h"

class UGameMapInfo;

/**
 * 
 */
UCLASS()
class GAMEMAPSYSTEM_API UGameMapManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};
