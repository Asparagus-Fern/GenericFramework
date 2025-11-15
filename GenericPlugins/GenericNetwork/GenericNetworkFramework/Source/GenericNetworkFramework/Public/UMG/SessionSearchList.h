// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "SessionSearchList.generated.h"

class USessionSearchListItemObject;
class USessionSearchResultViewModel;
class UListView;

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
	UFUNCTION(BlueprintCallable)
	void SetSessionSearchResult(const TArray<USessionSearchResultViewModel*>& InViewModels);

	UFUNCTION(BlueprintNativeEvent)
	void OnFindSessionsStart();

	UFUNCTION(BlueprintNativeEvent)
	void OnFindSessionsComplete();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UListView> ListView_SessionSearch;

	UPROPERTY()
	TArray<TObjectPtr<USessionSearchListItemObject>> SessionSearchListItemObjects;
};
