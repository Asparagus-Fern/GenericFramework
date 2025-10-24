// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlowLoad.h"
#include "ProcedureFlowLoadLevelStreaming.generated.h"

UCLASS(MinimalAPI)
class UProcedureFlowLoadLevelStreaming : public UProcedureFlowLoad
{
	GENERATED_BODY()

protected:
	PROCEDUREFLOWAPPLICATION_API virtual void OnProcedureFlowEnter_Implementation() override;
	PROCEDUREFLOWAPPLICATION_API virtual void OnProcedureFlowExit_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoadCurrentWorldLevels = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> VisibleLevels;

protected:
	PROCEDUREFLOWAPPLICATION_API virtual void OnLoadCurrentWorldLevelStreamingOnceFinish();
	PROCEDUREFLOWAPPLICATION_API virtual void OnLoadCurrentWorldLevelStreamingFinish();
	PROCEDUREFLOWAPPLICATION_API virtual void OnLoadVisibleLevelsOnceFinish();
	PROCEDUREFLOWAPPLICATION_API virtual void OnLoadVisibleLevelsFinish();
};
