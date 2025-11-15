// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	bool operator==(const FUniqueNetworkID& Other) const { return UniqueID == Other.UniqueID; }
	bool operator!=(const FUniqueNetworkID& Other) const { return !(*this == Other); }

	bool CheckIsValid() const { return !UniqueID.IsEmpty() && UniqueIdRepl.IsValid(); }
	FUniqueNetIdPtr GetUniqueNetIDPtr() const { return UniqueIdRepl.GetUniqueNetId(); }
	const FUniqueNetId& GetUniqueNetID() const { return *UniqueIdRepl.GetUniqueNetId(); }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString UniqueID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FUniqueNetIdRepl UniqueIdRepl;
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

