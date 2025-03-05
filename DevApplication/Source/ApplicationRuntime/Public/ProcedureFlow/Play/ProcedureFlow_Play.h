// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "ProcedureFlowActor.h"
#include "ProcedureFlow_Play.generated.h"

class UManagerWorldSetting;

UCLASS(Abstract, MinimalAPI)
class AProcedureFlow_Play : public AProcedureFlowActor
{
	GENERATED_BODY()

public:
	AProcedureFlow_Play();

protected:
	virtual void OnProcedureFlowEnter_Implementation() override;
	virtual void OnProcedureFlowExit_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="WorldSetting")
	TSet<UManagerWorldSetting*> ManagerWorldSettings;
};
