// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlowNext.h"
#include "ProcedureFlowLoad.generated.h"

class UGenericLoadingScreenData;
class UGenericLoadingScreen;
class ULoadingPanel;

UCLASS(Abstract, MinimalAPI)
class UProcedureFlowLoad : public UProcedureFlowNext
{
	GENERATED_BODY()

protected:
	PROCEDUREFLOWAPPLICATION_API virtual void OnProcedureFlowEnter_Implementation() override;
	PROCEDUREFLOWAPPLICATION_API virtual void OnProcedureFlowExit_Implementation() override;

protected:
	PROCEDUREFLOWAPPLICATION_API virtual int32 GetLoadCount();
	PROCEDUREFLOWAPPLICATION_API virtual void StartLoading();
	PROCEDUREFLOWAPPLICATION_API virtual void OnLoadOnceFinish();
	PROCEDUREFLOWAPPLICATION_API virtual void OnLoadFinish();
	PROCEDUREFLOWAPPLICATION_API virtual void OnPerformanceLoadFinish();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bEnableLoadingScreen = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "bEnableLoadingScreen"))
	TSubclassOf<UGenericLoadingScreen> LoadingScreenClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "bEnableLoadingScreen"))
	TObjectPtr<UGenericLoadingScreenData> LoadingScreenData = nullptr;

protected:
	UPROPERTY()
	TObjectPtr<UGenericLoadingScreen> LoadingScreen = nullptr;
};
