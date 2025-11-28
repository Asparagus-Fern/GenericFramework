// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyProxy.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "NetworkType.generated.h"

GENERICNETWORKFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogNetwork, Log, All);

/**
 * 
 */
USTRUCT(BlueprintType)
struct GENERICNETWORKFRAMEWORK_API FUniqueNetworkID
{
	GENERATED_BODY()

public:
	FUniqueNetworkID();
	FUniqueNetworkID(const APlayerController* InPlayer);
	FUniqueNetworkID(const APlayerState* InPlayerState);
	FUniqueNetworkID(const FUniqueNetIdRepl& InUniqueNetIDRepl);
	bool operator==(const FUniqueNetworkID& Other) const { return UniqueID == Other.UniqueID; }
	bool operator!=(const FUniqueNetworkID& Other) const { return !(*this == Other); }

	bool CheckIsValid() const { return !UniqueID.IsEmpty() && UniqueNetIdRepl.IsValid(); }
	FUniqueNetIdPtr GetUniqueNetIDPtr() const { return UniqueNetIdRepl.GetUniqueNetId(); }
	const FUniqueNetId& GetUniqueNetID() const { return *UniqueNetIdRepl.GetUniqueNetId(); }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString UniqueID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FUniqueNetIdRepl UniqueNetIdRepl;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct GENERICNETWORKFRAMEWORK_API FGenericSessionHandle
{
	GENERATED_BODY()

public:
	FGenericSessionHandle()
	{
	}

	FGenericSessionHandle(const FUniqueNetworkID& InUniqueNetID, const FName InSessionName, const FOnlineSessionSettings& InSessionSettings)
	{
		UniqueNetworkID = InUniqueNetID;
		SessionName = InSessionName;
		SessionSettings = InSessionSettings;
	}

	bool operator==(const FGenericSessionHandle& Other) const { return SessionName == Other.SessionName; }
	bool operator==(const FName OtherSessionName) const { return SessionName == OtherSessionName; }
	bool operator!=(const FGenericSessionHandle& Other) const { return !(*this == Other); }
	bool operator!=(const FName OtherSessionName) const { return !(*this == OtherSessionName); }

	bool CheckIsValid() const { return UniqueNetworkID.CheckIsValid() && SessionName != NAME_None; }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FUniqueNetworkID UniqueNetworkID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName SessionName = NAME_None;

	FOnlineSessionSettings SessionSettings;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct GENERICNETWORKFRAMEWORK_API FGenericSessionSettings
{
	GENERATED_BODY()

public:
	FGenericSessionSettings();
	FGenericSessionSettings(const FOnlineSessionSettings& InSettings);

	const FOnlineSessionSettings& GetSessionSettings() const;
	void SetSessionSettings(const FOnlineSessionSettings& InSettings);

	void EncodeSessionSettings();
	void DecodeSessionSettings();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsAutoStart = true;

public:
	/* 公有连接数量 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 NumPublicConnections = 4;

	/* 私有连接(通过邀请/密码连接)数量 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 NumPrivateConnections = 4;

	/* 是否允许玩家通过搜索发现此会话 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bShouldAdvertise = true;

	/* 是否允许中途加入 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAllowJoinInProgress = true;

	/* 是否使用局域网 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsLANMatch = false;

	/* 是否由专用服务器托管会话 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsDedicated = false;

	/* 是否使用统计信息 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bUsesStats = true;

	/* 是否允许邀请 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAllowInvites = true;

	/* 是否使用在线状态功能 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bUsesPresence = true;

	/* 是否允许玩家通过在线状态发现并加入会话 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAllowJoinViaPresence = true;

	/* 是否仅限好友之间通过在线状态发现并加入会话 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(EditCondition = "bAllowJoinViaPresence"))
	bool bAllowJoinViaPresenceFriendsOnly = false;

	/* 是否使用反作弊保护 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAntiCheatProtected = true;

	/* 是否使用游戏大厅 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bUseLobbiesIfAvailable = true;

	/* 是否自动加入语音 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bUseLobbiesVoiceChatIfAvailable = false;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString MapName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString SessionName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 NumRobots = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 PlayerNeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString SessionKey;

private:
	FOnlineSessionSettings SessionSettings;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct GENERICNETWORKFRAMEWORK_API FGenericSessionSearchSettings
{
	GENERATED_BODY()

public:
	FGenericSessionSearchSettings();
	FGenericSessionSearchSettings(const TSharedRef<FOnlineSessionSearch>& InSettings);

	TSharedRef<FOnlineSessionSearch> GetSessionSearchSettings() const;
	void SetSessionSearchSettings(const TSharedRef<FOnlineSessionSearch>& InSettings);

	void EncodeSessionSearchSettings();
	void DecodeSessionSearchSettings();

public:
	/* 最大查询结果数量 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxSearchResults = 10;

	/* 查询是否用于局域网匹配。如果为true，则搜索局域网内的会话；如果为false，则搜索在线会话。 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsLanQuery = false;

	/* 等待搜索结果的超时时间（以秒为单位） */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeoutInSeconds = 60.f;

public:
	/* 只搜索专用服务器 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bDedicatedOnly = false;

	/* 只搜索空服务器 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bEmptyServerOnly = false;

	/* 只搜索非空服务器 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bNotEmptyServerOnly = false;

	/* 搜索会话的用户ID */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString SearchUserName;

	/* 会话搜索中匹配的关键字 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString SearchKeywords;

private:
	TSharedPtr<FOnlineSessionSearch> SessionSearchSettings = nullptr;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct GENERICNETWORKFRAMEWORK_API FGenericSessionSearchResult
{
	GENERATED_BODY()

public:
	FGenericSessionSearchResult();
	FGenericSessionSearchResult(const FOnlineSessionSearchResult& InResult);

	const FOnlineSessionSearchResult& GetSessionSearchResult() const;
	void SetSessionSearchResult(const FOnlineSessionSearchResult& InResult);

	FName GetSessionName() const;

public:
	/* Ping */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PingInMs = 0;

	/* 创建该会话的玩家ID */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FUniqueNetIdRepl OwnerPlayerID;

	/* 创建该会话的玩家名 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString OwningPlayerName;

	/* 当前会话内人数 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentPlayers = 0;

	/* 会话最大人数 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxPlayers = 0;

	/* 该会话的设置 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGenericSessionSettings SessionSettings;

private:
	FOnlineSessionSearchResult SessionSearchResult;
};


/**
 * 
 */
UENUM(BlueprintType)
enum class EJoinSessionResult : uint8
{
	/** The join worked as expected */
	Success,
	/** There are no open slots to join */
	SessionIsFull,
	/** The session couldn't be found on the service */
	SessionDoesNotExist,
	/** There was an error getting the session server's address */
	CouldNotRetrieveAddress,
	/** The user attempting to join is already a member of the session */
	AlreadyInSession,
	/** An error not covered above occurred */
	UnknownError
};

inline EOnJoinSessionCompleteResult::Type ConvertToJoinSessionResult(const EJoinSessionResult EnumBP)
{
	switch (EnumBP)
	{
	case EJoinSessionResult::Success:
		return EOnJoinSessionCompleteResult::Success;
	case EJoinSessionResult::SessionIsFull:
		return EOnJoinSessionCompleteResult::SessionIsFull;
	case EJoinSessionResult::SessionDoesNotExist:
		return EOnJoinSessionCompleteResult::SessionDoesNotExist;
	case EJoinSessionResult::CouldNotRetrieveAddress:
		return EOnJoinSessionCompleteResult::CouldNotRetrieveAddress;
	case EJoinSessionResult::AlreadyInSession:
		return EOnJoinSessionCompleteResult::AlreadyInSession;
	case EJoinSessionResult::UnknownError:
		return EOnJoinSessionCompleteResult::UnknownError;
	}
	return EOnJoinSessionCompleteResult::UnknownError;
}

inline EJoinSessionResult ConvertToJoinSessionResultBP(EOnJoinSessionCompleteResult::Type Enum)
{
	switch (Enum)
	{
	case EOnJoinSessionCompleteResult::Success:
		return EJoinSessionResult::Success;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		return EJoinSessionResult::SessionIsFull;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		return EJoinSessionResult::SessionDoesNotExist;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		return EJoinSessionResult::CouldNotRetrieveAddress;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		return EJoinSessionResult::AlreadyInSession;
	case EOnJoinSessionCompleteResult::UnknownError:
		return EJoinSessionResult::UnknownError;
	}
	return EJoinSessionResult::UnknownError;
}
