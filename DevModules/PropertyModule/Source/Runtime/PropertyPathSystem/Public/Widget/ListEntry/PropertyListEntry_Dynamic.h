// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntryBase.h"
#include "PropertyListEntry_Dynamic.generated.h"

class UPropertyValueBase;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, MinimalAPI)
class UPropertyListEntry_Dynamic : public UPropertyListEntryBase
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

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
