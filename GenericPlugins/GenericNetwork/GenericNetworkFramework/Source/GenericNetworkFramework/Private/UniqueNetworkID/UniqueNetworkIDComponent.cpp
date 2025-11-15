// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "UniqueNetworkID/UniqueNetworkIDComponent.h"

#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Type/DebugType.h"
#include "UniqueNetworkID/UniqueNetworkIDInterface.h"

UUniqueNetworkIDComponent::UUniqueNetworkIDComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UUniqueNetworkIDComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		RefreshUniqueNetworkID();
	}
}

void UUniqueNetworkIDComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUniqueNetworkIDComponent, UniqueNetworkID);
}

bool UUniqueNetworkIDComponent::GetUniqueNetworkID(FUniqueNetworkID& OutUniqueNetworkID) const
{
	if (UniqueNetworkID.CheckIsValid())
	{
		OutUniqueNetworkID = UniqueNetworkID;
		return true;
	}
	else
	{
		return false;
	}
}

void UUniqueNetworkIDComponent::RefreshUniqueNetworkID()
{
	if (GetOwnerRole() == ROLE_Authority || GetOwnerRole() == ROLE_None)
	{
		FUniqueNetworkID NewUniqueNetworkID;

		if (APlayerController* Player = Cast<APlayerController>(GetOwner()))
		{
			NewUniqueNetworkID = FUniqueNetworkID(Player);
		}
		else if (APlayerState* PlayerState = Cast<APlayerState>(GetOwner()))
		{
			NewUniqueNetworkID = FUniqueNetworkID(PlayerState);
		}
		else if (APawn* Pawn = Cast<APawn>(GetOwner()))
		{
			if (APlayerController* PawnController = Pawn->GetController<APlayerController>())
			{
				NewUniqueNetworkID = FUniqueNetworkID(PawnController);
			}
		}
		else if (IUniqueNetworkIDInterface* NetworkUserInterface = Cast<IUniqueNetworkIDInterface>(GetOwner()))
		{
			if (APlayerState* InterfacePlayerState = NetworkUserInterface->GetPlayerState())
			{
				NewUniqueNetworkID = FUniqueNetworkID(InterfacePlayerState);
			}
		}

		if (NewUniqueNetworkID.CheckIsValid() && NewUniqueNetworkID != UniqueNetworkID)
		{
			UniqueNetworkID = NewUniqueNetworkID;
			OnRep_UniqueNetworkID();
		}
	}
	else if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		Server_RefreshUniqueNetworkID();
	}
	else if (GetOwnerRole() == ROLE_SimulatedProxy)
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("This Actor Is No Authority To RefreshUniqueNetworkID"))
	}
	else
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("Error To RefreshUniqueNetworkID"))
	}
}

void UUniqueNetworkIDComponent::Server_RefreshUniqueNetworkID_Implementation()
{
	RefreshUniqueNetworkID();
}

void UUniqueNetworkIDComponent::OnRep_UniqueNetworkID()
{
	OnUniqueNetworkIDChanged(UniqueNetworkID);
	OnUniqueNetworkIDChangedEvent.Broadcast(UniqueNetworkID);
}
