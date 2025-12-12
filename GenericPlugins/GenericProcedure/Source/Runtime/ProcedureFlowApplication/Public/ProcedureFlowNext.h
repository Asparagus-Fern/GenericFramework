#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlowExecute.h"
#include "ProcedureFlowNext.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UProcedureFlowNext : public UProcedureFlowExecute
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	PROCEDUREFLOWAPPLICATION_API void SwitchToNextProcedureFlow() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "ProcedureFlow"))
	FGameplayTag NextProcedureFlowTag = FGameplayTag::EmptyTag;
};
