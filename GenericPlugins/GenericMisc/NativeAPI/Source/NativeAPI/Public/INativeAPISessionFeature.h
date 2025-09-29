// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Features/IModularFeature.h"
#include "NativeAPITypes.h"

DECLARE_DELEGATE_OneParam(FOnReceiveNativePayload, const FNativeAPIPayload&);

/**
 * 
 */
class NATIVEAPI_API INativeAPISessionFeature : public IModularFeature
{
public:
	static FName GetFeatureName()
	{
		static FName NativeAPISessionFeatureName(TEXT("NativeAPISession"));
		return NativeAPISessionFeatureName;
	};

	virtual ~INativeAPISessionFeature()
	{
	}

	virtual FName GetSessionName() = 0;
	virtual bool StartSession() = 0;
	virtual void EndSession() = 0;

protected:
	void SetReceiveSessionPayloadBinding(FOnReceiveNativePayload&& InDelegate)
	{
		ReceiveNativePayload = MoveTemp(InDelegate);
	}

	void NotifyReceiveNativePayload(const FNativeAPIPayload& Payload) const
	{
		ReceiveNativePayload.ExecuteIfBound(Payload);
	}

	FOnReceiveNativePayload ReceiveNativePayload;
	friend class UNativeAPISubsystem;
};
