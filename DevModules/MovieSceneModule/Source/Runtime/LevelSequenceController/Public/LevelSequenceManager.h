// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceType.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelSequenceManager.generated.h"

class ULevelSequence;
class ALevelSequenceActor;
class ULevelSequencePlayer;

/**
 * 
 */
UCLASS()
class LEVELSEQUENCECONTROLLER_API ULevelSequenceManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	UFUNCTION(BlueprintCallable)
	bool RegisterLevelSequence(FName SequenceID, ULevelSequence* InSequence, FLevelSequenceHandle& LevelSequenceHandle);

	UFUNCTION(BlueprintCallable)
	void UnRegisterLevelSequence(FName SequenceID);

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FLevelSequenceHandle> LevelSequenceHandles;
};
