// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineSessionSearchSettingsViewModel.generated.h"

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UOnlineSessionSearchSettingsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	virtual bool GetOnlineSessionSearchSettings(TSharedPtr<class FOnlineSessionSearch>& Result);

public:
	/* 最大查询结果数量 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	int32 MaxSearchResults = 10;

	/* 查询是否用于局域网匹配。如果为true，则搜索局域网内的会话；如果为false，则搜索在线会话。 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bIsLanQuery = false;

	/* 等待搜索结果的超时时间（以秒为单位） */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	float TimeoutInSeconds = 60.f;

public:
	/* 只搜索专用服务器 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly, Category="Search Condition")
	bool bDedicatedOnly = false;

	/* 只搜索空服务器 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly, Category="Search Condition")
	bool bEmptyServerOnly = false;

	/* 只搜索非空服务器 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly, Category="Search Condition")
	bool bNotEmptyServerOnly = false;

	/* 搜索会话的用户ID */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly, Category="Search Condition")
	FString SearchUserName;

	/* 会话搜索中匹配的关键字 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly, Category="Search Condition")
	FString SearchKeywords;
};
