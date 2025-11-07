// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NetworkType.h"
#include "SessionSearchListViewModel.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGetSessionSearchResult, const TArray<FOnlineSessionSearchResult>&)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGetPageSessionSearchResult, const TArray<FOnlineSessionSearchResult>&)

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchListViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(FieldNotify, BlueprintPure)
	int32 GetItemsPerPage() const;

	UFUNCTION(BlueprintCallable)
	void SetItemsPerPage(int32 InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	int32 GetPageIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetPageIndex(int32 InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	int32 GetTotalPageIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetTotalPageIndex(int32 InValue);
	
public:
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite)
	ESessionState SessionState = ESessionState::InValid;

	UPROPERTY(FieldNotify, EditDefaultsOnly, meta=(ClampMin = 1), Getter, Setter, BlueprintGetter="GetItemsPerPage", BlueprintSetter="SetItemsPerPage")
	int32 ItemsPerPage = 10;

	UPROPERTY(FieldNotify, EditDefaultsOnly, meta=(ClampMin = 0), Getter, Setter, BlueprintGetter="GetPageIndex", BlueprintSetter="SetPageIndex")
	int32 PageIndex = 0;

	UPROPERTY(FieldNotify, EditDefaultsOnly, meta=(ClampMin = 0), Getter,Setter,  BlueprintGetter="GetTotalPageIndex", BlueprintSetter="SetTotalPageIndex")
	int32 TotalPageIndex = 0;

public:
	FOnGetSessionSearchResult& GetOnGetSessionSearchResultEvent() { return OnGetSessionSearchResultEvent; }
	FOnGetPageSessionSearchResult& GetOnGetPageSessionSearchResultEvent() { return OnGetPageSessionSearchResultEvent; }

	const TArray<FOnlineSessionSearchResult>& GetSearchResults();
	void SetSearchResults(const TArray<FOnlineSessionSearchResult>& InResults);

protected:
	TArray<FOnlineSessionSearchResult> GetPageResult();

private:
	TArray<FOnlineSessionSearchResult> SearchResults;
	FOnGetSessionSearchResult OnGetSessionSearchResultEvent;
	FOnGetPageSessionSearchResult OnGetPageSessionSearchResultEvent;
};
