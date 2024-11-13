// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DevHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEVGAMEPLAY_API ADevHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:
	virtual void DrawHUD() override;

protected:
	virtual void DrawMapScale();
};
