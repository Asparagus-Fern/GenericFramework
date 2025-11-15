// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineSessionSettings.h"
#include "SessionSettingViewModel.generated.h"

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSettingViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	const FOnlineSessionSettings& GetSessionSettings();
	void SetSessionSettings(const FOnlineSessionSettings& InSettings);
	
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

public:
	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly, Category="Advance")
	FString MapName;

	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly, Category="Advance")
	FString SessionName;

	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly, Category="Advance")
	int32 NumRobots = 0;

	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly, Category="Advance")
	int32 PlayerNeed = 0;

	UPROPERTY(FieldNotify, VisibleAnywhere, BlueprintReadOnly, Category="Advance")
	FString SessionKey;

private:
	FOnlineSessionSettings Settings;
};
