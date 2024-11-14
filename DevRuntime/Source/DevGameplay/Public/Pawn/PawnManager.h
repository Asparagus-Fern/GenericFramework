// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreManager.h"
#include "PawnManager.generated.h"

class ADevPawn;

/**
 * 
 */
UCLASS()
class DEVGAMEPLAY_API UPawnManager : public UCoreManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UPawnManager */
protected:
	UPROPERTY(Transient)
	TArray<ADevPawn*> Pawns;

protected:
	void RegisterPawn(ADevPawn* Pawn);
	void UnRegisterPawn(ADevPawn* Pawn);
};
