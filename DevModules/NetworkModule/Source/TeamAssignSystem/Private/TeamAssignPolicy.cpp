// Copyright ChenTaiye 2025. All Rights Reserved.

#include "TeamAssignPolicy.h"

#include "GenericWidgetManager.h"
#include "TeamAssignInfo.h"
#include "TeamState.h"
#include "Interface/TeamAssignInterface.h"
#include "Net/UnrealNetwork.h"
#include "UMG/TeamAssignPanel.h"
#include "UMG/MVVM/TeamAssignViewModel.h"

ATeamAssignPolicy::ATeamAssignPolicy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetReplicates(true);
	TeamStateClass = ATeamState::StaticClass();
	TeamAssignViewModelClass = UTeamAssignViewModel::StaticClass();
}

void ATeamAssignPolicy::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (TeamAssignViewModelClass)
		{
			TeamAssignViewModel = NewObject<UTeamAssignViewModel>(this, TeamAssignViewModelClass);
		}
	}
}

void ATeamAssignPolicy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ATeamAssignPolicy::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	SharedParams.RepNotifyCondition = REPNOTIFY_Always;

	DOREPLIFETIME_WITH_PARAMS_FAST(ATeamAssignPolicy, TeamAssignViewModel, SharedParams);
}

void ATeamAssignPolicy::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();
	Server_CreateNewTeamAssignInfos();

	// if (bEnableTeamAssignPanel && TeamAssignPanelClass)
	// {
	// 	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	// 	{
	// 		TeamAssignPanel = GenericWidgetManager->OpenUserWidget<UTeamAssignPanel>(TeamAssignPanelClass);
	// 	}
	// }
}

void ATeamAssignPolicy::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();

	// if (TeamAssignPanel)
	// {
	// 	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	// 	{
	// 		GenericWidgetManager->CloseUserWidget(TeamAssignPanel);
	// 	}
	//
	// 	TeamAssignPanel = nullptr;
	// }

	Players.Reset();
	PlayerTeams.Reset();
}

bool ATeamAssignPolicy::IsPolicyValid() const
{
	return TeamStateClass && TeamAssignViewModelClass;
}

void ATeamAssignPolicy::Server_AddPlayer_Implementation(APlayerController* InPlayer)
{
	if (!IsPolicyValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Policy Must Has Valid TeamStateClass And Valid TeamAssignViewModel"))
		return;
	}

	if (!IsValid(InPlayer) || !EvaluatePlayerValid(InPlayer))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Player Is InValid"))
		return;
	}

	if (Players.Contains(InPlayer))
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("Player Is Already In Team"))
		return;
	}

	Server_SetPlayerAssignState(InPlayer, ETeamAssignState::NotAssigned);

	/*if (!bEnableMidwayPlayerLogin && bIsMidway)
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("Disable Midway Player"))
		OnPlayerAssign(InPlayerState, ETeamAssignResult::DisableMidwayPlayer);
		return;
	}

	if (HasPlayer(InPlayerState))
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("InPlayerState Is Already In Team"))
		OnPlayerAssign(InPlayerState, ETeamAssignResult::AssignedPlayer);
		return;
	}

	if (CanPlayerJoinTeam(PlayerTeams, InPlayerState))
	{
		if (UTeamAssignInfo* JoinTeam = GetTeamPlayerJoin(InPlayerState))
		{
			PlayerStates.Add(InPlayerState);
			JoinTeam->PlayerStates.Add(InPlayerState);
	
			OnPlayerAssign(InPlayerState, ETeamAssignResult::Success);
			OnTeamPlayerAddedEvent.Broadcast(InPlayerState);
		}
	}
	else
	{
		OnPlayerAssign(InPlayerState, ETeamAssignResult::JoinTeamFail);
	}
	
	if (IsAllTeamFull() && bAutoFinishAssignTeam)
	{
		FinishAssignTeam();
	}*/
}

void ATeamAssignPolicy::Server_RemovePlayer_Implementation(APlayerController* InPlayer)
{
	if (!IsPolicyValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Policy Must Has Valid TeamStateClass And Valid TeamAssignViewModel"))
		return;
	}

	if (!IsValid(InPlayer))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InPlayerState Is InValid"))
		return;
	}

	/*if (!HasPlayer(InPlayerState))
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("InPlayerState Is Not In Team"))
		return;
	}

	for (auto& PlayerTeam : PlayerTeams)
	{
		if (PlayerTeam->PlayerStates.Contains(InPlayerState))
		{
			PlayerTeam->PlayerStates.Remove(InPlayerState);
		}
	}

	OnTeamPlayerRemovedEvent.Broadcast(InPlayerState);
	PlayerStates.Remove(InPlayerState);*/
}

TArray<APlayerController*> ATeamAssignPolicy::GetAllPlayer() const
{
	TArray<APlayerController*> AllPlayers;
	Players.GenerateKeyArray(AllPlayers);
	return AllPlayers;
}

TArray<APlayerController*> ATeamAssignPolicy::GetPlayers(const ETeamAssignState InState)
{
	TArray<APlayerController*> AllPlayers;

	for (auto& Player : Players)
	{
		if (Player.Value == InState)
		{
			AllPlayers.Add(Player.Key);
		}
	}

	return AllPlayers;
}

TArray<UTeamAssignInfo*> ATeamAssignPolicy::GetPlayerTeams()
{
	return PlayerTeams;
}

bool ATeamAssignPolicy::GetIsTeamAssignFinish() const
{
	return bIsTeamAssignFinish;
}

void ATeamAssignPolicy::Server_CreateNewTeamAssignInfos_Implementation()
{
	PlayerTeams.Reset();

	// if (TeamAssignViewModel)
	// {
	// 	for (int i = 0; i < TeamAssignViewModel->GetTeamCount(); ++i)
	// 	{
	// 		PlayerTeams.Add(CreateNewTeam());
	// 	}
	// }
}

void ATeamAssignPolicy::Server_SetPlayerAssignState_Implementation(APlayerController* InPlayer, ETeamAssignState InState)
{
	ETeamAssignState& State = Players.FindOrAdd(InPlayer, InState);

	if (InState == ETeamAssignState::NotAssigned)
	{
		if (GetIsTeamAssignFinish())
		{
		}
		else
		{
			if (InPlayer->GetClass()->ImplementsInterface(UTeamAssignInterface::StaticClass()))
			{
				ITeamAssignInterface::Execute_CreatePlayerAssignPanel(InPlayer, TeamAssignPanelClass);

				for (auto& Player : Players)
				{
					ITeamAssignInterface::Execute_UpdatePlayerAssignState(InPlayer, Player.Key, Player.Value);
				}
			}
		}
	}
	else if (InState == ETeamAssignState::Assigned)
	{
	}
	else if (InState == ETeamAssignState::Ready)
	{
	}

	State = InState;
	OnPlayerAssignStateChanged(InPlayer, InState);
}

void ATeamAssignPolicy::OnPlayerAssignStateChanged(APlayerController* InPlayer, ETeamAssignState NewState)
{
}

UTeamAssignInfo* ATeamAssignPolicy::CreateNewTeam()
{
	UTeamAssignInfo* NewPlayerTeam = NewObject<UTeamAssignInfo>(GetOuter());
	NewPlayerTeam->TeamID = PlayerTeams.IsEmpty() ? 0 : PlayerTeams.Last()->TeamID + 1;

	ATeamState* NewTeamState = GetWorld()->SpawnActor<ATeamState>(TeamStateClass);
	NewPlayerTeam->TeamState = NewTeamState;

	return NewPlayerTeam;
}

bool ATeamAssignPolicy::EvaluatePlayerValid(APlayerController* InPlayer)
{
	return true;
}

/*void UTeamAssignPolicy::ReAssignPlayer()
{
	TArray<APlayerState*> AllPlayerState = PlayerStates;
	CreateNewTeamAssignInfos();
	PlayerStates.Reset();

	for (auto& PlayerState : AllPlayerState)
	{
		AddPlayer(PlayerState);
	}
}*/

/*bool UTeamAssignPolicy::HasPlayer_Implementation(APlayerState* InPlayerState) const
{
	return PlayerStates.Contains(InPlayerState);
}

bool UTeamAssignPolicy::NeedCreateNewTeam_Implementation()
{
	if (PlayerTeams.IsEmpty())
	{
		return true;
	}

	if (PlayerTeams.Num() < MaxTeamCount && PlayerTeams.Last()->PlayerStates.Num() >= MaxTeamPlayerCount)
	{
		return true;
	}

	return false;
}

bool UTeamAssignPolicy::CanPlayerJoinTeam_Implementation(const TArray<UTeamAssignInfo*>& InPlayerTeams, APlayerState* InPlayerState)
{
	return !InPlayerTeams.IsEmpty() && InPlayerTeams.Last()->PlayerStates.Num() < MaxTeamPlayerCount;
}

UTeamAssignInfo* UTeamAssignPolicy::GetTeamPlayerJoin_Implementation(APlayerState* InPlayerState)
{
	if (PlayerTeams.IsEmpty())
	{
		PlayerTeams.Add(CreateNewTeam());
	}

	return PlayerTeams.Last();
}

bool UTeamAssignPolicy::IsAllTeamFull_Implementation()
{
	if (PlayerTeams.Num() < MaxTeamCount)
	{
		return false;
	}

	for (auto& PlayerTeam : PlayerTeams)
	{
		if (PlayerTeam->PlayerStates.Num() < MaxTeamPlayerCount)
		{
			return false;
		}
	}

	return true;
}

void UTeamAssignPolicy::OnPlayerAssign_Implementation(APlayerState* InPlayerState, ETeamAssignResult AssignResult)
{
}

void UTeamAssignPolicy::FinishAssignTeam()
{
	OnTeamAssignFinishEvent.Broadcast(PlayerTeams);
}*/
