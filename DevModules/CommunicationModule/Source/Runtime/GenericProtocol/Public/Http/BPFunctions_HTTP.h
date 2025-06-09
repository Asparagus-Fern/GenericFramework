// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTTPType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_HTTP.generated.h"

/**
 * 
 */
UCLASS()
class GENERICPROTOCOL_API UBPFunctions_HTTP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Http Verb Enum", CompactNodeTitle = "->", BlueprintAutocast), Category="HTTP")
	static EHttpVerb BP_ConvertStringVerbToEnum(FString InVerb);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Http Verb String", CompactNodeTitle = "->", BlueprintAutocast), Category="HTTP")
	static FString BP_ConvertEnumVerbToString(EHttpVerb InVerb);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Http Mime Type Enum", CompactNodeTitle = "->", BlueprintAutocast), Category="HTTP")
	static EHttpMimeType BP_ConvertStringMimeTypeToEnum(FString InMimeType);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Http Mime Type String", CompactNodeTitle = "->", BlueprintAutocast), Category="HTTP")
	static FString BP_ConvertEnumMimeTypeToString(EHttpMimeType InMimeType);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Response Code Enum", CompactNodeTitle = "->", BlueprintAutocast), Category="HTTP")
	static EHttpResponseCode BP_ConvertToResponseCodeEnum(int32 InCode);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Response Code", CompactNodeTitle = "->", BlueprintAutocast), Category="HTTP")
	static int32 BP_ConvertToResponseCode(EHttpResponseCode InCode);

	/* HTTP Global */
public:
	/* 获取每个服务器允许的最大连接数 */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	int32 GetHttpMaxConnectionsPerServer();

	/* 获取用于联系服务器的代理地址 */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	FString GetProxyAddress();

	/* 获取HTTP请求的最大读取缓冲区大小 */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	int32 GetMaxReadBufferSize();

	/**
	* 添加要附加到未来请求的默认标头
	* 如果请求已经指定了此标头，则不会使用默认版本
	* @param HeaderName 标头的名称（例如，“内容类型”）
	* @param HeaderValue 标头的值
	*/
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	static void AddDefaultHeader(const FString& HeaderName, const FString& HeaderValue);

	/**
	* 代理地址的设置程序。
	* @param InProxyAddress 要使用的新代理地址。
	*/
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	static void SetProxyAddress(const FString& InProxyAddress);

	/**
	* 设置请求的最大读取缓冲区大小。
	* @param SizeInBytes 用于读取缓冲区的最大字节数
	*/
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	static void SetMaxReadBufferSize(const int32 SizeInBytes);

	/* 设置空闲HTTP线程的最小 tick rate */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	static void SetHttpThreadIdleMinimumSleepTimeInSeconds(const float Time);

	/* 设置空闲HTTP线程的tick rate of an idle */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	static void SetHttpThreadIdleFrameTimeInSeconds(const float Time);

	/* 设置活动HTTP线程的最小 tick rate */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	static void SetHttpThreadActiveMinimumSleepTimeInSeconds(const float Time);

	/* 设置活动HTTP线程的目标节拍 tick rate */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	static void SetHttpThreadActiveFrameTimeInSeconds(const float Time);

	/* 设置每个http请求的最小延迟时间 */
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	static void SetHttpDelayTime(const float Delay);

public:
	/**转义参数并将其添加到URL的末尾*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HTTP")
	static FString AddParametersToUrl(FString InUrl, const TMap<FString, FString>& Parameters);
};
