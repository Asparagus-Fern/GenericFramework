// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Obect/GenericObject.h"
#include "Base/GenericWidget.h"
#include "SessionSearchListItem.generated.h"

class UGenericButtonWidget;
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
UCLASS(MinimalAPI)
class USessionSearchListItem : public UGenericWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	friend class USessionSearchList;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
	virtual void NativeOnEntryReleased() override;

public:
	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API void SetSessionSearchResultViewModel(USessionSearchResultViewModel* InViewModel);

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API void RefreshSelectedSession();
	GENERICNETWORKFRAMEWORK_API virtual void OnRefreshSelectedSessionComplete(int32 InPlayerIndex, bool bWasSuccessful, const FOnlineSessionSearchResult& InResult);

protected:
	UFUNCTION()
	void OnJoinButtonClicked(UGenericButtonWidget* InButton);

protected:
	UFUNCTION(BlueprintNativeEvent)
	GENERICNETWORKFRAMEWORK_API void OnSessionSearchResultViewModelSet(USessionSearchResultViewModel* InViewModel);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USessionSearchResultViewModel> SessionSearchResultViewModel = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButtonWidget> GenericButtonWidget_Join;
};
