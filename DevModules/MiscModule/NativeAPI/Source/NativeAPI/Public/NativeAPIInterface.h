// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NativeAPIInterface.generated.h"

class FJsonObject;
struct FNativeAPIPayload;

UINTERFACE(MinimalAPI, NotBlueprintable)
class UNativeAPIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATIVEAPI_API INativeAPIInterface
{
	GENERATED_BODY()

public:
	typedef UNativeAPIInterface UClassType;

	virtual void ProcessingNativeAPI(const FNativeAPIPayload& Payload) const { };
	
	virtual void SendSimulationNativeAPIMessage_Internal(const TSharedPtr<FJsonObject>& InJson) const;
	void SendSimulationNativeAPIMessage(const FString& JsonStr) const;
};

UINTERFACE(MinimalAPI, NotBlueprintable)
class UNativeAPIEntityInterface : public UInterface
{
	GENERATED_BODY()
};

class NATIVEAPI_API INativeAPIEntityInterface : public INativeAPIInterface
{
	GENERATED_BODY()

public:
	typedef UNativeAPIEntityInterface UClassType;
	
	virtual FString GetEntity() const { return TEXT(""); };
	
	virtual UClass* GetEntityClass() const;

	FString GetEntityPath() const;
};