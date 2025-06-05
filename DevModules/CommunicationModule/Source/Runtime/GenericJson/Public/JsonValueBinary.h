// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "JsonValueBinary.generated.h"

/**
 * 
 */
class GENERICJSON_API FJsonValueBinary : public FJsonValue
{
public:
	FJsonValueBinary(const TArray<uint8>& InBinary) : Value(InBinary) { Type = EJson::String; }

	virtual bool TryGetString(FString& OutString) const override
	{
		//OutString = FString::FromHexBlob(Value.GetData(), Value.Num());	//HEX encoding
		OutString = FBase64::Encode(Value); //Base64 encoding
		return true;
	}

	virtual bool TryGetNumber(double& OutDouble) const override
	{
		OutDouble = Value.Num();
		return true;
	}

	//hackery: we use this as an indicator we have a binary (strings don't normally do this)
	virtual bool TryGetBool(bool& OutBool) const override { return false; }

	/** 返回二进制数据. */
	TArray<uint8> AsBinary() { return Value; }

	/** 判断FJsonValue是否为Binary. */
	static bool IsBinary(const TSharedPtr<FJsonValue>& InJsonValue);

	/** 获取Brinary数组若要使用此方法,最好用IsBinary做判断. */
	static TArray<uint8> AsBinary(const TSharedPtr<FJsonValue>& InJsonValue);

protected:
	TArray<uint8> Value;

	virtual FString GetType() const override { return TEXT("Binary"); }
};
