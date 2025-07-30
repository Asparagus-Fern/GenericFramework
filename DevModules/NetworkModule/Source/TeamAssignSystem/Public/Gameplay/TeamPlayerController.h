// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interface/TeamAssignInterface.h"
#include "PlayerController/GenericPlayerController.h"
#include "TeamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMASSIGNSYSTEM_API ATeamPlayerController : public AGenericPlayerController, public ITeamAssignInterface
{
	GENERATED_BODY()

	/* ITeamAssignInterface */
public:
	virtual void CreatePlayerAssignPanel_Implementation(TSubclassOf<UTeamAssignPanel> InClass) override;
	virtual void UpdatePlayerAssignState_Implementation(APlayerController* InPlayer, ETeamAssignState InState) override;
	virtual void DestroyPlayerAssignPanel_Implementation() override;

	/* ATeamPlayerController */
private:
	UFUNCTION(Client, Reliable)
	void Client_CreatePlayerAssignPanel(TSubclassOf<UTeamAssignPanel> InClass);

	UFUNCTION(Client, Reliable)
	void Client_UpdatePlayerAssignState(APlayerController* InPlayer, ETeamAssignState InState);

	UFUNCTION(Client, Reliable)
	void Client_DestroyPlayerAssignPanel();

private:
	UPROPERTY(Transient)
	TObjectPtr<UTeamAssignPanel> TeamAssignPanel = nullptr;
};
