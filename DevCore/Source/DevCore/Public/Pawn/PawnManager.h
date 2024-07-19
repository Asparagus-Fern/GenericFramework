// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreManager.h"
#include "PawnManager.generated.h"

class IPawnInterface;

/**
 * 
 */
UCLASS()
class DEVCORE_API UPawnManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UPawnManager();

	/* IManagerInterface */
public:
	virtual FText GetManagerDisplayName() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UPawnManager */
public:
	void RegisterPawn(IPawnInterface* InPawnInterface);
	void UnRegisterPawn(IPawnInterface* InPawnInterface);
	virtual void PossessPawn(int32 PlayerIndex, FGameplayTag InPawnTag);
	virtual IPawnInterface* GetPawnInterface(FGameplayTag InPawnTag);
	virtual APawn* GetPawn(FGameplayTag InPawnTag);

public:	
	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.1f, ClampMax = 2.f))
	float MovementSpeed = 1.f;
							
	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.1f, ClampMax = 2.f))
	float RotationSpeed = 1.f;

	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadOnly, meta=(ClampMin = -89.9f, ClampMax = 0.f))
	float MinRotationPitch = -88.f;

	UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadOnly, meta=(ClampMin = -89.9f, ClampMax = 0.f))
	float MaxRotationPitch = -2.f;

protected:
	UPROPERTY(Transient)
	TMap<FGameplayTag, IPawnInterface*> PawnMapping;
};
