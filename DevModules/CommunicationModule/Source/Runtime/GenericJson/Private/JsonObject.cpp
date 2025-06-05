// Copyright ChenTaiye 2025. All Rights Reserved.

#include "JsonObject.h"

typedef TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> FJsonWriterFactory;
typedef TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> FJsonWriter;

UJsonObject::UJsonObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Reset();
}

UJsonObject* UJsonObject::ConstructJsonObject(UObject* WorldContextObject)
{
	return NewObject<UJsonObject>(WorldContextObject);
}

void UJsonObject::Reset()
{
	if (JsonObject.IsValid())
	{
		JsonObject.Reset();
	}

	JsonObject = MakeShareable(new FJsonObject());
}

bool UJsonObject::EncodeJson(FString& OutJsonString)
{
	if (!JsonObject.IsValid())
	{
		Reset();

		GenericLOG(JsonLog, Error, TEXT("Invalid Json Object"));
		return false;
	}

	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), FJsonWriterFactory::Create(&JsonString)))
	{
		OutJsonString = JsonString;
		return true;
	}

	return false;
}

bool UJsonObject::DecodeJson(const FString& InJsonString)
{
	if (!JsonObject.IsValid())
	{
		Reset();

		GenericLOG(JsonLog, Error, TEXT("Invalid Json Object"));
		return false;
	}

	if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(*InJsonString), JsonObject))
	{
		SetJsonString(InJsonString);
		return true;
	}

	GenericLOG(JsonLog, Error, TEXT("Json decoding failed for: %s"), *InJsonString);
	return false;
}

TSharedPtr<FJsonObject>& UJsonObject::GetJsonObject()
{
	return JsonObject;
}

void UJsonObject::SetJsonObject(const TSharedPtr<FJsonObject>& InJsonObject)
{
	JsonObject = InJsonObject;
}

FString UJsonObject::GetJsonString()
{
	return JsonString;
}

void UJsonObject::SetJsonString(FString InJsonString)
{
	JsonString = InJsonString;
}
