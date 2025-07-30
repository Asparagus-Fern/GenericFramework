// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamType.generated.h"

class ATeamState;
class ATeamPlayerState;

UENUM(BlueprintType)
enum class ETeamAssignState :uint8
{
	NotAssigned,
	Assigned,
	Ready
};

UENUM(BlueprintType)
enum class ETeamColor :uint8
{
	Black,
	White,
	Red,
	Blue,
	Yellow,
	Green,
};
