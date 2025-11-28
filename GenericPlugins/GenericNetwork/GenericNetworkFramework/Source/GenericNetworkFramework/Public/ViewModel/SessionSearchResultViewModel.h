// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NetworkType.h"
#include "OnlineSessionSettings.h"
#include "SessionSearchResultViewModel.generated.h"

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchResultViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	const FOnlineSessionSearchResult& GetSessionSearchResult() const;
	void SetSessionSearchResult(const FOnlineSessionSearchResult& InResult);

public:
	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly)
	FGenericSessionSearchResult SessionSearchResult;
};
