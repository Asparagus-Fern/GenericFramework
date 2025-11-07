// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameType.h"
#include "Subsystem/GenericGameInstanceSubsystem.h"
#include "GenericSaveGameSubsystem.generated.h"

class USaveGame;
class UGenericSaveGame;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericSaveGameSubsystem : public UGenericGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static GENERICSAVEGAMESYSTEM_API UGenericSaveGameSubsystem* Get(const UObject* WorldContextObject);

public:
	GENERICSAVEGAMESYSTEM_API void AsyncSaveGame(const FSaveGameParameter& Parameter);
	GENERICSAVEGAMESYSTEM_API void OnAsyncSaveGameCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	GENERICSAVEGAMESYSTEM_API void AsyncLoadGame(const FSaveGameParameter& Parameter);
	GENERICSAVEGAMESYSTEM_API void OnAsyncLoadGameCompleted(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);

	GENERICSAVEGAMESYSTEM_API void StartAutoSaveGame();
	GENERICSAVEGAMESYSTEM_API void StopAutoSaveGame();

private:
	TArray<FSaveGameParameter> SaveGameParameters;
	TArray<FSaveGameParameter> LoadGameParameters;
	TArray<FSaveGameParameter> AutoSaveParameters;
};
