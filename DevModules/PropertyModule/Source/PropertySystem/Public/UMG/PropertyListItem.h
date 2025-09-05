// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Generic/GenericObject.h"
#include "PropertyListItem.generated.h"

class UTextBlock;
class UPropertyValueBase;
class UPropertyValueViewModel;
class UPropertyValueSpawner;

UCLASS(EditInlineNew, MinimalAPI)
class UPropertyListItemObject : public UGenericObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PropertyName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText PropertyDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPropertyValueBase> PropertyValueClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TObjectPtr<UPropertyValueViewModel> PropertyValueViewModel = nullptr;
};


/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UPropertyListItem : public UGenericWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
	virtual void NativeOnEntryReleased() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_PropertyName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyValueSpawner> PropertyValueSpawner;
};
