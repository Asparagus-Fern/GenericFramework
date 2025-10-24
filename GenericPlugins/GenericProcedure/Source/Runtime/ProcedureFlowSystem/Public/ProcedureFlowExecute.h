// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlowInterface.h"
#include "Generic/GenericObject.h"
#include "ProcedureFlowExecute.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UProcedureFlowExecute : public UGenericObject, public IProcedureFlowInterface
{
	GENERATED_BODY()

	/* IProcedureFlowInterface */
public:
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowRegister_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowInitialized_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowEnter_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void ReInitProcedureFlow_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowExit_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowDeinitialize_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowUnRegister_Implementation() override;
};
