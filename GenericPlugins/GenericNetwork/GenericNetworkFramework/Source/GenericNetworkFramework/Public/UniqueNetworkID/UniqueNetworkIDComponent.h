// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "Components/ActorComponent.h"
#include "UniqueNetworkIDComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUniqueNetworkIDChanged, const FUniqueNetworkID&, UniqueNetworkID);

/**
 * 
 */
UCLASS(ClassGroup=(GenericFreamwork), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UUniqueNetworkIDComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUniqueNetworkIDComponent();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintPure)
	GENERICNETWORKFRAMEWORK_API bool GetUniqueNetworkID(FUniqueNetworkID& OutUniqueNetworkID) const;

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API void RefreshUniqueNetworkID();

	UPROPERTY(BlueprintAssignable)
	FOnUniqueNetworkIDChanged OnUniqueNetworkIDChangedEvent;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	GENERICNETWORKFRAMEWORK_API void OnUniqueNetworkIDChanged(const FUniqueNetworkID& InUniqueNetworkID);

private:
	UFUNCTION(Server, Reliable)
	void Server_RefreshUniqueNetworkID();

	UFUNCTION()
	virtual void OnRep_UniqueNetworkID();

	UPROPERTY(ReplicatedUsing="OnRep_UniqueNetworkID")
	FUniqueNetworkID UniqueNetworkID;
};
