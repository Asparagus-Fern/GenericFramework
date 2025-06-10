// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WebSocket/WebSocketAsyncActionBase.h"
#include "ReStartWebSocketAsyncAction.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UReStartWebSocketAsyncAction : public UWebSocketAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWebSocketReStartedEvent OnReStarted;

	UPROPERTY(BlueprintAssignable)
	FWebSocketReStartErrorEvent OnReStartError;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category ="WebSocket")
	static UReStartWebSocketAsyncAction* ReStart();

protected:
	virtual void OnReStartedInternal() override;
	virtual void OnReStartErrorInternal(const FString& Error) override;
};
