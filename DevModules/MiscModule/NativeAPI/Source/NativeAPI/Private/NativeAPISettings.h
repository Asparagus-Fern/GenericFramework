// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeAPITypes.h"
#include "Engine/DeveloperSettings.h"
#include "Generic/GenericSettings.h"
#include "WebSocket/WebSocketType.h"
#include "NativeAPISettings.generated.h"

/**
 * 
 */
UCLASS()
class UNativeAPISettings : public UGenericSettings
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
#if WITH_EDITOR
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("Native API Settings")); }
#endif
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "WebSocket")
	bool bSupportWebSocket = false;

	UPROPERTY(Config, EditAnywhere, meta = (EditCondition = "bSupportWebSocket"), Category = "WebSocket")
	FGenericWebSocketConnection Connect;

public:
	UPROPERTY(Config, EditAnywhere, Category = "HTTP")
	bool bSupportHTTP = false;

	UPROPERTY(Config, EditAnywhere, meta = (EditCondition = "bSupportHTTP", ClampMin = 0, ClampMax = 65545, UIMin = 0, UIMax = 65535), Category = "HTTP")
	int32 HTTPServerPort = INDEX_NONE;
};
