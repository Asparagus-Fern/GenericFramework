// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GameSettingValueMapping.generated.h"

class UGameSettingValue;

/**
 * 
 */
UCLASS()
class GAMESETTINGSYSTEM_API UGameSettingValueMapping : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* MenuTagTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TMap<FGameplayTag, UGameSettingValue*> GameSettingValue;

public:
#if WITH_EDITOR
	UFUNCTION(CallInEditor)
	void Generate();
#endif
};
