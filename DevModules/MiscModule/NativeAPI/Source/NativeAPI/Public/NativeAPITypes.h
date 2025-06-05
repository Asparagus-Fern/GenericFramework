// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "NativeAPITypes.generated.h"

UENUM()
enum EWebSocketProtocol : uint8
{
	ws,
	wss
};

FORCEINLINE FString EnumToString(EWebSocketProtocol InProtocol)
{
	FString Result;
	
	switch (InProtocol) {
	case ws:
		Result = TEXT("ws");
		break;
	case wss:
		Result = TEXT("wss");
		break;
	}
	
	return Result;
}

USTRUCT(BlueprintType)
struct NATIVEAPI_API FWebSocketConnect
{
	GENERATED_BODY()

public:
	FWebSocketConnect()
		: Host(TEXT("127.0.0.1"))
		, Port(8070)
		, Protocol(EWebSocketProtocol::ws)
	{ }
	
	// hostname  i.e. : "127.0.0.1" , "airtmeta.com" or "unreal.epicgames.com"
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Default)
	FString Host;

	// Host port i.e. : 0 ~ 65535
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, ClampMax = 65535, UIMin = 0, UIMax = 65535), Category = Default)
	int32 Port;

	// Protocol, i.e. "ws" or "wss"
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Default)
	TEnumAsByte<EWebSocketProtocol> Protocol;

	// headers
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = Default)
	TMap<FString, FString> Headers;
	
	FString GetUrl() const
	{
		FStringFormatNamedArguments Arguments;
		Arguments.Add(TEXT("PROTOCOL"), EnumToString(Protocol));
		Arguments.Add(TEXT("HOST"), Host);
		Arguments.Add(TEXT("PORT"), FString::FromInt(Port));
		
		return FString::Format(TEXT("{PROTOCOL}://{HOST}:{PORT}"), Arguments);
	}

	bool IsValid() const
	{
		return !Host.IsEmpty() && Port != INDEX_NONE;
	}
};

/**
 * 描述一个 Native API 任务.
 */
struct NATIVEAPI_API FNativeAPITask
{
	bool IsValid() const
	{
		return !FuncName.IsNone() && ParamJson.IsValid();	
	}
	
	FName FuncName;
	
	TSharedPtr<FJsonObject> ParamJson;

	bool operator==(const FNativeAPITask& Other) const
	{
		return Other.FuncName == FuncName;
	}

	bool operator!=(const FNativeAPITask& Other) const
	{
		return !operator==(Other);
	}
};

/**
 * Native API 执行凭据.
 */
USTRUCT()
struct NATIVEAPI_API FNativeAPIPayload
{
	GENERATED_BODY()

public:
	FNativeAPIPayload() { }
	
	bool IsValid() const
	{
		return EntityClassPath.IsValid() && !TaskList.IsEmpty();
	}

	// Entity Class 软引用, 用于确定 UClass 类型.
	FSoftClassPath GetClassPath() const { return EntityClassPath; }

	// UWorld 软引用, 用于确定世界.
	FSoftObjectPath GetWorldPath() const { return WorldPath; }

	// Entity Object 软引用, 用于确定Native API 实例对象.
	FSoftObjectPath GetEntityPath() const { return EntityObjectPath; }
	
	// Entity 标识符.
	FName GetEntity() const { return Entity; }

	// 获取任务列表 ...
	void GetTaskList(TArray<FNativeAPITask>& OutList) const { OutList = TaskList; }

	// 检查 EntityPath 是否存在
	bool IsValidEntityPath() const { return EntityObjectPath.IsSubobject(); }
	
	// 检查接口对象是否为消费者.
	bool IsConsumer(TScriptInterface<class INativeAPIEntityInterface> InScript) const;

#if WITH_EDITOR
	void FixupFromPIE(int32 PIEInstance);
#endif
	
private:
	FSoftClassPath EntityClassPath;
	FSoftObjectPath WorldPath;
	FName Entity;
	FSoftObjectPath EntityObjectPath;
	TArray<FNativeAPITask> TaskList;

	friend class FNativeAPIUtilities;
	friend class ANativeAPITestActor;
};