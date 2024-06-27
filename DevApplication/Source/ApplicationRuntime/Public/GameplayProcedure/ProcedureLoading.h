// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/GameplayProcedure.h"
#include "ProcedureLoading.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureLoading_Default);

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UProcedureLoading : public UGameplayProcedure
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
};
