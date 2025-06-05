// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPIInterface.h"
#include "NativeAPILog.h"
#include "NativeAPITypes.h"
#include "NativeAPIUtilities.h"
#include "Debug/DebugType.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void INativeAPIInterface::SendSimulationNativeAPIMessage_Internal(const TSharedPtr<FJsonObject>& InJson) const
{
	if (!InJson.IsValid())
	{
		GenericLOG(LogNativeAPI, Warning, TEXT("Send simulation native api fail, invalid json object."))
		return;
	}

	FNativeAPIPayload Payload;

	if (!FNativeAPIUtilities::ConvertNativeAPIJsonToPayload(InJson, Payload) || !Payload.IsValid())
	{
		GenericLOG(LogNativeAPI, Warning, TEXT("解析 Native API Json 失败!"))
		return;
	}

	this->ProcessingNativeAPI(Payload);
}

void INativeAPIInterface::SendSimulationNativeAPIMessage(const FString& JsonStr) const
{
	if (JsonStr.IsEmpty())
	{
		GenericLOG(LogNativeAPI, Warning, TEXT("Send simulation native api fail! json string can not be empty!"))
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;

	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonStr);

	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
	{
		return;
	}

	if (FNativeAPIUtilities::IsNativeAPIJson(JsonObject))
	{
		return;
	}

	this->SendSimulationNativeAPIMessage_Internal(JsonObject);
}

UClass* INativeAPIEntityInterface::GetEntityClass() const
{
	const auto ThisObject = Cast<UObject>(this);
	if (ThisObject != nullptr)
	{
		return ThisObject->GetClass();
	}

	return nullptr;
}

FString INativeAPIEntityInterface::GetEntityPath() const
{
	const auto ThisObject = Cast<UObject>(this);

	if (ThisObject != nullptr)
	{
		return ThisObject->GetPathName();
	}

	return TEXT("");
}
