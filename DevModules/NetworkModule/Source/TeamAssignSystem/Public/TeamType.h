// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamType.generated.h"

class ATeamState;
class ATeamPlayerState;

UENUM(BlueprintType)
enum class ETeamAssignMethod :uint8
{
	Static,
	Dynamic
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerTeam
{
	GENERATED_BODY()

public:
	FPlayerTeam();
	FPlayerTeam(int32 InTeamID);
	FPlayerTeam(ATeamPlayerState* InPlayerState);
	FPlayerTeam(int32 InTeamID, ATeamPlayerState* InPlayerState);

	bool operator==(const FPlayerTeam& Other) const { return TeamID == Other.TeamID; }
	bool operator==(const int32& Other) const { return TeamID == Other; }
	bool operator!=(const FPlayerTeam& Other) const { return !(*this == Other); }
	bool operator!=(const int32& Other) const { return !(*this == Other); }

	bool IsValid() const { return TeamID != INDEX_NONE; }

public:
	UPROPERTY(BlueprintReadOnly)
	int32 TeamID = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<ATeamState> TeamState = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<ATeamPlayerState>> PlayerStates;
};
