// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Manager/CoreManager.h"
#include "PawnManager.generated.h"

class ADevPawn;

/**
 * 
 */
UCLASS(MinimalAPI)
class UPawnManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

protected:
	UPROPERTY(Transient)
	TArray<ADevPawn*> Pawns;

protected:
	void RegisterPawn(ADevPawn* Pawn);
	void UnRegisterPawn(ADevPawn* Pawn);
};
