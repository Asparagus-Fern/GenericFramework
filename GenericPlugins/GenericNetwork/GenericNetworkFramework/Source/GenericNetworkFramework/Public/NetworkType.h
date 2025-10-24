// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.generated.h"

GENERICNETWORKFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogNetwork, Log, All);

USTRUCT(BlueprintType)
struct GENERICNETWORKFRAMEWORK_API FUniqueNetworkID
{
	GENERATED_BODY()

public:
	FUniqueNetworkID();
	FUniqueNetworkID(const ULocalPlayer* InLocalPlayer);
	FUniqueNetworkID(const APlayerController* InPlayer);
	FUniqueNetworkID(const APlayerState* InPlayerState);
	bool operator==(const FUniqueNetworkID& Other) const { return UniqueID == Other.UniqueID; }
	bool operator!=(const FUniqueNetworkID& Other) const { return !(*this == Other); }

public:
	bool IsNetworkIDValid() const { return !UniqueID.IsEmpty() && UniqueIdRepl.IsValid(); }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString UniqueID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FUniqueNetIdRepl UniqueIdRepl;
};
