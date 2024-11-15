// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingsInteractionManager.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API UBuildingsInteractionManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};
