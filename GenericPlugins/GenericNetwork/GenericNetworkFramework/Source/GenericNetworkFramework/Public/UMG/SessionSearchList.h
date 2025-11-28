// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "SessionSearchList.generated.h"

class USessionSettingPanel;
class USessionSearchListItemObject;
class USessionSearchResultViewModel;
class UListView;

/**
 * 
 */
UCLASS(MinimalAPI)
class USessionSearchList : public UGenericWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API void SetSessionSearchResult(const TArray<USessionSearchResultViewModel*>& InViewModels);

	UFUNCTION(BlueprintNativeEvent)
	GENERICNETWORKFRAMEWORK_API void OnFindSessionsStart();

	UFUNCTION(BlueprintNativeEvent)
	GENERICNETWORKFRAMEWORK_API void OnFindSessionsComplete();

protected:
	GENERICNETWORKFRAMEWORK_API virtual void OnItemSelectionChanged(UObject* Item);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UListView> ListView_SessionSearch;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USessionSettingPanel> SessionSettingPanel;

	UPROPERTY()
	TArray<TObjectPtr<USessionSearchListItemObject>> SessionSearchListItemObjects;
};
