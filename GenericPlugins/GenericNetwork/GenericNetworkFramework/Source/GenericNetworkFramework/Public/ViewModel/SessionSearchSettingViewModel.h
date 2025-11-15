// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineSessionSettings.h"
#include "SessionSearchSettingViewModel.generated.h"

class USessionSearchResultViewModel;
/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchSettingViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	TSharedRef<FOnlineSessionSearch> GetSessionSettings();
	void SetSessionSettings(const TSharedRef<FOnlineSessionSearch>& InSessionSettings);

	UFUNCTION(BlueprintPure)
	void GetSessionSearchResults(TArray<USessionSearchResultViewModel*>& OutResults) const;

	UFUNCTION(BlueprintCallable)
	void RefreshSessionSearchResults();
	
public:
	/* 最大查询结果数量 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxSearchResults = 10;

	/* 查询是否用于局域网匹配。如果为true，则搜索局域网内的会话；如果为false，则搜索在线会话。 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite)
	bool bIsLanQuery = false;

	/* 等待搜索结果的超时时间（以秒为单位） */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite)
	float TimeoutInSeconds = 60.f;

public:
	/* 只搜索专用服务器 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly)
	bool bDedicatedOnly = false;

	/* 只搜索空服务器 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly)
	bool bEmptyServerOnly = false;

	/* 只搜索非空服务器 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly)
	bool bNotEmptyServerOnly = false;

	/* 搜索会话的用户ID */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly)
	FString SearchUserName;

	/* 会话搜索中匹配的关键字 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly)
	FString SearchKeywords;

private:
	TSharedPtr<FOnlineSessionSearch> SessionSettings = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<USessionSearchResultViewModel>> SearchResults;
};
