// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameState/GenericGameState.h"
#include "TeamAllocationGameState.generated.h"

class UTeamAllocationPanel;

/**
 * 
 */
UCLASS(MinimalAPI)
class ATeamAllocationGameState : public AGenericGameState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_TeamAllocationPanelClass();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(UIMin = "1", ClampMin = "1"), Category="Team Allocation")
	int32 MinPlayerInTeam = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(UIMin = "1", ClampMin = "1"), Category="Team Allocation")
	int32 MaxPlayerInTeam = 4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(UIMin = "1", ClampMin = "1"), Category="Team Allocation")
	int32 MaxPlayerSlotInTeam = 4;

	UPROPERTY(ReplicatedUsing="OnRep_TeamAllocationPanelClass", EditAnywhere, BlueprintReadOnly, Category="Team Allocation")
	TSubclassOf<UTeamAllocationPanel> TeamAllocationPanelClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Team Allocation")
	TObjectPtr<UDataTable> TeamInformationTable = nullptr;
};
