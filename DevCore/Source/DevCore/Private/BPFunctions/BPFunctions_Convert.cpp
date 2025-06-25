// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_Convert.h"

bool FConvertLibrary::ToBool(unsigned int Var)
{
	return static_cast<bool>(Var);;
}

int32 FConvertLibrary::ToInt32(bool Var)
{
	return Var ? 1 : 0;
}

int32 FConvertLibrary::ToInt32(uint8 Var)
{
	return static_cast<int32>(Var);
}

int32 FConvertLibrary::ToInt32(uint32 Var)
{
	return static_cast<int32>(Var);
}

int32 FConvertLibrary::ToInt32(int64 Var)
{
	if (Var >= INT32_MIN && Var <= INT32_MAX)
	{
		return static_cast<int32>(Var);
	}
	return INDEX_NONE;
}

int32 FConvertLibrary::ToInt32(FString Var)
{
	return FCString::Atoi(*Var);
}

int32 FConvertLibrary::ToInt32(FName Var)
{
	return FCString::Atoi(*Var.ToString());
}

int32 FConvertLibrary::ToInt32(FText Var)
{
	return FCString::Atoi(*Var.ToString());
}

int64 FConvertLibrary::ToInt64(bool Var)
{
	return Var ? 1 : 0;
}

int64 FConvertLibrary::ToInt64(uint8 Var)
{
	return static_cast<int64>(Var);
}

int64 FConvertLibrary::ToInt64(uint32 Var)
{
	return static_cast<int64>(Var);
}

int64 FConvertLibrary::ToInt64(int32 Var)
{
	return static_cast<int64>(Var);
}

int64 FConvertLibrary::ToInt64(FString Var)
{
	return FCString::Atoi64(*Var);
}

int64 FConvertLibrary::ToInt64(FName Var)
{
	return FCString::Atoi64(*Var.ToString());
}

int64 FConvertLibrary::ToInt64(FText Var)
{
	return FCString::Atoi64(*Var.ToString());
}

float FConvertLibrary::ToFloat(bool Var)
{
	return Var ? 1.0f : 0.0f;
}

float FConvertLibrary::ToFloat(int32 Var)
{
	return static_cast<float>(Var);
}

float FConvertLibrary::ToFloat(int64 Var)
{
	return static_cast<float>(Var);
}

float FConvertLibrary::ToFloat(FString Var)
{
	return FCString::Atof(*Var);
}

float FConvertLibrary::ToFloat(FName Var)
{
	return FCString::Atof(*Var.ToString());
}

float FConvertLibrary::ToFloat(FText Var)
{
	return FCString::Atof(*Var.ToString());
}

FString FConvertLibrary::ToString(char* Var)
{
	return ANSI_TO_TCHAR(reinterpret_cast<const char*>(Var));
}

FString FConvertLibrary::ToString(unsigned char* Var)
{
	return ANSI_TO_TCHAR(reinterpret_cast<const char*>(Var));
}

FString FConvertLibrary::ToString(bool Var)
{
	return LexToString(Var);
}

FString FConvertLibrary::ToString(uint32 Var)
{
	return LexToString(Var);
}

FString FConvertLibrary::ToString(int32 Var)
{
	return LexToString(Var);
}

FString FConvertLibrary::ToString(int64 Var)
{
	return LexToString(Var);
}

FString FConvertLibrary::ToString(float Var)
{
	return LexToString(Var);
}

FString FConvertLibrary::ToString(FName Var)
{
	return LexToString(Var);
}

FString FConvertLibrary::ToString(FText Var)
{
	return Var.ToString();
}

FString FConvertLibrary::ToString(FVector2D Var)
{
	return Var.ToString();
}

FString FConvertLibrary::ToString(FTransform Var)
{
	return Var.ToString();
}

FString FConvertLibrary::ToString(FVector Var)
{
	return Var.ToString();
}

FString FConvertLibrary::ToString(FRotator Var)
{
	return Var.ToString();
}

FString FConvertLibrary::ToString(TArray<uint8> Var)
{
	return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(Var.GetData())));
}

TArray<uint8> FConvertLibrary::ToByteArray(const FString& InStr)
{
	TArray<uint8> ByteArray;

	FTCHARToUTF8 Converter(*InStr); // 创建转换器
	const uint8* Data = reinterpret_cast<const uint8*>(Converter.Get()); // 获取原始数据
	int32 Size = Converter.Length(); // 获取字节长度（不包括空终止符）
	ByteArray.Append(Data, Size);

	return ByteArray;
}
