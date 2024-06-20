// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/NamedSlot.h"
#include "TagNameSlot.generated.h"

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UTagNameSlot : public UNamedSlot
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(Categories="HUD"))
	FGameplayTag SlotTag;
};
