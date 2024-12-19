// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Handle/HandleInterface.h"
#include "LevelSequenceHandle.h"
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
class LEVELSEQUENCESYSTEM_API ULevelSequenceManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* ULevelSequenceManager */
public:
	virtual ULevelSequenceHandle* RegisterLevelSequence(ULevelSequence* InLevelSequence);
	virtual void UnRegisterLevelSequence(ULevelSequence* InLevelSequence);
	virtual void UnRegisterLevelSequence(ULevelSequenceHandle* InLevelSequenceHandle);

	bool IsLevelSequenceRegister(const ULevelSequence* InLevelSequence);
	ULevelSequenceHandle* GetLevelSequenceHandle(const ULevelSequence* InLevelSequence);

protected:
	UPROPERTY()
	TArray<ULevelSequenceHandle*> LevelSequenceHandles;
};
