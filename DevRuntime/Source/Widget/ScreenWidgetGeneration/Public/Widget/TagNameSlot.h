// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InstanceSlot.h"
#include "TagNameSlot.generated.h"

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UTagNameSlot : public UInstanceSlot
{
	GENERATED_UCLASS_BODY()

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(Categories="HUD"))
	FGameplayTag SlotTag;
};
