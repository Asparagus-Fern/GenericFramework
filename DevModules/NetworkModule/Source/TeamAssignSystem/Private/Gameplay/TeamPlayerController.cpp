// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Gameplay/TeamPlayerController.h"

#include "GenericGameHUDManager.h"
#include "GenericWidgetManager.h"
#include "UMG/TeamAssignPanel.h"

void ATeamPlayerController::CreatePlayerAssignPanel_Implementation(TSubclassOf<UTeamAssignPanel> InClass)
{
	ITeamAssignInterface::CreatePlayerAssignPanel_Implementation(InClass);
	Client_CreatePlayerAssignPanel(InClass);
}

void ATeamPlayerController::UpdatePlayerAssignState_Implementation(APlayerController* InPlayer, ETeamAssignState InState)
{
	ITeamAssignInterface::UpdatePlayerAssignState_Implementation(InPlayer, InState);
	Client_UpdatePlayerAssignState(InPlayer, InState);
}

void ATeamPlayerController::DestroyPlayerAssignPanel_Implementation()
{
	ITeamAssignInterface::DestroyPlayerAssignPanel_Implementation();
	Client_DestroyPlayerAssignPanel();
}

void ATeamPlayerController::Client_CreatePlayerAssignPanel_Implementation(TSubclassOf<UTeamAssignPanel> InClass)
{
	FOnWidgetActiveStateChanged OnWidgetActiveStateChanged;
	OnWidgetActiveStateChanged.BindLambda([this](UGenericWidget* InWidget)
		{
			TeamAssignPanel = Cast<UTeamAssignPanel>(InWidget);
		}
	);

	OpenGenericWidget<UTeamAssignPanel>(InClass, OnWidgetActiveStateChanged);
}

void ATeamPlayerController::Client_UpdatePlayerAssignState_Implementation(APlayerController* InPlayer, ETeamAssignState InState)
{
	if (TeamAssignPanel)
	{
		TeamAssignPanel->UpdatePlayerAssignState(InPlayer, InState);
	}
}

void ATeamPlayerController::Client_DestroyPlayerAssignPanel_Implementation()
{
	CloseGenericWidget(TeamAssignPanel);
}
