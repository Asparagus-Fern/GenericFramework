// Copyright ChenTaiye 2025. All Rights Reserved.


#include "StaticFunctions/StaticFunctions_Convert.h"


bool FStaticFunctions_Convert::ToBool(unsigned int Var)
{
	return static_cast<bool>(Var);;
}

int32 FStaticFunctions_Convert::ToInt32(bool Var)
{
	return Var ? 1 : 0;
}

int32 FStaticFunctions_Convert::ToInt32(uint8 Var)
{
	return static_cast<int32>(Var);
}

int32 FStaticFunctions_Convert::ToInt32(uint32 Var)
{
	return static_cast<int32>(Var);
}

int32 FStaticFunctions_Convert::ToInt32(int64 Var)
{
	if (Var >= INT32_MIN && Var <= INT32_MAX)
	{
		return static_cast<int32>(Var);
	}
	return INDEX_NONE;
}

int32 FStaticFunctions_Convert::ToInt32(FString Var)
{
	return FCString::Atoi(*Var);
}

int32 FStaticFunctions_Convert::ToInt32(FName Var)
{
	return FCString::Atoi(*Var.ToString());
}

int32 FStaticFunctions_Convert::ToInt32(FText Var)
{
	return FCString::Atoi(*Var.ToString());
}

int64 FStaticFunctions_Convert::ToInt64(bool Var)
{
	return Var ? 1 : 0;
}

int64 FStaticFunctions_Convert::ToInt64(uint8 Var)
{
	return static_cast<int64>(Var);
}

int64 FStaticFunctions_Convert::ToInt64(uint32 Var)
{
	return static_cast<int64>(Var);
}

int64 FStaticFunctions_Convert::ToInt64(int32 Var)
{
	return static_cast<int64>(Var);
}

int64 FStaticFunctions_Convert::ToInt64(FString Var)
{
	return FCString::Atoi64(*Var);
}

int64 FStaticFunctions_Convert::ToInt64(FName Var)
{
	return FCString::Atoi64(*Var.ToString());
}

int64 FStaticFunctions_Convert::ToInt64(FText Var)
{
	return FCString::Atoi64(*Var.ToString());
}

float FStaticFunctions_Convert::ToFloat(bool Var)
{
	return Var ? 1.0f : 0.0f;
}

float FStaticFunctions_Convert::ToFloat(int32 Var)
{
	return static_cast<float>(Var);
}

float FStaticFunctions_Convert::ToFloat(int64 Var)
{
	return static_cast<float>(Var);
}

float FStaticFunctions_Convert::ToFloat(FString Var)
{
	return FCString::Atof(*Var);
}

float FStaticFunctions_Convert::ToFloat(FName Var)
{
	return FCString::Atof(*Var.ToString());
}

float FStaticFunctions_Convert::ToFloat(FText Var)
{
	return FCString::Atof(*Var.ToString());
}

FString FStaticFunctions_Convert::ToString(FString Var)
{
	return Var;
}

FString FStaticFunctions_Convert::ToString(char* Var)
{
	return ANSI_TO_TCHAR(reinterpret_cast<const char*>(Var));
}

FString FStaticFunctions_Convert::ToString(unsigned char* Var)
{
	return ANSI_TO_TCHAR(reinterpret_cast<const char*>(Var));
}

FString FStaticFunctions_Convert::ToString(bool Var)
{
	return LexToString(Var);
}

FString FStaticFunctions_Convert::ToString(uint32 Var)
{
	return LexToString(Var);
}

FString FStaticFunctions_Convert::ToString(int32 Var)
{
	return LexToString(Var);
}

FString FStaticFunctions_Convert::ToString(int64 Var)
{
	return LexToString(Var);
}

FString FStaticFunctions_Convert::ToString(float Var)
{
	return LexToString(Var);
}

FString FStaticFunctions_Convert::ToString(double Var)
{
	return LexToString(Var);
}

FString FStaticFunctions_Convert::ToString(FName Var)
{
	return LexToString(Var);
}

FString FStaticFunctions_Convert::ToString(FText Var)
{
	return Var.ToString();
}

FString FStaticFunctions_Convert::ToString(FVector2D Var)
{
	return Var.ToString();
}

FString FStaticFunctions_Convert::ToString(FTransform Var)
{
	return Var.ToString();
}

FString FStaticFunctions_Convert::ToString(FVector Var)
{
	return Var.ToString();
}

FString FStaticFunctions_Convert::ToString(FRotator Var)
{
	return Var.ToString();
}

FString FStaticFunctions_Convert::ToString(TArray<uint8> Var)
{
	return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(Var.GetData())));
}

TArray<uint8> FStaticFunctions_Convert::ToByteArray(const FString& InStr)
{
	TArray<uint8> ByteArray;

	FTCHARToUTF8 Converter(*InStr); // 创建转换器
	const uint8* Data = reinterpret_cast<const uint8*>(Converter.Get()); // 获取原始数据
	int32 Size = Converter.Length(); // 获取字节长度（不包括空终止符）
	ByteArray.Append(Data, Size);

	return ByteArray;
}
