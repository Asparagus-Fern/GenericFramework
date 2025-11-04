// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "ProcedureFlowExecute.h"

#include "ProcedureFlowLoad.generated.h"

class ULoadingPanel;

UCLASS(Abstract, MinimalAPI)
class UProcedureFlowLoad : public UProcedureFlowExecute
{
	GENERATED_BODY()

public:
	/* Enter Next Procedure Flow */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "ProcedureFlow"))
	FGameplayTag NextProcedureFlowTag = FGameplayTag::EmptyTag;

public:
	UFUNCTION(BlueprintCallable)
	PROCEDUREFLOWAPPLICATION_API void SwitchToNextProcedureFlow() const;
};
