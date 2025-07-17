// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamAssignPolicy.h"
#include "TeamState.h"
#include "TeamType.h"
#include "GameState/GenericGameState.h"
#include "TeamGameState.generated.h"

class UTeamAssignPolicy;
class ATeamGameMode;
class ATeamState;

/**
 * 
 */
UCLASS()
class TEAMASSIGNSYSTEM_API ATeamGameState : public AGenericGameState
{
	GENERATED_BODY()

	friend ATeamGameMode;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION(Server, Reliable)
	void Server_LoginPlayer(APlayerState* InPlayerState);

	UFUNCTION(Server, Reliable)
	void Server_LogoutPlayer(APlayerState* InPlayerState);

public:
	UFUNCTION(BlueprintPure)
	const TArray<FPlayerTeam>& GetPlayerTeams();

	UFUNCTION(BlueprintPure)
	bool GetPlayerTeamByID(int32 InTeamID, FPlayerTeam& OutPlayerTeam);

	UFUNCTION(BlueprintPure)
	bool GetPlayerTeamByTeamState(ATeamState* InTeamState, FPlayerTeam& OutPlayerTeam);

	UFUNCTION(BlueprintPure)
	bool GetPlayerTeamByPlayerState(APlayerState* InPlayerState, FPlayerTeam& OutPlayerTeam);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTeamAssignPolicy> TeamAssignPolicyClass = UTeamAssignPolicy::StaticClass();

	UPROPERTY(Transient)
	TObjectPtr<UTeamAssignPolicy> TeamAssignPolicy = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ATeamState> TeamStateClass = ATeamState::StaticClass();

	UPROPERTY(Transient, Replicated)
	TArray<FPlayerTeam> PlayerTeams;

private:
	UFUNCTION()
	virtual void OnTeamAssignFinish();
};
