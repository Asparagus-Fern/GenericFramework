// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "StaticFunctions/StaticFunctions_Enum.h"
#include "WebSocketType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGenericWebSocketProtocol : uint8
{
	ws,
	wss
};

inline EGenericWebSocketProtocol ConvertToWebSocketProtocolEnum(const FString& InProtocol)
{
	EGenericWebSocketProtocol HttpVerb;
	if (FStaticFunctions_Enum::GetEnumByNameString(InProtocol, HttpVerb))
	{
		return HttpVerb;
	}

	return EGenericWebSocketProtocol::ws;
}

inline FString ConvertToWebSocketProtocolString(EGenericWebSocketProtocol InProtocol)
{
	return FStaticFunctions_Enum::GetEnumNameString(InProtocol);
}

/**
 * 
 */
USTRUCT(BlueprintType)
struct GENERICPROTOCOL_API FGenericWebSocketConnection
{
	GENERATED_BODY()

public:
	// hostname  i.e. : "127.0.0.1"
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	FString Host;

	// Host port i.e. : 0 ~ 65535
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, ClampMax = 65535, UIMin = 0, UIMax = 65535))
	int32 Port = INDEX_NONE;

	// Protocol, i.e. "ws" or "wss"
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	EGenericWebSocketProtocol Protocol = EGenericWebSocketProtocol::ws;

	// headers
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> Headers;

public:
	bool IsValid() const { return !Host.IsEmpty() && Port != INDEX_NONE; }

	FString GetUrl() const
	{
		FStringFormatNamedArguments Arguments;
		Arguments.Add(TEXT("PROTOCOL"), ConvertToWebSocketProtocolString(Protocol));
		Arguments.Add(TEXT("HOST"), Host);
		Arguments.Add(TEXT("PORT"), FString::FromInt(Port));

		return FString::Format(TEXT("{PROTOCOL}://{HOST}:{PORT}"), Arguments);
	}
};


/**
 * 官方响应代码
 */
UENUM(BlueprintType)
enum class EGenericWebSocketCode : uint8
{
	Code1000 UMETA(DisplayName="Code1000 : Close Normal", ToolTip="正常关闭; 无论为何目的而创建，该链接都已成功完成任务。"),
	Code1001 UMETA(DisplayName="Code1001 : Close Going Away", ToolTip="终端离开，可能因为服务端错误，也可能因为浏览器正从打开连接的页面跳转离开。"),
	Code1002 UMETA(DisplayName="Code1002 : Close Protocol Error", ToolTip="由于协议错误而中断连接。"),
	Code1003 UMETA(DisplayName="Code1003 : Close Unsupported", ToolTip="由于接收到不允许的数据类型而断开连接。"),
	Code1004 UMETA(DisplayName="Code1004 : Undefined", ToolTip="保留。"),
	Code1005 UMETA(DisplayName="Code1005 : Close No Status", ToolTip="没有收到预期的状态码。"),
	Code1006 UMETA(DisplayName="Code1006 : Close Abnormal", ToolTip="期望收到状态码时连接非正常关闭。"),
	Code1007 UMETA(DisplayName="Code1007 : Unsupported Data", ToolTip="收到了格式不符的数据而断开连接。"),
	Code1008 UMETA(DisplayName="Code1008 : Policy Violation", ToolTip="收到不符合约定的数据而断开连接。这是一个通用状态码，用于不适合使用 1003 和 1009 状态码的场景。"),
	Code1009 UMETA(DisplayName="Code1009 : Close Too Large", ToolTip="收到过大的数据帧而断开连接。"),
	Code1010 UMETA(DisplayName="Code1010 : Missing Extension", ToolTip="客户端期望服务器商定一个或多个拓展，但服务器没有处理，因此客户端断开连接。"),
	Code1011 UMETA(DisplayName="Code1011 : Internal Error", ToolTip="客户端由于遇到没有预料的情况阻止其完成请求，因此服务端断开连接。"),
	Code1012 UMETA(DisplayName="Code1012 : Service Restart", ToolTip="服务器由于重启而断开连接。"),
	Code1013 UMETA(DisplayName="Code1013 : Try Again Later", ToolTip="服务器由于临时原因断开连接，如服务器过载。"),
	Code1014 UMETA(DisplayName="Code1014 : Undefined", ToolTip="保留。"),
	Code1015 UMETA(DisplayName="Code1015 : TLS Handshake", ToolTip="连接由于无法完成 TLS 握手而关闭 (例如无法验证服务器证书)。"),

	CodeUnKnown UMETA(DisplayName="UnKnown Error")
};

inline EGenericWebSocketCode ConvertToWebSocketCodeEnum(const int32 InCode)
{
	const FString CodeString = TEXT("Code") + FString::FromInt(InCode);

	EGenericWebSocketCode Code;
	if (FStaticFunctions_Enum::GetEnumByNameString(CodeString, Code))
	{
		return Code;
	}

	return EGenericWebSocketCode::CodeUnKnown;
}

inline int32 ConvertToWebSocketCodeInt(const EGenericWebSocketCode InCode)
{
	if (InCode == EGenericWebSocketCode::CodeUnKnown)
	{
		return -1;
	}

	FString CodeString = FStaticFunctions_Enum::GetEnumNameString(InCode);
	CodeString.Split(TEXT("Code"), nullptr, &CodeString, ESearchCase::CaseSensitive);

	return FCString::Atoi(*CodeString);
}
