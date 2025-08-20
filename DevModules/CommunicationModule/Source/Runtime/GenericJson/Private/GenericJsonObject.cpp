// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericJsonObject.h"

#include "JsonType.h"

typedef TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> FJsonWriterFactory;
typedef TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> FJsonWriter;

UGenericJsonObject::UGenericJsonObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Reset();
}

UGenericJsonObject* UGenericJsonObject::ConstructJsonObject(UObject* WorldContextObject)
{
	return NewObject<UGenericJsonObject>(WorldContextObject);
}

void UGenericJsonObject::Reset()
{
	if (JsonObject.IsValid())
	{
		JsonObject.Reset();
	}

	JsonObject = MakeShareable(new FJsonObject());
}

bool UGenericJsonObject::EncodeJson(FString& OutJsonString)
{
	if (!JsonObject.IsValid())
	{
		Reset();

		GenericLOG(GenericLogJson, Error, TEXT("Invalid Json Object"));
		return false;
	}

	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), FJsonWriterFactory::Create(&JsonString)))
	{
		OutJsonString = JsonString;
		return true;
	}

	return false;
}

bool UGenericJsonObject::DecodeJson(const FString& InJsonString)
{
	if (!JsonObject.IsValid())
	{
		Reset();

		GenericLOG(GenericLogJson, Error, TEXT("Invalid Json Object"));
		return false;
	}

	if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(*InJsonString), JsonObject))
	{
		SetJsonString(InJsonString);
		return true;
	}

	GenericLOG(GenericLogJson, Error, TEXT("Json decoding failed for: %s"), *InJsonString);
	return false;
}

TSharedPtr<FJsonObject>& UGenericJsonObject::GetJsonObject()
{
	return JsonObject;
}

void UGenericJsonObject::SetJsonObject(const TSharedPtr<FJsonObject>& InJsonObject)
{
	JsonObject = InJsonObject;
}

FString UGenericJsonObject::GetJsonString()
{
	return JsonString;
}

void UGenericJsonObject::SetJsonString(FString InJsonString)
{
	JsonString = InJsonString;
}
