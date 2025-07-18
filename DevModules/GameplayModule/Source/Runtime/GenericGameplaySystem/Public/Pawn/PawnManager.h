// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "PawnManager.generated.h"

class AGenericPawn;

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
	TArray<AGenericPawn*> Pawns;

protected:
	void RegisterPawn(AGenericPawn* Pawn);
	void UnRegisterPawn(AGenericPawn* Pawn);
};
