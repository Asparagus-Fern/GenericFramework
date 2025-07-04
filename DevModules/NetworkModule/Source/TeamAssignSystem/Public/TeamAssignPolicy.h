// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamType.h"
#include "Generic/GenericObject.h"
#include "TeamAssignPolicy.generated.h"

class ATeamPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamPlayerAdded, APlayerState*, PlayerState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamPlayerRemoved, APlayerState*, PlayerState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTeamAssignFinish);


/**
 * 队伍的分配策略
 */
UCLASS()
class TEAMASSIGNSYSTEM_API UTeamAssignPolicy : public UGenericObject
{
	GENERATED_BODY()

public:
	virtual void InitAssignPolicy();
	void LoginPlayer(ATeamPlayerState* InPlayerState);
	void LogoutPlayer(ATeamPlayerState* InPlayerState);

public:
	UFUNCTION(BlueprintPure)
	TArray<FPlayerTeam>& GetPlayerTeams();

protected:
	virtual bool HasPlayer(APlayerState* InPlayerState) const;
	virtual bool CanCreateNewTeam();
	virtual FPlayerTeam CreateNewTeam();
	virtual bool CanPlayerJoinTeam(const FPlayerTeam& InTeam);
	virtual FPlayerTeam& GetTeamPlayerJoin(ATeamPlayerState* InPlayerState);
	virtual bool IsTeamFull();
	virtual void FinishAssignTeam();

public:
	UPROPERTY(BlueprintAssignable)
	FOnTeamPlayerAdded OnTeamPlayerAddedEvent;

	UPROPERTY(BlueprintAssignable)
	FOnTeamPlayerRemoved OnTeamPlayerRemovedEvent;

	UPROPERTY(BlueprintAssignable)
	FOnTeamAssignFinish OnTeamAssignFinishEvent;

protected:
	/* 在队伍满员时自动结束队伍分配 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAutoFinishAssignTeam = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETeamAssignMethod TeamAssignMethod = ETeamAssignMethod::Dynamic;

	/* 队伍数量，仅在 TeamAssignMethod = ETeamAssignMethod::Static 时启用 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(UIMin = 1, ClampMin = 1, EditConditionHides, EditCondition = "TeamAssignMethod == ETeamAssignMethod::Static"))
	int32 TeamCount = 2;

	/* 队伍的最大数量，仅在 TeamAssignMethod = ETeamAssignMethod::Dynamic 时启用 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(UIMin = 1, ClampMin = 1, EditConditionHides, EditCondition = "TeamAssignMethod == ETeamAssignMethod::Dynamic"))
	int32 MaxTeamCount = 2;

	/* 每个队伍的最大玩家数量 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(UIMin = 1, ClampMin = 1))
	int32 MaxTeamPlayerCount = 2;

private:
	UPROPERTY(Transient)
	TArray<APlayerState*> PlayerStates;

	UPROPERTY(Transient)
	TArray<FPlayerTeam> PlayerTeams;
};
