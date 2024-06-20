// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/GameplayProcedure.h"
#include "World/LevelStreamingType.h"
#include "ProcedurePlay_Base.generated.h"

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UProcedurePlay_Base : public UGameplayProcedure
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

protected:
	UFUNCTION()
	void OnSetAlwaysVisibleLevelsFinish();

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnFinish_SetAlwaysVisibleLevels();
};
