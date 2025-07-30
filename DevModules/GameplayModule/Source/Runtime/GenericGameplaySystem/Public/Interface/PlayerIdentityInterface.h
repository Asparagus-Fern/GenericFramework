// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerIdentityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPlayerIdentityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GENERICGAMEPLAYSYSTEM_API IPlayerIdentityInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerIdentity() = 0;
	virtual const FUniqueNetIdRepl& GetPlayerUniqueIdentity() = 0;
};
