// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntryBase.h"
#include "PropertyListEntry.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta=(DisableNativeTick))
class PROPERTYDETAILVIEWSYSTEM_API UPropertyListEntry : public UPropertyListEntryBase
{
	GENERATED_BODY()

protected:
	virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_DisplayName;
};
