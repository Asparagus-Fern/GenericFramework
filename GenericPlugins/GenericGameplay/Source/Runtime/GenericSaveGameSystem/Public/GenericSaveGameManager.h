// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameType.h"
#include "Interface/ManagerInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GenericSaveGameManager.generated.h"

class USaveGame;
class UGenericSaveGame;

/**
 * 
 */
UCLASS()
class GENERICSAVEGAMESYSTEM_API UGenericSaveGameManager : public UGameInstanceSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void AsyncSaveGame(const FSaveGameParameter& Parameter);
	void OnAsyncSaveGameCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	void AsyncLoadGame(const FSaveGameParameter& Parameter);
	void OnAsyncLoadGameCompleted(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);

public:
	void StartAutoSaveGame();
	void StopAutoSaveGame();
	
private:
	TArray<FSaveGameParameter> SaveGameParameters;
	TArray<FSaveGameParameter> LoadGameParameters;

private:
	TArray<FSaveGameParameter> AutoSaveParameters;
};
