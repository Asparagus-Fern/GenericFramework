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
	virtual int32 GetLoadCount() override;
	virtual void StartLoading() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoadCurrentWorldLevels = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> VisibleLevels;

private:
	void OnLoadCurrentWorldLevelStreamingOnceFinish();
	void OnLoadCurrentWorldLevelStreamingFinish();
	void OnLoadVisibleLevelsOnceFinish();
	void OnLoadVisibleLevelsFinish();
};
