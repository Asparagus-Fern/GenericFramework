// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineSessionSettings.h"
#include "SessionSettingsViewModel.generated.h"

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSettingsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Initialize(const FOnlineSessionSettings& InSettings);
	const FOnlineSessionSettings& GetSessionSettings() const { return Settings; }

public:
	/* 公有连接数量 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	int32 NumPublicConnections = 4;

	/* 私有连接(通过邀请/密码连接)数量 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	int32 NumPrivateConnections = 4;

	/* 是否允许玩家通过搜索发现此会话 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bShouldAdvertise = false;

	/* 是否允许中途加入 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bAllowJoinInProgress = false;

	/* 是否使用局域网 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bIsLANMatch = false;

	/* 是否由专用服务器托管会话 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bIsDedicated = false;

	/* 是否使用统计信息 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bUsesStats = false;

	/* 是否允许邀请 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bAllowInvites = false;

	/* 是否使用在线状态功能 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bUsesPresence = false;

	/* 是否允许玩家通过在线状态发现并加入会话 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bAllowJoinViaPresence = false;

	/* 是否仅限好友之间通过在线状态发现并加入会话 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic", meta=(EditConditionHides, EditCondition = "bAllowJoinViaPresence"))
	bool bAllowJoinViaPresenceFriendsOnly = false;

	/* 是否使用反作弊保护 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bAntiCheatProtected = false;

	/* 是否使用游戏大厅 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bUseLobbiesIfAvailable = false;

	/* 是否自动加入语音 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	bool bUseLobbiesVoiceChatIfAvailable = false;

private:
	FOnlineSessionSettings Settings;
};
