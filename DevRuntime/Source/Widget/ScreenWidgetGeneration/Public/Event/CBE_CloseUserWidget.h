// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CBE_CloseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCBE_CloseUserWidget : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="HUD"))
	FGameplayTag SlotTag;

public:
	// virtual bool GetIsAsync() override { return true; }
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

protected:
	virtual void OnCloseFinish();
};
