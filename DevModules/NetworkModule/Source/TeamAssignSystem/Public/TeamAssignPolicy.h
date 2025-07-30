// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamType.h"
#include "Interface/StateInterface.h"
#include "TeamAssignPolicy.generated.h"

class UTeamAssignViewModel;
class UTeamAssignPanel;
class UTeamAssignInfo;
class ATeamPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamPlayerAdded, APlayerState*, PlayerState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamPlayerRemoved, APlayerState*, PlayerState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamAssignFinish, TArray<UTeamAssignInfo*>, PlayerTeams);


/**
 * 队伍的分配策略
 */
UCLASS()
class TEAMASSIGNSYSTEM_API ATeamAssignPolicy : public AActor, public IStateInterface
{
	GENERATED_BODY()

public:
	ATeamAssignPolicy(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	/* IStateInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* UTeamAssignPolicy */
public:
	bool IsPolicyValid() const;

	UFUNCTION(Server, Reliable)
	void Server_AddPlayer(APlayerController* InPlayer);

	UFUNCTION(Server, Reliable)
	void Server_RemovePlayer(APlayerController* InPlayer);

	TArray<APlayerController*> GetAllPlayer() const;
	TArray<APlayerController*> GetPlayers(ETeamAssignState InState);
	TArray<UTeamAssignInfo*> GetPlayerTeams();
	bool GetIsTeamAssignFinish() const;

private:
	UFUNCTION(Server, Reliable)
	void Server_CreateNewTeamAssignInfos();

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerAssignState(APlayerController* InPlayer, ETeamAssignState InState);

protected:
	virtual UTeamAssignInfo* CreateNewTeam();
	virtual bool EvaluatePlayerValid(APlayerController* InPlayer);
	virtual void OnPlayerAssignStateChanged(APlayerController* InPlayer, ETeamAssignState NewState);

public:
	UPROPERTY(BlueprintAssignable)
	FOnTeamAssignFinish OnTeamAssignFinishEvent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ATeamState> TeamStateClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UTeamAssignViewModel> TeamAssignViewModelClass = nullptr;

	UPROPERTY(Transient, Replicated)
	TObjectPtr<UTeamAssignViewModel> TeamAssignViewModel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bEnableTeamAssignPanel = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition = "bEnableTeamAssignPanel"))
	TSubclassOf<UTeamAssignPanel> TeamAssignPanelClass = nullptr;

private:
	UPROPERTY(Transient)
	TMap<APlayerController*, ETeamAssignState> Players;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UTeamAssignInfo>> PlayerTeams;

	bool bIsTeamAssignFinish = false;
};
