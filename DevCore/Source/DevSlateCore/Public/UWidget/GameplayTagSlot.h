// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/NamedSlot.h"
#include "GameplayTagSlot.generated.h"

class UGameplayTagSlot;

DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayTagSlotDelegate, UGameplayTagSlot*)
static FGameplayTagSlotDelegate OnGameplayTagSlotBuild;
static FGameplayTagSlotDelegate OnGameplayTagSlotDestroy;

/**
 * 带GameplayTag的插槽
 */
UCLASS()
class DEVSLATECORE_API UGameplayTagSlot : public UNamedSlot
{
	GENERATED_BODY()

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void BeginDestroy() override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(Categories="HUD"))
	FGameplayTag SlotTag;
};
