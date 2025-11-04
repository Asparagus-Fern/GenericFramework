// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Obect/GenericObject.h"
#include "PropertyListItem.generated.h"

class UPropertyListItemOption;
class UPropertyViewModel;
class UTextBlock;
class UPropertyValueBase;
class UPropertyValueSpawner;

/**
 * 
 */
UCLASS(EditInlineNew, MinimalAPI)
class UPropertyListItemObject : public UGenericObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TObjectPtr<UPropertyViewModel> PropertyViewModel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPropertyValueBase> PropertyValueClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, TSubclassOf<UPropertyListItemOption>> PropertyOptionClasses;
};


/**
 * List Item Is a Visual Widget For Property View Model
 */
UCLASS(MinimalAPI)
class UPropertyListItem : public UGenericWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	PROPERTYSYSTEM_API virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	PROPERTYSYSTEM_API virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	PROPERTYSYSTEM_API virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
	PROPERTYSYSTEM_API virtual void NativeOnEntryReleased() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyDisplayNameChanged(const FText& InDisplayName);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyTagAdded(FGameplayTag InPropertyTag);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyTagRemoved(FGameplayTag InPropertyTag);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void AddPropertyOption(FGameplayTag InPropertyTag, TSubclassOf<UPropertyListItemOption> InClass);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void RemovePropertyOption(FGameplayTag InPropertyTag);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPropertyViewModel> PropertyViewModel = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_PropertyName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyValueSpawner> PropertyValueSpawner;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPanelWidget> Panel_PropertyOption;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UPropertyListItemOption>> PropertyOptions;
};
