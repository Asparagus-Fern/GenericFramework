// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntry.h"
#include "PropertyListEntry_Action.generated.h"

class UPropertyActionValue;
class UCommonButtonBase;

/**
 * 
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyListEntry_Action : public UPropertyListEntry
{
	GENERATED_BODY()

public:
	virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnEntryReleased() override;
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;

	virtual void HandleActionButtonClicked();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPropertyAssigned(const FText& ActionText);

protected:
	UPROPERTY()
	TObjectPtr<UPropertyActionValue> ActionProperty;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UCommonButtonBase> Button_Action;
};
