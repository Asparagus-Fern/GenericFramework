// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntry.h"
#include "PropertyListEntry_Discrete.generated.h"

class UPropertyDiscreteValue;
class UCommonButtonBase;
class UCommonRotator;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyListEntry_Discrete : public UPropertyListEntry
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	virtual void NativeOnEntryReleased() override;

	virtual void OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson) override;
	virtual void OnPropertyEditConditionChanged(UPropertyEntity* InProperty) override;
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;

	virtual void Refresh() PURE_VIRTUAL(,);

protected:
	UPROPERTY()
	TObjectPtr<UPropertyDiscreteValue> DiscreteProperty;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPanelWidget> Panel_Value;
};
