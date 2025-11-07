// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "Base/GenericWidget.h"
#include "SessionSearchList.generated.h"

class USessionSearchListViewModel;
class USessionSearchSettingsViewModel;
class UListView;
class FOnlineSessionSearch;

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchList : public UGenericWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintPure)
	USessionSearchListViewModel* GetSessionSearchListViewModel();

	UFUNCTION(BlueprintCallable)
	void SetSessionSearchListViewModel(USessionSearchListViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnSessionStateChanged(ESessionState InSessionState);

	UFUNCTION(BlueprintNativeEvent)
	void OnItemsPerPageChanged(int32 InItemsPerPage);

	UFUNCTION(BlueprintNativeEvent)
	void OnPageIndexChanged(int32 InPageIndex);

	virtual void OnGetSessionSearchResult(const TArray<FOnlineSessionSearchResult>& InResults);
	virtual void OnGetPageSessionSearchResult(const TArray<FOnlineSessionSearchResult>& InResults);

	UPROPERTY()
	TObjectPtr<USessionSearchListViewModel> SessionSearchListViewModel = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UListView> ListView_SessionSearch;

	TSharedPtr<FOnlineSessionSearch> Settings;
};
