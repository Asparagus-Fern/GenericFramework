// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pawn/PawnInterface.h"
#include "DevCharacter.generated.h"

UCLASS()
class DEVCORE_API ADevCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADevCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
