// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "ProcedureFlowActor.h"
#include "ProcedureFlow_Play.generated.h"

UCLASS(Abstract, MinimalAPI)
class AProcedureFlow_Play : public AProcedureFlowActor
{
	GENERATED_BODY()

public:
	AProcedureFlow_Play();

protected:
	virtual void OnProcedureFlowEnter_Implementation() override;
	virtual void OnProcedureFlowExit_Implementation() override;
};
