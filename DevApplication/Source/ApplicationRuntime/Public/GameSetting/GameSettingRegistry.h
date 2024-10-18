// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyRegistry.h"
#include "GameSettingRegistry.generated.h"

class UPropertyCollection;

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UGameSettingRegistry : public UPropertyRegistry
{
	GENERATED_BODY()

public:
	virtual void Initialize() override;
	virtual void SavePropertyChanges() override;

	UPropertyCollection* GetGameSettingCollection() const { return Collection; }

private:
	UPROPERTY()
	UPropertyCollection* Collection;
};
