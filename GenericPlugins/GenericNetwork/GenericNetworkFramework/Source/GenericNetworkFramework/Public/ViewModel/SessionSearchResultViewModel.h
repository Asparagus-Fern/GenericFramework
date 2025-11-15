// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NetworkType.h"
#include "OnlineSessionSettings.h"
#include "SessionSearchResultViewModel.generated.h"

class USessionSettingViewModel;

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchResultViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	const FOnlineSessionSearchResult& GetSessionSearchResult();
	void SetSessionSearchResult(const FOnlineSessionSearchResult& InResult);

	UFUNCTION(BlueprintPure)
	FName GetSessionName() const;
	
public:
	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly)
	int32 PingInMs;

	/* 创建该会话的玩家ID */
	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly)
	FUniqueNetIdRepl OwnerPlayerID;

	/* 创建该会话的玩家名 */
	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly)
	FString OwningPlayerName;

	/* 当前会话内人数 */
	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentPlayers = 0;

	/* 会话最大人数 */
	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly)
	int32 MaxPlayers = 0;

	/* 该会话的设置 */
	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USessionSettingViewModel> SessionSettings;

private:
	FOnlineSessionSearchResult Result;
};
