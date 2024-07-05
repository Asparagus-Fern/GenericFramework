// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CBE_OpenUserWidget.generated.h"

class UUserWidgetBase;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCBE_OpenUserWidget : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UUserWidgetBase* HandleWidget;

public:
	// virtual bool GetIsAsync() override { return true; }
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

protected:
	virtual void OnOpenFinish();
};
