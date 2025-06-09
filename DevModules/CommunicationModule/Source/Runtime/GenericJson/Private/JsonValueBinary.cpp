// Copyright ChenTaiye 2025. All Rights Reserved.

#include "JsonValueBinary.h"

#include "Debug/DebugType.h"

bool FJsonValueBinary::IsBinary(const TSharedPtr<FJsonValue>& InJsonValue)
{
	if (!InJsonValue.IsValid())
	{
		return false;
	}

	bool IgnoreBool;
	return !InJsonValue->TryGetBool(IgnoreBool);
}

TArray<uint8> FJsonValueBinary::AsBinary(const TSharedPtr<FJsonValue>& InJsonValue)
{
	if (FJsonValueBinary::IsBinary(InJsonValue))
	{
		const TSharedPtr<FJsonValueBinary> BinaryValue = StaticCastSharedPtr<FJsonValueBinary>(InJsonValue);

		return BinaryValue->AsBinary();
	}
	else if(InJsonValue->Type==EJson::String)
	{
		//如果我们通过 socket.io 协议 hack 得到一个未被检测为二进制的字符串,需要将这个字符串解码为 base 64
		TArray<uint8> DecodedArray;
		const bool bDidDecodeCorrectly = FBase64::Decode(InJsonValue->AsString(), DecodedArray);
		if (!bDidDecodeCorrectly)
		{
			GenericLOG(GenericLogJson, Warning, TEXT("FJsonValueBinary::AsBinary couldn't decode %s as a binary."), *InJsonValue->AsString());
		}
		return DecodedArray;
	}
	else
	{
		TArray<uint8> EmptyArray;
		return EmptyArray;
	}
}