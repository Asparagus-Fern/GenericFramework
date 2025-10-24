// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineSessionCreateSettingsViewModel.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UOnlineSessionCreateSettingsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	GENERICNETWORKFRAMEWORK_API virtual bool GetOnlineSessionCreateSettings(class FOnlineSessionSettings& Result);

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

	/* Manual override for the Session Id instead of having one assigned by the backend. Its size may be restricted depending on the platform */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Generic")
	FString SessionIdOverride;

public:
	/* 是否使用自定义的地图名 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced")
	bool bUseCustomMapName = false;

	/* 自定义的地图名 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced", meta=(InlineEditConditionToggle, EditCondition = "bUseCustomMapName"))
	FString MapNameOverride;

	/* 是否使用自定义的游戏模式描述 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced")
	bool bUseCustomGameModeDescription = false;

	/* 自定义游戏模式描述 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced", meta=(InlineEditConditionToggle, EditCondition = "bUseCustomGameModeDescription"))
	FString GameModeDescriptionOverride;

	/* 是否使用自定义的机器人数量 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced")
	bool bUseCustomNumBots = false;

	/* 会话中的机器人数量 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced", meta=(InlineEditConditionToggle, EditCondition = "bUseCustomNumBots", ClampMin = 0, UIMin =0))
	int32 NumBotsOverride = 0;

	/* 是否启用会话最少人数限制 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced")
	bool bUseNumPlayerNeeded = false;

	/* 会话所需的最少人数 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced", meta=(InlineEditConditionToggle, EditCondition = "bUseNumPlayerNeeded", ClampMin = 0, UIMin =0))
	int32 NumPlayerNeeded = 0;

	/* 是否启用会话秘钥 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced")
	bool bUseSessionKey = false;

	/* 会话秘钥 */
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite, Category="Advanced", meta=(InlineEditConditionToggle, EditCondition = "bUseSessionKey"))
	FString SessionKey;
};
