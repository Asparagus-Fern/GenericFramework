// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UGameHUD : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeDestruct() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ViewportZOrder = 0;
};
