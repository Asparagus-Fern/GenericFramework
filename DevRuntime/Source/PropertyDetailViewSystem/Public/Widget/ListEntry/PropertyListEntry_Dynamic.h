// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntryBase.h"
#include "PropertyListEntry_Dynamic.generated.h"

class UPropertyValueBase;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, meta=(DisableNativeTick))
class PROPERTYDETAILVIEWSYSTEM_API UPropertyListEntry_Dynamic : public UPropertyListEntryBase
{
	GENERATED_BODY()

public:
	virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	virtual void OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson) override;
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName="SetPropertyEntity")
	void BP_SetPropertyEntity();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnPropertyChanged")
	void BP_OnPropertyChanged();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="RefreshEditableState")
	void BP_RefreshEditableState(bool bIsEnable);
};
