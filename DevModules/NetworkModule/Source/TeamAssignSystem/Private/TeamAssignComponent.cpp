// Copyright ChenTaiye 2025. All Rights Reserved.

#include "TeamAssignComponent.h"

#include "Gameplay/TeamGameState.h"
#include "Net/UnrealNetwork.h"

UTeamAssignComponent::UTeamAssignComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UTeamAssignComponent::BeginPlay()
{
	Super::BeginPlay();
	OnTeamComponentRegisterEvent.Broadcast(this);
}

void UTeamAssignComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnTeamComponentUnRegisterEvent.Broadcast(this);
	TeamID = INDEX_NONE;
}

void UTeamAssignComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	SharedParams.RepNotifyCondition = REPNOTIFY_Always;

	DOREPLIFETIME_WITH_PARAMS_FAST(UTeamAssignComponent, TeamID, SharedParams);
}

void UTeamAssignComponent::Server_SetTeamID_Implementation(int32 InTeamID)
{
	TeamID = InTeamID;
	OnTeamComponentIDChanged(TeamID);
	OnTeamComponentIDChangedEvent.Broadcast(TeamID);
}

void UTeamAssignComponent::OnRep_TeamID()
{
	OnTeamComponentIDChanged(TeamID);
	OnTeamComponentIDChangedEvent.Broadcast(TeamID);
}

void UTeamAssignComponent::OnTeamComponentIDChanged_Implementation(int32 InTeamID)
{
}
