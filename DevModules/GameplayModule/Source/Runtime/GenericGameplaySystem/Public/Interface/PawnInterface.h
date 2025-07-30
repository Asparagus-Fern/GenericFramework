// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnInterface.generated.h"

class AAIController;

// This class does not need to be modified.
UINTERFACE()
class UPawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GENERICGAMEPLAYSYSTEM_API IPawnInterface
{
	GENERATED_BODY()

public:
	virtual bool IsPlayer() { return false; }
	virtual bool IsAI() { return false; }
	virtual APlayerController* GetPlayerController() { return nullptr; }
	virtual AAIController* GetAIController() { return nullptr; }
};
