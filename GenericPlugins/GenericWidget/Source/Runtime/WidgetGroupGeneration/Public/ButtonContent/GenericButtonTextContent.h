// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericButtonContent.h"
#include "GenericButtonTextContent.generated.h"

USTRUCT(BlueprintType)
struct FButtonTextContentTableRow : public FButtonContentTableRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Normal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Hovered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Selected;
};


/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericButtonTextContent : public UGenericButtonContent
{
	GENERATED_BODY()

protected:
	WIDGETGROUPGENERATION_API virtual bool OnInitialized() override;
	WIDGETGROUPGENERATION_API virtual TSubclassOf<UWidget> GetContentSupportClass() const override;
	WIDGETGROUPGENERATION_API virtual UStruct* GetContentRowSupportClass() const override;
	WIDGETGROUPGENERATION_API virtual void OnButtonHovered_Implementation(UGenericButtonWidget* InButton) override;
	WIDGETGROUPGENERATION_API virtual void OnButtonUnhovered_Implementation(UGenericButtonWidget* InButton) override;
	WIDGETGROUPGENERATION_API virtual void OnButtonSelectionChanged_Implementation(UGenericButtonWidget* InButton, bool InSelection) override;

protected:
	UPROPERTY()
	FButtonTextContentTableRow Cache;
};
