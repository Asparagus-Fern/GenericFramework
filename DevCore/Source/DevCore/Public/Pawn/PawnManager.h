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

protected:
	UPROPERTY(Transient)
	TMap<FGameplayTag, IPawnInterface*> PawnMapping;

	// protected:
	// 	TMap<int32, FGameplayTag> LastPossessPawn;
	// 	TMap<int32, FGameplayTag> CurrentPossessPawn;
};
