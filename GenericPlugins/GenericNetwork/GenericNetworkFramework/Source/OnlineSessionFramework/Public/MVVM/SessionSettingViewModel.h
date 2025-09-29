// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "SessionSettingViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ONLINESESSIONFRAMEWORK_API USessionSettingViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	/* 公开连接的最大数量 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 NumPublicConnections = 8;

	/* 私有连接的最大数量。私有连接通常用于邀请，不会在公开搜索中显示。 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	int32 NumPrivateConnections = 8;

	/*
	 * 如果为 true：会话将被公开，其他玩家可以搜索到该会话。
	 * 如果为 false：会话不会出现在搜索结果中，只能通过邀请加入。
	 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bShouldAdvertise = true;

	/* 是否允许玩家在游戏进行中加入会话 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bAllowJoinInProgress = true;

	/*
	 * 如果为 true：表示这是一个局域网（LAN）游戏，不会使用在线服务。
	 * 如果为 false：使用在线子系统。
	 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bIsLANMatch = false;

	/* 是否为专用服务器会话 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bIsDedicated = false;

	/* 是否使用在线统计 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bUsesStats = false;

	/* 是否允许邀请其他玩家加入会话 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bAllowInvites = true;

	/* 是否使用在线状态 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bUsesPresence = true;

	/* 是否允许通过在线状态加入。如果启用，玩家可以通过好友列表加入会话。 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "bUsesPresence"))
	bool bAllowJoinViaPresence = true;

	/* 是否只允许好友通过在线状态加入 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "bUsesPresence"))
	bool bAllowJoinViaPresenceFriendsOnly = true;

	/* 是否受反作弊保护 */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bAntiCheatProtected = false;
};
