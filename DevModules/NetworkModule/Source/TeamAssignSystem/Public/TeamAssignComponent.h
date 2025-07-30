// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TeamAssignComponent.generated.h"

class UTeamAssignInfo;

UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent))
class TEAMASSIGNSYSTEM_API UTeamAssignComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTeamAssignComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTeamComponentRegister, UTeamAssignComponent*);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTeamComponentUnRegister, UTeamAssignComponent*);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTeamComponentIDChanged, int32);

	inline static FOnTeamComponentRegister OnTeamComponentRegisterEvent;
	inline static FOnTeamComponentUnRegister OnTeamComponentUnRegisterEvent;
	FOnTeamComponentIDChanged OnTeamComponentIDChangedEvent;

public:
	UFUNCTION(Server, Reliable)
	void Server_SetTeamID(int32 InTeamID);

protected:
	UFUNCTION()
	void OnRep_TeamID();

	UFUNCTION(BlueprintNativeEvent)
	void OnTeamComponentIDChanged(int32 InTeamID);
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LocalPlayerIndex = 0;

	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing="OnRep_TeamID")
	int32 TeamID = INDEX_NONE;
};
