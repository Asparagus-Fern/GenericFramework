// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/GameplayProcedure.h"
#include "LevelStreamingType.h"
#include "ProcedurePlay.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedurePlay_Default);

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UProcedurePlay : public UGameplayProcedure
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
