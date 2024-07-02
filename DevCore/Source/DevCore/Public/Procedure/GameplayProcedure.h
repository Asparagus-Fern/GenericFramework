// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProcedureInterface.h"
#include "UObject/Object.h"
#include "GameplayProcedure.generated.h"

class UTimelineComponent;
/**
 * 
 */
UCLASS(BlueprintType)
class DEVCORE_API UGameplayProcedure : public UObject, public IProcedureBaseInterface, public IProcedureInterface
{
	GENERATED_BODY()

public:
	UGameplayProcedure();
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
};
