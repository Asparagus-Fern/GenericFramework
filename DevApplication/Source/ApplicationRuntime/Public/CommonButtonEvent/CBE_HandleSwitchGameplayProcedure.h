// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleSwitchGameplayProcedure.generated.h"

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandleSwitchGameplayProcedure : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	// virtual bool GetIsAsync() override { return true; }
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Procedure"))
	FGameplayTag SwitchGameplayProcedureTagOnActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Procedure"))
	FGameplayTag SwitchGameplayProcedureTagOnInactive;

protected:
	virtual void OnActiveGameplayProcedureSwitchFinish();
	virtual void OnInactiveGameplayProcedureSwitchFinish();
};
