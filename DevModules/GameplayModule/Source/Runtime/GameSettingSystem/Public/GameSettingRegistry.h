// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyRegistry.h"
#include "GameSettingRegistry.generated.h"

class UPropertyCollection;

#define GET_GAME_SETTING_PATH(FunctionOrPropertyName) \
MakeShared<FPropertyDataSource>(TArray<FString>({ \
	GET_FUNCTION_NAME_STRING_CHECKED(UGameSettings, GetGameSettings), \
	GET_FUNCTION_NAME_STRING_CHECKED(UGameUserSettings, FunctionOrPropertyName) \
}))

/**
 * 
 */
UCLASS()
class GAMESETTINGSYSTEM_API UGameSettingRegistry : public UPropertyRegistry
{
	GENERATED_BODY()

public:
	virtual void Initialize() override;
	virtual void SavePropertyChanges() override;

public:
	UPropertyCollection* GetGameSettingCollection() const { return Collection; }

private:
	UPROPERTY()
	UPropertyCollection* Collection;
};
