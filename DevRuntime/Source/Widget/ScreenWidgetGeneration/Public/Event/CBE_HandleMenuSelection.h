// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CBE_HandleMenuSelection.generated.h"

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCBE_HandleMenuSelection : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Menu"), Category="OnActived")
	FGameplayTag ActiveSelectMenuTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Menu"), Category="OnActived")
	FGameplayTag ActiveDeselectMenuTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Menu"), Category="OnInactived")
	FGameplayTag InactiveSelectMenuTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Menu"), Category="OnInactived")
	FGameplayTag InactiveDeselectMenuTag;
};
