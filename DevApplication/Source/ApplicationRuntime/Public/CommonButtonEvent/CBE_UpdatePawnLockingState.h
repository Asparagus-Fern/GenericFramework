// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "Pawn/PawnType.h"
#include "CBE_UpdatePawnLockingState.generated.h"

/**
 * 更新Pawn锁定状态
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_UpdatePawnLockingState : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TargetPlayerIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPawnLockingState PawnLockingState;
};
