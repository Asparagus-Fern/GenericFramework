// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "PropertyListEntryBase.generated.h"

class FPropertyEditableState;
class UTextBlock;
class UPropertyEntity;

/**
 * 
 */
UCLASS(Abstract, NotBlueprintable, MinimalAPI)
class UPropertyListEntryBase : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	/* IUserObjectListEntry */
protected:
	virtual void NativeOnEntryReleased() override;

	/* UPropertyListEntryBase */
public:
	virtual void SetPropertyEntity(UPropertyEntity* InProperty);

protected:
	virtual void OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson);
	virtual void OnPropertyEditConditionChanged(UPropertyEntity* InProperty);
	virtual void RefreshEditableState(FPropertyEditableState InEditableState);

protected:
	bool bSuspendChangeUpdates = false;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPropertyEntity> PropertyEntity;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	TObjectPtr<UUserWidget> Background;

private:
	void HandlePropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson);
	void HandlePropertyEditConditionChanged(UPropertyEntity* InProperty);
};
