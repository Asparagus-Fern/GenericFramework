// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DevPlayerController.generated.h"

class IPawnInputInterface;

/**
 * 
 */
UCLASS()
class DEVCORE_API ADevPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADevPlayerController();
	// virtual void OnPossess(APawn* InPawn) override;
	// virtual void OnUnPossess() override;
};
