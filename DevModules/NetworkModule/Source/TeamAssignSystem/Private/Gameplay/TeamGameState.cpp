// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Gameplay/TeamGameState.h"

#include "TeamAssignPolicy.h"
#include "TeamAssignComponent.h"
#include "TeamAssignInfo.h"
#include "Debug/DebugType.h"
#include "GameFramework/PlayerState.h"
#include "Gameplay/TeamGameMode.h"
#include "Kismet/GameplayStatics.h"

void ATeamGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		CreateTeamAssignPolicy();

		AGenericGameMode::GetOnPlayerLogin().AddUObject(this, &ATeamGameState::LoginPlayer);
		AGenericGameMode::GetOnPlayerLogout().AddUObject(this, &ATeamGameState::LogoutPlayer);

		UTeamAssignComponent::OnTeamComponentRegisterEvent.AddUObject(this, &ATeamGameState::OnTeamComponentRegister);
		UTeamAssignComponent::OnTeamComponentUnRegisterEvent.AddUObject(this, &ATeamGameState::OnTeamComponentUnRegister);
	}
}

void ATeamGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (HasAuthority())
	{
		DestroyTeamAssignPolicy();

		AGenericGameMode::GetOnPlayerLogin().RemoveAll(this);
		AGenericGameMode::GetOnPlayerLogout().RemoveAll(this);

		UTeamAssignComponent::OnTeamComponentRegisterEvent.RemoveAll(this);
		UTeamAssignComponent::OnTeamComponentUnRegisterEvent.RemoveAll(this);
	}
}

void ATeamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATeamGameState::CreateTeamAssignPolicy()
{
	if (!TeamAssignPolicy)
	{
		TeamAssignPolicy = GetWorld()->SpawnActor<ATeamAssignPolicy>(TeamAssignPolicyClass);
		TeamAssignPolicy->OnTeamAssignFinishEvent.AddUniqueDynamic(this, &ATeamGameState::OnTeamAssignFinish);
		TeamAssignPolicy->NativeOnCreate();
	}
}

void ATeamGameState::DestroyTeamAssignPolicy()
{
	if (TeamAssignPolicy)
	{
		TeamAssignPolicy->NativeOnDestroy();
		TeamAssignPolicy->OnTeamAssignFinishEvent.RemoveAll(this);
		TeamAssignPolicy->MarkAsGarbage();
		TeamAssignPolicy = nullptr;
	}
}

void ATeamGameState::LoginPlayer(APlayerController* InPlayer)
{
	Server_LoginPlayer(InPlayer);
}

void ATeamGameState::LogoutPlayer(APlayerController* InPlayer)
{
	Server_LogoutPlayer(InPlayer);
}

void ATeamGameState::Server_LoginPlayer_Implementation(APlayerController* InPlayer)
{
	if (!IsValid(InPlayer))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InPlayerState Is InValid"))
		return;
	}

	if (!TeamAssignPolicy)
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("TeamAssignPolicy Is InValid"))
		return;
	}

	TeamAssignPolicy->Server_AddPlayer(InPlayer);
}

void ATeamGameState::Server_LogoutPlayer_Implementation(APlayerController* InPlayer)
{
	if (!IsValid(InPlayer))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InPlayerState Is InValid"))
		return;
	}

	if (!TeamAssignPolicy)
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("TeamAssignPolicy Is InValid"))
		return;
	}

	if (!TeamAssignPolicy->IsPolicyValid())
	{
		return;
	}

	TeamAssignPolicy->Server_RemovePlayer(InPlayer);
}

void ATeamGameState::OnTeamComponentRegister(UTeamAssignComponent* InComponent)
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InComponent Is InValid"))
		return;
	}

	AddTeamComponent(InComponent);
}

void ATeamGameState::OnTeamComponentUnRegister(UTeamAssignComponent* InComponent)
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InComponent Is InValid"))
		return;
	}

	RemoveTeamComponent(InComponent);
}

void ATeamGameState::OnTeamAssignFinish(TArray<UTeamAssignInfo*> InPlayerTeams)
{
	PlayerTeamInfos = InPlayerTeams;

	for (auto& TeamComponent : TeamAssignComponents)
	{
		AddTeamComponent(TeamComponent);
	}

	TeamAssignComponents.Reset();
}

const TArray<UTeamAssignInfo*>& ATeamGameState::GetPlayerTeams()
{
	return PlayerTeamInfos;
}

UTeamAssignInfo* ATeamGameState::GetPlayerTeam(int32 InTeamID)
{
	TObjectPtr<UTeamAssignInfo>* PlayerTeam = PlayerTeamInfos.FindByPredicate([InTeamID](const TObjectPtr<UTeamAssignInfo>& PlayerTeam)
		{
			return PlayerTeam->TeamID == InTeamID;
		}
	);

	if (PlayerTeam)
	{
		return *PlayerTeam;
	}

	return nullptr;
}

UTeamAssignInfo* ATeamGameState::GetPlayerTeam(ATeamState* InTeamState)
{
	TObjectPtr<UTeamAssignInfo>* PlayerTeam = PlayerTeamInfos.FindByPredicate([InTeamState](const TObjectPtr<UTeamAssignInfo>& PlayerTeam)
		{
			return PlayerTeam->TeamState == InTeamState;
		}
	);

	if (PlayerTeam)
	{
		return *PlayerTeam;
	}

	return nullptr;
}

UTeamAssignInfo* ATeamGameState::GetPlayerTeam(const APawn* InPawn)
{
	return GetPlayerTeam(InPawn->GetPlayerState());
}

UTeamAssignInfo* ATeamGameState::GetPlayerTeam(const APlayerController* InPlayerController)
{
	TObjectPtr<UTeamAssignInfo>* PlayerTeam = PlayerTeamInfos.FindByPredicate([InPlayerController](const TObjectPtr<UTeamAssignInfo>& PlayerTeam)
		{
			return PlayerTeam->PlayerList.Contains(InPlayerController);
		}
	);

	if (PlayerTeam)
	{
		return *PlayerTeam;
	}

	return nullptr;
}

UTeamAssignInfo* ATeamGameState::GetPlayerTeam(const APlayerState* InPlayerState)
{
	return GetPlayerTeam(InPlayerState->GetPlayerController());
}

UTeamAssignInfo* ATeamGameState::GetPlayerTeam(const UTeamAssignComponent* InTeamComponent)
{
	if (ATeamState* TS = Cast<ATeamState>(InTeamComponent->GetOwner()))
	{
		return GetPlayerTeam(TS);
	}
	else if (APawn* Pawn = Cast<APawn>(InTeamComponent->GetOwner()))
	{
		return GetPlayerTeam(Pawn);
	}
	else if (APlayerController* PC = Cast<APlayerController>(InTeamComponent->GetOwner()))
	{
		return GetPlayerTeam(PC);
	}
	else if (APlayerState* OwnerPS = Cast<APlayerState>(InTeamComponent->GetOwner()))
	{
		return GetPlayerTeam(OwnerPS);
	}
	else if (APlayerState* LocalPS = UGameplayStatics::GetPlayerState(this, InTeamComponent->LocalPlayerIndex))
	{
		return GetPlayerTeam(LocalPS);
	}

	return nullptr;
}

void ATeamGameState::Server_ReAssignTeam_Implementation()
{
	/*PlayerTeamInfos.Reset();
	
	if (TeamAssignPolicy)
	{
		if (TeamAssignPolicy.GetClass() != TeamAssignPolicyClass)
		{
			const TArray<APlayerState*>& PLayerStates = TeamAssignPolicy->GetAllPlayer();
	
			DestroyTeamAssignPolicy();
			CreateTeamAssignPolicy();
	
			for (auto& PLayerState : PLayerStates)
			{
				TeamAssignPolicy->AddPlayer(PLayerState);
			}
		}
		else
		{
			TeamAssignPolicy->ReAssignPlayer();
		}
	}*/
}

void ATeamGameState::AddTeamComponent(UTeamAssignComponent* InTeamComponent)
{
	if (!HasAuthority())
	{
		return;
	}

	if (!TeamAssignPolicy->GetIsTeamAssignFinish())
	{
		TeamAssignComponents.Add(InTeamComponent);
	}
	else
	{
		if (UTeamAssignInfo* Team = GetPlayerTeam(InTeamComponent))
		{
			if (!Team->TeamComponents.Contains(InTeamComponent))
			{
				Team->TeamComponents.Add(InTeamComponent);
			}

			UpdateTeamComponent(InTeamComponent);
		}
	}
}

void ATeamGameState::UpdateTeamComponent(UTeamAssignComponent* InTeamComponent)
{
	if (!HasAuthority())
	{
		return;
	}

	if (UTeamAssignInfo* Team = GetPlayerTeam(InTeamComponent))
	{
		InTeamComponent->Server_SetTeamID(Team->TeamID);
	}
}

void ATeamGameState::RemoveTeamComponent(UTeamAssignComponent* InTeamComponent)
{
	if (!HasAuthority())
	{
		return;
	}

	if (!TeamAssignPolicy->GetIsTeamAssignFinish())
	{
		TeamAssignComponents.Remove(InTeamComponent);
	}
	else
	{
		if (UTeamAssignInfo* Team = GetPlayerTeam(InTeamComponent))
		{
			if (Team->TeamComponents.Contains(InTeamComponent))
			{
				Team->TeamComponents.Remove(InTeamComponent);
			}
		}
	}
}
