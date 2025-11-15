// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Obect/GenericObject.h"
#include "Base/GenericWidget.h"
#include "SessionSearchListItem.generated.h"

class USessionSettingViewModel;
class USessionSearchResultViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class USessionSearchListItemObject : public UGenericObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<USessionSearchResultViewModel> SessionSearchResultViewModel = nullptr;
};

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchListItem : public UGenericWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
	virtual void NativeOnEntryReleased() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetSessionSearchResultViewModel(USessionSearchResultViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnSessionSearchResultViewModelSet(USessionSearchResultViewModel* InViewModel);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USessionSearchResultViewModel> SessionSearchResultViewModel = nullptr;
};
