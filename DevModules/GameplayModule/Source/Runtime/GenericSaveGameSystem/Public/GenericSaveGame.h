// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GenericSaveGame.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GENERICSAVEGAMESYSTEM_API UGenericSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	virtual void OnSaved();
	virtual void OnLoaded();

public:
	UFUNCTION(BlueprintPure)
	FDateTime GetLastSaveTime() const;

	UFUNCTION(BlueprintPure)
	FDateTime GetLastLoadTime() const;
	
private:
	UPROPERTY()
	FDateTime LastSaveTime;

	UPROPERTY()
	FDateTime LastLoadTime;
};
