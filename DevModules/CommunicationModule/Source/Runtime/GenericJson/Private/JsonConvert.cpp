// Copyright ChenTaiye 2025. All Rights Reserved.


#include "JsonConvert.h"
#include "JsonObjectConverter.h"
#include "JsonType.h"
#include "JsonValueBinary.h"
#include "Type/DebugType.h"
#include "Policies/CondensedJsonPrintPolicy.h"

typedef TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriterFactory;
typedef TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> FCondensedJsonStringWriter;

//The one key that will break
#define TMAP_STRING TEXT("!__!INTERNAL_TMAP")

namespace
{
	FJsonObjectConverter::CustomExportCallback EnumOverrideExportCallback;

	//Begin partial copy of FJsonObjectConverter for BP enum workaround
	bool JsonValueToFPropertyWithContainer(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags);
	bool JsonAttributesToUStructWithContainer(const TMap<FString, TSharedPtr<FJsonValue>>& JsonAttributes, const UStruct* StructDefinition, void* OutStruct, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags);

	//将json转化为property,若property不是数组或数组元素
	bool ConvertScalarJsonValueToFPropertyWithContainer(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags)
	{
		if (FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property))
		{
			if (JsonValue->Type == EJson::String)
			{
				//是否字符串枚举
				const UEnum* Enum = EnumProperty->GetEnum();
				check(Enum);
				FString StrValue = JsonValue->AsString();
				int64 IntValue = Enum->GetValueByName(FName(*StrValue));
				if (IntValue == INDEX_NONE)
				{
					GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable import enum %s from string value %s for property %s"), *Enum->CppType, *StrValue, *Property->GetNameCPP());
					return false;
				}

				EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(OutValue, IntValue);
			}
			else
			{
				//AsNumber 将为完全不合适的类型记录错误（然后给我们一个默认值）
				EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(OutValue, (int64)JsonValue->AsNumber());
			}
		}
		else if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property))
		{
			if (NumericProperty->IsEnum() && JsonValue->Type == EJson::String)
			{
				//是否字符串枚举
				const UEnum* Enum = NumericProperty->GetIntPropertyEnum();
				check(Enum); // should be assured by IsEnum()
				FString StrValue = JsonValue->AsString();
				int64 IntValue = Enum->GetValueByName(FName(*StrValue));

				if (IntValue == INDEX_NONE)
				{
					const FString LowerStrValue = StrValue.ToLower();
					//blueprints 仅支持 int8 大小enums
					int8 MaxEnum = (int8)Enum->GetMaxEnumValue();
					for (int32 i = 0; i < MaxEnum; i++)
					{
						//不区分大小写的匹配
						if (LowerStrValue.Equals(Enum->GetDisplayNameTextByIndex(i).ToString().ToLower()))
						{
							IntValue = i;
						}
					}

					if (IntValue == INDEX_NONE)
					{
						GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable import enum %s from string value %s for property %s"), *Enum->CppType, *StrValue, *Property->GetNameCPP());
						return false;
					}
				}
				NumericProperty->SetIntPropertyValue(OutValue, IntValue);
			}
			else if (NumericProperty->IsFloatingPoint())
			{
				//AsNumber 将为完全不合适的类型记录错误（然后给我们一个默认值）
				NumericProperty->SetFloatingPointPropertyValue(OutValue, JsonValue->AsNumber());
			}
			else if (NumericProperty->IsInteger())
			{
				if (JsonValue->Type == EJson::String)
				{
					// parse string ->int64 这样我们就不会丢失任何通过 AsNumber（又名双精度）的精度
					NumericProperty->SetIntPropertyValue(OutValue, FCString::Atoi64(*JsonValue->AsString()));
				}
				else
				{
					// AsNumber 将为完全不合适的类型记录错误（然后给我们一个默认值）
					NumericProperty->SetIntPropertyValue(OutValue, (int64)JsonValue->AsNumber());
				}
			}
			else
			{
				GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to set numeric property type %s for property %s"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
		{
			//AsBool 将为完全不合适的类型记录错误（然后给我们一个默认值）
			BoolProperty->SetPropertyValue(OutValue, JsonValue->AsBool());
		}
		else if (FStrProperty* StrProperty = CastField<FStrProperty>(Property))
		{
			//AsString 将为完全不合适的类型记录错误（然后给我们一个默认值）
			StrProperty->SetPropertyValue(OutValue, JsonValue->AsString());
		}
		else if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
		{
			if (JsonValue->Type == EJson::Array)
			{
				TArray<TSharedPtr<FJsonValue>> ArrayValue = JsonValue->AsArray();
				int32 ArrLen = ArrayValue.Num();

				//使输出数组大小匹配
				FScriptArrayHelper Helper(ArrayProperty, OutValue);
				Helper.Resize(ArrLen);

				//设置property值
				for (int32 i = 0; i < ArrLen; i++)
				{
					const TSharedPtr<FJsonValue>& ArrayValueItem = ArrayValue[i];
					if (ArrayValueItem.IsValid() && !ArrayValueItem->IsNull())
					{
						if (!JsonValueToFPropertyWithContainer(ArrayValueItem, ArrayProperty->Inner, Helper.GetRawPtr(i), ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags))
						{
							GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to deserialize array element [%d] for property %s"), i, *Property->GetNameCPP());
							return false;
						}
					}
				}
			}
			else
			{
				GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TArray from non-array JSON key for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FMapProperty* MapProperty = CastField<FMapProperty>(Property))
		{
			if (JsonValue->Type == EJson::Object)
			{
				TSharedPtr<FJsonObject> ObjectValue = JsonValue->AsObject();

				FScriptMapHelper Helper(MapProperty, OutValue);
				check(ObjectValue);
				int32 MapSize = ObjectValue->Values.Num();
				Helper.EmptyValues(MapSize);

				for (const auto& Entry : ObjectValue->Values)
				{
					if (Entry.Value.IsValid() && !Entry.Value->IsNull())
					{
						int32 NewIndex = Helper.AddDefaultValue_Invalid_NeedsRehash();

						TSharedPtr<FJsonValueString> TempKeyValue = MakeShared<FJsonValueString>(Entry.Key);

						const bool bKeySuccess = JsonValueToFPropertyWithContainer(TempKeyValue, MapProperty->KeyProp, Helper.GetKeyPtr(NewIndex), ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags);
						const bool bValueSuccess = JsonValueToFPropertyWithContainer(Entry.Value, MapProperty->ValueProp, Helper.GetValuePtr(NewIndex), ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags);

						if (!(bKeySuccess && bValueSuccess))
						{
							GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to deserialize map element [key: %s] for property %s"), *Entry.Key, *Property->GetNameCPP());
							return false;
						}
					}
				}

				Helper.Rehash();
			}
			else
			{
				GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TSet from non-array JSON key for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FTextProperty* TextProperty = CastField<FTextProperty>(Property))
		{
			if (JsonValue->Type == EJson::String)
			{
				//假设这个字符串已经本地化，所以导入为不变的
				TextProperty->SetPropertyValue(OutValue, FText::FromString(JsonValue->AsString()));
			}
			else if (JsonValue->Type == EJson::Object)
			{
				TSharedPtr<FJsonObject> Obj = JsonValue->AsObject();
				check(Obj.IsValid());

				FText Text;
				if (!FJsonObjectConverter::GetTextFromObject(Obj.ToSharedRef(), Text))
				{
					GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import FText from JSON object with invalid keys for property %s"), *Property->GetNameCPP());
					return false;
				}
				TextProperty->SetPropertyValue(OutValue, Text);
			}
			else
			{
				GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import FText from JSON that was neither string nor object for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			static const FName NAME_DateTime(TEXT("DateTime"));
			static const FName NAME_Color_Local(TEXT("Color"));
			static const FName NAME_LinearColor_Local(TEXT("LinearColor"));
			if (JsonValue->Type == EJson::Object)
			{
				TSharedPtr<FJsonObject> Obj = JsonValue->AsObject();
				check(Obj.IsValid());
				if (!JsonAttributesToUStructWithContainer(Obj->Values, StructProperty->Struct, OutValue, ContainerStruct, Container, CheckFlags & (~CPF_ParmFlags), SkipFlags))
				{
					GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - FJsonObjectConverter::JsonObjectToUStruct failed for property %s"), *Property->GetNameCPP());
					return false;
				}
			}
			else if (JsonValue->Type == EJson::String && StructProperty->Struct->GetFName() == NAME_LinearColor_Local)
			{
				FLinearColor& ColorOut = *(FLinearColor*)OutValue;
				FString ColorString = JsonValue->AsString();

				FColor IntermediateColor;
				IntermediateColor = FColor::FromHex(ColorString);

				ColorOut = IntermediateColor;
			}
			else if (JsonValue->Type == EJson::String && StructProperty->Struct->GetFName() == NAME_Color)
			{
				FColor& ColorOut = *(FColor*)OutValue;
				FString ColorString = JsonValue->AsString();

				ColorOut = FColor::FromHex(ColorString);
			}
			else if (JsonValue->Type == EJson::String && StructProperty->Struct->GetFName() == NAME_DateTime)
			{
				FString DateString = JsonValue->AsString();
				FDateTime& DateTimeOut = *(FDateTime*)OutValue;
				if (DateString == TEXT("min"))
				{
					//我们的日期结构的最小可表示值。 实际日期可能因平台而异（用于排序）
					DateTimeOut = FDateTime::MinValue();
				}
				else if (DateString == TEXT("max"))
				{
					//我们日期结构的最大可表示值。 实际日期可能因平台而异（用于排序）
					DateTimeOut = FDateTime::MaxValue();
				}
				else if (DateString == TEXT("now"))
				{
					// 这个值在 json 序列化中并没有真正意义（因为我们不知道时区）但是无论如何都要处理它，因为我们正在处理其他关键字
					DateTimeOut = FDateTime::UtcNow();
				}
				else if (FDateTime::ParseIso8601(*DateString, DateTimeOut))
				{
					// ok
				}
				else if (FDateTime::Parse(DateString, DateTimeOut))
				{
					// ok
				}
				else
				{
					GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable to import FDateTime for property %s"), *Property->GetNameCPP());
					return false;
				}
			}
			else if (JsonValue->Type == EJson::String && StructProperty->Struct->GetCppStructOps() && StructProperty->Struct->GetCppStructOps()->HasImportTextItem())
			{
				//ICppStructOps模板接口，用于管理对 C++ 结构构造和销毁的动态访问 
				UScriptStruct::ICppStructOps* TheCppStructOps = StructProperty->Struct->GetCppStructOps();

				FString ImportTextString = JsonValue->AsString();
				const TCHAR* ImportTextPtr = *ImportTextString;
				if (!TheCppStructOps->ImportTextItem(ImportTextPtr, OutValue, PPF_None, nullptr, (FOutputDevice*)GWarn))
				{
					// 如果自定义 ImportTextItem 无法完成，则退回到尝试标记属性方法
					Property->ImportText_Direct(ImportTextPtr, OutValue, nullptr, PPF_None);
				}
			}
			else if (JsonValue->Type == EJson::String)
			{
				FString ImportTextString = JsonValue->AsString();
				const TCHAR* ImportTextPtr = *ImportTextString;
				Property->ImportText_Direct(ImportTextPtr, OutValue, nullptr, PPF_None);
			}
			else
			{
				GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import UStruct from non-object JSON key for property %s"), *Property->GetNameCPP());
				return false;
			}
		}
		else if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			if (JsonValue->Type == EJson::Object)
			{
				UObject* Outer = GetTransientPackage();
				if (ContainerStruct->IsChildOf(UObject::StaticClass()))
				{
					Outer = (UObject*)Container;
				}

				UClass* PropertyClass = ObjectProperty->PropertyClass;
				UObject* CreatedObj = StaticAllocateObject(PropertyClass, Outer, NAME_None, EObjectFlags::RF_NoFlags, EInternalObjectFlags::None, false);
				(*PropertyClass->ClassConstructor)(FObjectInitializer(CreatedObj, PropertyClass->ClassDefaultObject, EObjectInitializerOptions::None));

				ObjectProperty->SetObjectPropertyValue(OutValue, CreatedObj);

				TSharedPtr<FJsonObject> Obj = JsonValue->AsObject();
				check(Obj.IsValid()); // should not fail if Type == EJson::Object
				if (!JsonAttributesToUStructWithContainer(Obj->Values, ObjectProperty->PropertyClass, CreatedObj, ObjectProperty->PropertyClass, CreatedObj, CheckFlags & (~CPF_ParmFlags), SkipFlags))
				{
					GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - FJsonObjectConverter::JsonObjectToUStruct failed for property %s"), *Property->GetNameCPP());
					return false;
				}
				else if (JsonValue->Type == EJson::String)
				{
					// Default to expect a string for everything else
					if (Property->ImportText_Direct(*JsonValue->AsString(), OutValue, nullptr, PPF_None) == nullptr)
					{
						GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable import property type %s from string value for property %s"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
						return false;
					}
				}
			}
		}
		else
		{
			// 默认为其他所有内容都期望一个字符串
			if (Property->ImportText_Direct(*JsonValue->AsString(), OutValue, nullptr, PPF_None) == nullptr)
			{
				GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Unable import property type %s from string value for property %s"), *Property->GetClass()->GetName(), *Property->GetNameCPP());
				return false;
			}
		}

		return true;
	}

	bool JsonValueToFPropertyWithContainer(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags)
	{
		if (!JsonValue.IsValid())
		{
			GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Invalid value JSON key"));
			return false;
		}

		const bool bArrayOrSetPeoperty = Property->IsA<FArrayProperty>() || Property->IsA<FSetProperty>();
		const bool bJsonArray = JsonValue->Type == EJson::Array;

		if (!bJsonArray)
		{
			if (bArrayOrSetPeoperty)
			{
				const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property);
				if (ArrayProperty->Inner->IsA<FByteProperty>())
				{
					//是否为二进制
					TArray<uint8> ByteArray;
					if (FJsonValueBinary::IsBinary(JsonValue))
					{
						ByteArray = FJsonValueBinary::AsBinary(JsonValue);
					}
					//若是string ,则base64转化为bytes
					else if (JsonValue->Type == EJson::String)
					{
						const bool bDidDecodeCorrectly = FBase64::Decode(JsonValue->AsString(), ByteArray);
						if (!bDidDecodeCorrectly)
						{
							GenericLOG(GenericLogJson, Warning, TEXT("FBase64::Decode failed on %s"), *Property->GetName());
							return false;
						}
					}
					else
					{
						GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TArray from unsupported non-array JSON key: %s"), *Property->GetName());
						return false;
					}

					//Memcpy raw arrays
					FScriptArrayHelper ArrayHelper(ArrayProperty, OutValue);
					ArrayHelper.EmptyAndAddUninitializedValues(ByteArray.Num());
					FGenericPlatformMemory::Memcpy(ArrayHelper.GetRawPtr(), ByteArray.GetData(), ByteArray.Num());
					return true;
				}

				//End custom workaround 
				GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonValueToUProperty - Attempted to import TArray from non-array JSON key"));
				return false;
			}

			if (Property->ArrayDim != 1)
			{
				GenericLOG(GenericLogJson, Warning, TEXT("Ignoring excess properties when deserializing %s"), *Property->GetName());
			}
			return ConvertScalarJsonValueToFPropertyWithContainer(JsonValue, Property, OutValue, ContainerStruct, Container, CheckFlags, SkipFlags);
		}

		//实际上，ArrayDim == 1 检查应该是多余的，因为不支持 UProperty 的嵌套数组
		if (bArrayOrSetPeoperty && Property->ArrayDim == 1)
		{
			// Read into TArray
			return ConvertScalarJsonValueToFPropertyWithContainer(JsonValue, Property, OutValue, ContainerStruct, Container, CheckFlags, SkipFlags);
		}

		//反序列化一个 JSON 数组
		const auto& ArrayValue = JsonValue->AsArray();
		if (Property->ArrayDim < ArrayValue.Num())
		{
			GenericLOG(GenericLogJson, Warning, TEXT("BPEnumWA-Ignoring excess properties when deserializing %s"), *Property->GetName());
		}

		//读入本机数组
		const int ItemsToRead = FMath::Clamp(ArrayValue.Num(), 0, Property->ArrayDim);
		for (int Index = 0; Index != ItemsToRead; ++Index)
		{
			if (!ConvertScalarJsonValueToFPropertyWithContainer(ArrayValue[Index], Property, (char*)OutValue + Index * Property->GetElementSize(), ContainerStruct, Container, CheckFlags, SkipFlags))
			{
				return false;
			}
		}
		return true;
	}

	bool JsonAttributesToUStructWithContainer(const TMap<FString, TSharedPtr<FJsonValue>>& JsonAttributes, const UStruct* StructDefinition, void* OutStruct, const UStruct* ContainerStruct, void* Container, int64 CheckFlags, int64 SkipFlags)
	{
		if (StructDefinition == FJsonObjectWrapper::StaticStruct())
		{
			// 将其复制到对象中
			FJsonObjectWrapper* ProxyObject = (FJsonObjectWrapper*)OutStruct;
			ProxyObject->JsonObject = MakeShared<FJsonObject>();
			ProxyObject->JsonObject->Values = JsonAttributes;
			return true;
		}

		int32 NumUnclaimedProperties = JsonAttributes.Num();
		if (NumUnclaimedProperties <= 0)
		{
			return true;
		}

		//遍历
		for (TFieldIterator<FProperty> PropIt(StructDefinition); PropIt; ++PropIt)
		{
			FProperty* Property = *PropIt;

			//检查是否忽略Property

			if (CheckFlags != 0 && !Property->HasAnyPropertyFlags(CheckFlags))
			{
				continue;
			}

			if (Property->HasAnyPropertyFlags(SkipFlags))
			{
				continue;
			}

			//找到json值对应的property name
			const TSharedPtr<FJsonValue>* JsonValue = JsonAttributes.Find(Property->GetName());

			if (!JsonValue)
			{
				continue;
			}

			if (JsonValue->IsValid() && !(*JsonValue)->IsNull())
			{
				void* Value = Property->ContainerPtrToValuePtr<uint8>(OutStruct);
				if (!JsonValueToFPropertyWithContainer(*JsonValue, Property, Value, ContainerStruct, Container, CheckFlags, SkipFlags))
				{
					GenericLOG(GenericLogJson, Error, TEXT("BPEnumWA-JsonObjectToUStruct - Unable to parse %s.%s from JSON"), *StructDefinition->GetName(), *Property->GetName());
					return false;
				}
			}

			if (--NumUnclaimedProperties <= 0)
			{
				break;
			}
		}
		return true;
	}
}

FString FIVTrimmedKeyMap::ToString()
{
	FString SubMapString;
	for (auto Pair : SubMap)
	{
		FString PairString = FString::Printf(TEXT("{%s:%s}"), *Pair.Key, *Pair.Value->ToString());
		SubMapString.Append(PairString);
		SubMapString.Append(",");
	}
	return FString::Printf(TEXT("{%s:%s}"), *LongKey, *SubMapString);
}

FString FJsonConvert::ToJsonString(const TSharedPtr<FJsonObject>& JsonObject)
{
	FString OutputString;
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), FCondensedJsonStringWriterFactory::Create(&OutputString));
	return OutputString;
}

FString FJsonConvert::ToJsonString(const TSharedPtr<FJsonValue>& JsonValue)
{
	if (JsonValue->Type == EJson::None)
	{
		return FString();
	}
	else if (JsonValue->Type == EJson::Null)
	{
		return FString();
	}
	else if (JsonValue->Type == EJson::String)
	{
		return JsonValue->AsString();
	}
	else if (JsonValue->Type == EJson::Number)
	{
		return FString::Printf(TEXT("%f"), JsonValue->AsNumber());
	}
	else if (JsonValue->Type == EJson::Boolean)
	{
		return FString::Printf(TEXT("%d"), JsonValue->AsBool());
	}
	else if (JsonValue->Type == EJson::Array)
	{
		return ToJsonString(JsonValue->AsArray());
	}
	else if (JsonValue->Type == EJson::Object)
	{
		return ToJsonString(JsonValue->AsObject());
	}
	else
	{
		return FString();
	}
}

FString FJsonConvert::ToJsonString(const TArray<TSharedPtr<FJsonValue>>& JsonValueArray)
{
	FString OutputString;
	FJsonSerializer::Serialize(JsonValueArray, FCondensedJsonStringWriterFactory::Create(&OutputString));
	return OutputString;
}

TSharedPtr<FJsonObject> FJsonConvert::ConstructJsonObject()
{
	return MakeShareable(new FJsonObject);
}

TSharedPtr<FJsonObject> FJsonConvert::ConstructJsonObject(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(*JsonString), JsonObject);
	return JsonObject;
}

bool FJsonConvert::StructToJsonObject(const UStruct* Struct, const void* StructPtr, const TSharedRef<FJsonObject>& OutJsonObject)
{
	return FJsonObjectConverter::UStructToJsonObject(Struct, StructPtr, OutJsonObject);
}

bool FJsonConvert::JsonObjectToStruct(const TSharedPtr<FJsonObject>& JsonObject, const UStruct* Struct, void* StructPtr)
{
	return FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), Struct, StructPtr);
}

bool FJsonConvert::StructToJsonFile(const FString& FilePath, const UStruct* Struct, const void* StructPtr)
{
	FString JsonString;
	ensure(FJsonObjectConverter::UStructToJsonObjectString(Struct, StructPtr, JsonString) || JsonString.IsEmpty());
	return FFileHelper::SaveStringToFile(JsonString, *FilePath);
}

bool FJsonConvert::JsonFileToStruct(const FString& FilePath, const UStruct* Struct, void* StructPtr)
{
	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *FilePath) || JsonString.IsEmpty())
	{
		GenericLOG(GenericLogJson, Warning, TEXT("Json data load fail, invalid jons file : %s"), *FilePath)
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
	{
		GenericLOG(GenericLogJson, Warning, TEXT("Json data serializer fail, invalid jons file : %s"), *FilePath)
		return false;
	}

	if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), Struct, StructPtr))
	{
		GenericLOG(GenericLogJson, Warning, TEXT("Json converter fail, invalid jons file : %s"), *FilePath)
		return false;
	}

	return true;
}

TSharedPtr<FJsonValue> FJsonConvert::ToJsonValue(const TSharedPtr<FJsonObject>& JsonObject)
{
	return MakeShareable(new FJsonValueObject(JsonObject));
}

TSharedPtr<FJsonValue> FJsonConvert::ToJsonValue(const FString& StringValue)
{
	return MakeShareable(new FJsonValueString(StringValue));
}

TSharedPtr<FJsonValue> FJsonConvert::ToJsonValue(double NumberValue)
{
	return MakeShareable(new FJsonValueNumber(NumberValue));
}

TSharedPtr<FJsonValue> FJsonConvert::ToJsonValue(bool BoolValue)
{
	return MakeShareable(new FJsonValueBoolean(BoolValue));
}

TSharedPtr<FJsonValue> FJsonConvert::ToJsonValue(const TArray<uint8>& BinaryValue)
{
	return MakeShareable(new FJsonValueBinary(BinaryValue));
}

TSharedPtr<FJsonValue> FJsonConvert::ToJsonValue(const TArray<TSharedPtr<FJsonValue>>& ArrayValue)
{
	return MakeShareable(new FJsonValueArray(ArrayValue));
}

TSharedPtr<FJsonValue> FJsonConvert::JsonStringToJsonValue(const FString& JsonString)
{
	//Null
	if (JsonString.IsEmpty())
	{
		return MakeShareable(new FJsonValueNull);
	}

	//Number
	if (JsonString.IsNumeric())
	{
		//convert to double
		return MakeShareable(new FJsonValueNumber(FCString::Atod(*JsonString)));
	}

	//Object
	if (JsonString.StartsWith(FString(TEXT("{"))))
	{
		TSharedPtr<FJsonObject> JsonObject = ConstructJsonObject(JsonString);
		return MakeShareable(new FJsonValueObject(JsonObject));
	}

	//Array
	if (JsonString.StartsWith(FString(TEXT("["))))
	{
		TArray<TSharedPtr<FJsonValue>> RawJsonValueArray;
		if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(*JsonString), RawJsonValueArray))
		{
			return MakeShareable(new FJsonValueArray(RawJsonValueArray));
		}
	}

	//Bool
	if (JsonString == FString("true") || JsonString == FString("false"))
	{
		const bool BooleanValue = (JsonString == FString("true"));
		return MakeShareable(new FJsonValueBoolean(BooleanValue));
	}

	//String
	return MakeShareable(new FJsonValueString(JsonString));
}

TArray<TSharedPtr<FJsonValue>> FJsonConvert::JsonStringToJsonArray(const FString& JsonString)
{
	TArray<TSharedPtr<FJsonValue>> RawJsonValueArray;
	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(*JsonString), RawJsonValueArray);

	return RawJsonValueArray;
}

void FJsonConvert::TrimValueKeyNames(const TSharedPtr<FJsonValue>& JsonValue)
{
	//Array?
	if (JsonValue->Type == EJson::Array)
	{
		auto Array = JsonValue->AsArray();

		for (auto SubValue : Array)
		{
			TrimValueKeyNames(SubValue);
		}
	}
	//Object?
	else if (JsonValue->Type == EJson::Object)
	{
		const auto JsonObject = JsonValue->AsObject();
		for (auto Pair : JsonObject->Values)
		{
			const FString& Key = Pair.Key;
			FString TrimmedKey;

			const bool DidNeedTrimming = TrimKey(Key, TrimmedKey);

			//keep attempting sub keys even if we have a valid string
			auto SubValue = Pair.Value;
			TrimValueKeyNames(SubValue);

			if (DidNeedTrimming)
			{
				//Replace field names with the trimmed key
				JsonObject->SetField(TrimmedKey, SubValue);
				JsonObject->RemoveField(Key);
			}
		}
	}
	else
	{
		//GenericLOG(LogTemp, Warning, TEXT("TrimValueKeyNames:: uncaught type is: %d"), (int)JsonValue->Type);
	}
}

bool FJsonConvert::TrimKey(const FString& InLongKey, FString& OutTrimmedKey)
{
	//Look for the position of the 2nd '_'
	int32 LastIndex = InLongKey.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	LastIndex = InLongKey.Find(TEXT("_"), ESearchCase::IgnoreCase, ESearchDir::FromEnd, LastIndex);

	if (LastIndex >= 0)
	{
		OutTrimmedKey = InLongKey.Mid(0, LastIndex);;
		return true;
	}
	else
	{
		return false;
	}
}

void FJsonConvert::SetTrimmedKeyMapForStruct(const TSharedPtr<FIVTrimmedKeyMap>& InMap, const UStruct* Struct)
{
	//Get the child fields
	FField* FieldPtr = Struct->ChildProperties;

	//If it hasn't been set, the long key is the json standardized long name
	if (InMap->LongKey.IsEmpty())
	{
		InMap->LongKey = FJsonObjectConverter::StandardizeCase(Struct->GetName());
	}

	//For each child field...
	while (FieldPtr != nullptr)
	{
		//Map our trimmed name to our full name
		const FString& LowerKey = FJsonObjectConverter::StandardizeCase(FieldPtr->GetName());
		FString TrimmedKey;
		const bool DidTrim = TrimKey(LowerKey, TrimmedKey);

		//Set the key map
		TSharedPtr<FIVTrimmedKeyMap> SubMap = MakeShareable(new FIVTrimmedKeyMap);
		SubMap->LongKey = LowerKey;

		//No-trim case, trim = long
		if (!DidTrim)
		{
			TrimmedKey = SubMap->LongKey;
		}

		//Did we get a substructure?
		const FStructProperty* SubStruct = CastField<FStructProperty>(FieldPtr);
		const FArrayProperty* ArrayProp = CastField<FArrayProperty>(FieldPtr);
		FMapProperty* MapProperty = CastField<FMapProperty>(FieldPtr);

		if (SubStruct != nullptr)
		{
			//We did, embed the sub-map
			SetTrimmedKeyMapForStruct(SubMap, SubStruct->Struct);
		}

		//Did we get a sub-array?
		else if (ArrayProp != nullptr)
		{
			//set the inner map for the inner property
			//GenericLOG(LogTemp, Log, TEXT("found array: %s"), *ArrayProp->GetName());
			SetTrimmedKeyMapForProp(SubMap, ArrayProp->Inner);
		}
		else if (MapProperty != nullptr)
		{
			//GenericLOG(LogTemp, Log, TEXT("I'm a tmap: %s"), *MapProperty->GetName());
			SetTrimmedKeyMapForProp(SubMap, MapProperty);
		}

		//Debug types
		/**
		UProperty* ObjectProp = Cast<UProperty>(FieldPtr);
		if (ObjectProp)
		{
			GenericLOG(LogTemp, Log, TEXT("found map: %s, %s, type: %s, %s"),
				*ObjectProp->GetName(),
				*ObjectProp->GetNameCPP(),
				*ObjectProp->GetClass()->GetFName().ToString(),
				*ObjectProp->GetCPPType());
		}*/

		InMap->SubMap.Add(TrimmedKey, SubMap);
		//GenericLOG(LogTemp, Log, TEXT("long: %s, trim: %s, is struct: %d"), *SubMap->LongKey, *TrimmedKey, SubStruct != NULL);

		FieldPtr = FieldPtr->Next;
	}

	//GenericLOG(LogTemp, Log, TEXT("Final map: %d"), InMap->SubMap.Num());
}

void FJsonConvert::SetTrimmedKeyMapForProp(TSharedPtr<FIVTrimmedKeyMap>& InMap, FProperty* InnerProperty)
{
	//GenericLOG(LogTemp, Log, TEXT("got prop: %s"), *InnerProperty->GetName());
	const FStructProperty* SubStruct = CastField<FStructProperty>(InnerProperty);
	const FArrayProperty* ArrayProp = CastField<FArrayProperty>(InnerProperty);
	const FMapProperty* MapProperty = CastField<FMapProperty>(InnerProperty);

	if (SubStruct != nullptr)
	{
		//We did, embed the sub-map
		SetTrimmedKeyMapForStruct(InMap, SubStruct->Struct);
	}
	//Did we get a sub-array?
	else if (ArrayProp != nullptr)
	{
		SetTrimmedKeyMapForProp(InMap, ArrayProp->Inner);
	}
	else if (MapProperty != nullptr)
	{
		//Make a special submap with special TMAP identifier key
		TSharedPtr<FIVTrimmedKeyMap> SubMap = MakeShareable(new FIVTrimmedKeyMap);
		SubMap->LongKey = TMAP_STRING;
		InMap->SubMap.Add(SubMap->LongKey, SubMap);

		//Take the value property and set it as it's unique child
		SetTrimmedKeyMapForProp(SubMap, MapProperty->ValueProp);

		//Each child in the JSON object map will use the same structure (it's a UE4 limitation of maps anyway
	}
}

void FJsonConvert::ReplaceJsonValueNamesWithMap(const TSharedPtr<FJsonValue>& JsonValue, const TSharedPtr<FIVTrimmedKeyMap>& KeyMap)
{
	if (JsonValue->Type == EJson::Object)
	{
		//Go through each key in the object
		const auto Object = JsonValue->AsObject();
		auto SubMap = KeyMap->SubMap;
		auto AllValues = Object->Values;

		FString PreviewPreValue = FJsonConvert::ToJsonString(Object);
		//GenericLOG(LogTemp, Log, TEXT("Rep::PreObject: <%s>"), *PreviewPreValue);

		for (auto Pair : AllValues)
		{
			if (SubMap.Contains(TMAP_STRING))
			{
				FString TMapString = FString(TMAP_STRING);
				//If we found a tmap, replace each sub key with list of keys
				ReplaceJsonValueNamesWithMap(Pair.Value, SubMap[TMapString]);
			}
			else if (SubMap.Num() > 0 && SubMap.Contains(Pair.Key))
			{
				//Get the long key for entry
				const FString& LongKey = SubMap[Pair.Key]->LongKey;

				//loop nested structures
				ReplaceJsonValueNamesWithMap(Pair.Value, SubMap[Pair.Key]);

				if (Pair.Key != LongKey)
				{
					//finally set the field and remove the old field
					Object->SetField(LongKey, Pair.Value);
					Object->RemoveField(Pair.Key);
				}
			}
		}

		FString PreviewPostValue = FJsonConvert::ToJsonString(Object);
		//GenericLOG(LogTemp, Log, TEXT("Rep::PostObject: <%s>"), *PreviewPostValue);
	}
	else if (JsonValue->Type == EJson::Array)
	{
		auto Array = JsonValue->AsArray();
		for (auto Item : Array)
		{
			//GenericLOG(LogTemp, Log, TEXT("%s"), *Item->AsString());
			ReplaceJsonValueNamesWithMap(Item, KeyMap);
		}
	}
}
