// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Generic/GenericSetting.h"
#include "ProcedureFlowSetting.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDUREFLOWSYSTEM_API UProcedureFlowSetting : public UGenericSetting
{
	GENERATED_UCLASS_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

#if WITH_EDITOR
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("Procedure Flow")); }
#endif

public:
	/* If True, Enter Default Procedure Flow After BeginPlay */
	UPROPERTY(Config, EditAnywhere)
	bool AutoEnterDefaultProcedureFlowTag = true;

	UPROPERTY(Config, EditAnywhere, meta=(Categories="Procedure.Flow"))
	FGameplayTag DefaultProcedureFlowTag = FGameplayTag::EmptyTag;
};
