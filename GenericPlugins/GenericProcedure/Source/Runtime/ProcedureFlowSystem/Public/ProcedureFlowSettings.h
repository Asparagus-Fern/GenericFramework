// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Settings/GenericSettings.h"
#include "ProcedureFlowSettings.generated.h"

/**
 * 
 */
UCLASS()
class UProcedureFlowSettings : public UGenericSettings
{
	GENERATED_UCLASS_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	/* If True, Enter Default Procedure Flow After BeginPlay */
	UPROPERTY(Config, EditAnywhere)
	bool AutoEnterDefaultProcedureFlow = true;

	UPROPERTY(Config, EditAnywhere, meta=(Categories="ProcedureFlow"))
	FGameplayTag DefaultProcedureFlowTag = FGameplayTag::EmptyTag;
};
