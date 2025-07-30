// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamAssignPolicy.h"
#include "TeamState.h"
#include "TeamType.h"
#include "GameState/GenericGameState.h"
#include "TeamGameState.generated.h"

class ATeamAssignPolicy;
class ATeamGameMode;
class ATeamState;
class UTeamAssignInfo;


/**
 * 
 */
UCLASS()
class TEAMASSIGNSYSTEM_API ATeamGameState : public AGenericGameState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void CreateTeamAssignPolicy();
	void DestroyTeamAssignPolicy();

	void LoginPlayer(APlayerController* InPlayer);
	void LogoutPlayer(APlayerController* InPlayer);
	
	UFUNCTION(Server, Reliable)
	void Server_LoginPlayer(APlayerController* InPlayer);

	UFUNCTION(Server, Reliable)
	void Server_LogoutPlayer(APlayerController* InPlayer);

	void OnTeamComponentRegister(UTeamAssignComponent* InComponent);
	void OnTeamComponentUnRegister(UTeamAssignComponent* InComponent);

	UFUNCTION()
	virtual void OnTeamAssignFinish(TArray<UTeamAssignInfo*> InPlayerTeams);

public:
	const TArray<UTeamAssignInfo*>& GetPlayerTeams();

	UTeamAssignInfo* GetPlayerTeam(int32 InTeamID);
	UTeamAssignInfo* GetPlayerTeam(ATeamState* InTeamState);
	UTeamAssignInfo* GetPlayerTeam(const APawn* InPawn);
	UTeamAssignInfo* GetPlayerTeam(const APlayerController* InPlayerController);
	UTeamAssignInfo* GetPlayerTeam(const APlayerState* InPlayerState);
	UTeamAssignInfo* GetPlayerTeam(const UTeamAssignComponent* InTeamComponent);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ReAssignTeam();

private:
	void AddTeamComponent(UTeamAssignComponent* InTeamComponent);
	void UpdateTeamComponent(UTeamAssignComponent* InTeamComponent);
	void RemoveTeamComponent(UTeamAssignComponent* InTeamComponent);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATeamAssignPolicy> TeamAssignPolicyClass = ATeamAssignPolicy::StaticClass();

	UPROPERTY(Transient)
	TObjectPtr<ATeamAssignPolicy> TeamAssignPolicy = nullptr;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UTeamAssignInfo>> PlayerTeamInfos;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UTeamAssignComponent>> TeamAssignComponents;
};
