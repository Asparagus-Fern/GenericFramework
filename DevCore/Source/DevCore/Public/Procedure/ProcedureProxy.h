// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureType.h"
#include "Common/CommonObject.h"
#include "UObject/Object.h"
#include "ProcedureProxy.generated.h"

class UProcedureManager;
class IProcedureInterface;

enum class EProcedureState
{
	Continue,
	Pause,
	Stop,
};

/**
 * 流程处理的调度代理
 */
UCLASS()
class DEVCORE_API UProcedureProxy : public UCommonObject
{
	GENERATED_BODY()

	friend UProcedureManager;

public:
	UFUNCTION(BlueprintCallable)
	void Pause();

	UFUNCTION(BlueprintCallable)
	void Continue();

	UFUNCTION(BlueprintCallable)
	void Stop();

protected:
	void Handle(const FProcedureHandleGroup& InHandles);

private:
	void HandleInternal();
	void OnHandleOnceFinish();
	void OnHandleFinish();

	FProcedureHandleGroup ProcedureHandleGroup;
	int32 HandleIndex = 0;
	FProcedureHandle CurrentProcedureHandle;
	EProcedureState ProcedureState = EProcedureState::Continue;
};
