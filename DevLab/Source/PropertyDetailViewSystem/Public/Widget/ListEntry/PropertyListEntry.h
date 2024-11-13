// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntryBase.h"
#include "PropertyListEntry.generated.h"

/**
 * 
 */
UCLASS(Abstract, NotBlueprintable, meta=(DisableNativeTick))
class PROPERTYDETAILVIEWSYSTEM_API UPropertyListEntry : public UPropertyListEntryBase
{
	GENERATED_BODY()

protected:
	virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	TObjectPtr<UTextBlock> Text_DisplayName;
};
