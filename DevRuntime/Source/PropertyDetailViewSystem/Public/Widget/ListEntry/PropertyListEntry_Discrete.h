// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntry.h"
#include "PropertyListEntry_Discrete.generated.h"

class UPropertyDiscreteValueDynamic;
class UCommonButtonBase;
class UCommonRotator;

/**
 * 
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyListEntry_Discrete : public UPropertyListEntry
{
	GENERATED_BODY()

public:
	virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	virtual void NativeOnEntryReleased() override;

	virtual void OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson) override;
	virtual void OnPropertyEditConditionChanged(UPropertyEntity* InProperty) override;
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;

	virtual void Refresh() PURE_VIRTUAL(,);

protected:
	UPROPERTY()
	TObjectPtr<UPropertyDiscreteValueDynamic> DiscreteProperty;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPanelWidget> Panel_Value;
};
