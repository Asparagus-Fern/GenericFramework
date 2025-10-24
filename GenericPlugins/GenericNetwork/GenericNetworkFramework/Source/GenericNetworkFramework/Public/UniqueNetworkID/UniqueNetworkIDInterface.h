// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "UniqueNetworkIDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUniqueNetworkIDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GENERICNETWORKFRAMEWORK_API IUniqueNetworkIDInterface
{
	GENERATED_BODY()

public:
	virtual APlayerState* GetPlayerState() = 0;
	virtual const FUniqueNetworkID& GetUniqueNetworkID() = 0;
	virtual void SetUniqueNetworkID(const FUniqueNetworkID& InUniqueNetworkID) = 0;
};
