// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputType.h"
#include "Manager/CoreManager.h"
#include "InputManager.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UInputManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UInputManager();
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TArray<FEnhanceInputMappingContext> EnhanceInputMappingContexts;
};
