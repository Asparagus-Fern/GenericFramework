// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPIUtilities.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/PackageName.h"
#include "NativeAPILog.h"
#include "Type/DebugType.h"

#define NATIVE_API_ENTITY_CLASS_FIELD TEXT("EntityClass")
#define NATIVE_API_WORLD_PATH_FIELD TEXT("WorldPath")
#define NATIVE_API_ENTITY_PATH_FIELD TEXT("EntityPath")
#define NATIVE_API_ENTITY_FIELD TEXT("Entity")
#define NATIVE_API_PREFIX TEXT("API_")

bool FNativeAPIUtilities::IsNativeAPIJson(const TSharedPtr<FJsonObject>& Json)
{
	if(Json.IsValid())
	{
		return Json->HasTypedField<EJson::String>(NATIVE_API_ENTITY_CLASS_FIELD);
	}

	return false;
}

bool FNativeAPIUtilities::IsNativeAPIFunctionName(const FName& InName)
{
	return InName.ToString().StartsWith(NATIVE_API_PREFIX);
}

void FNativeAPIUtilities::ReadStruct(const TSharedPtr<FJsonObject>& JsonObject, const UStruct* Struct, void* Instance, UObject* Owner)
{
	FString TypeName;
	JsonObject->TryGetStringField(TEXT("$type"), TypeName);

	if (!TypeName.IsEmpty() && !ensureAlwaysMsgf(Struct->GetName().Equals(TypeName), TEXT("Type name mismatch in FEditorConfig::ReadUObject. Expected: %s, Actual: %s"), *Struct->GetName(), *TypeName))
	{
		return;
	}

	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		const FProperty* Property = *It;

		void* DataPtr = Property->ContainerPtrToValuePtr<void>(Instance);
			
		TSharedPtr<FJsonValue> Value = JsonObject->TryGetField(Property->GetName());
		if (Value.IsValid())
		{
			ReadValue(Value, Property, DataPtr, Owner);
		}
	}
}
void FNativeAPIUtilities::ReadValue(const TSharedPtr<FJsonValue>& JsonValue, const FProperty* Property, void* DataPtr, UObject* Owner)
{
	if (Property->IsA<FStrProperty>())
	{
		FString* Value = (FString*) DataPtr;
		JsonValue->TryGetString(*Value);
		return;
	}

	if (Property->IsA<FNameProperty>())
	{
		FString TempValue;
		JsonValue->TryGetString(TempValue);

		*(FName*) DataPtr = *TempValue;
		return;
	}

	if (Property->IsA<FTextProperty>())
	{
		FString TempValue;
		JsonValue->TryGetString(TempValue);

		*(FText*) DataPtr = FText::FromString(TempValue);
		return;
	}

	if (Property->IsA<FBoolProperty>())
	{
		bool Value = ((FBoolProperty*)Property)->GetDefaultPropertyValue();
		if (JsonValue->TryGetBool(Value))
		{
			((FBoolProperty*)Property)->SetPropertyValue(DataPtr, Value);
		}
		return;
	}

	if (Property->IsA<FFloatProperty>())
	{
		float* Value = (float*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FDoubleProperty>())
	{
		double* Value = (double*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FInt8Property>())
	{
		int8* Value = (int8*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FInt16Property>())
	{
		int16* Value = (int16*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FIntProperty>())
	{
		int32* Value = (int32*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FInt64Property>())
	{
		int64* Value = (int64*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FByteProperty>())
	{
		uint8* Value = (uint8*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FUInt16Property>())
	{
		uint16* Value = (uint16*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FUInt32Property>())
	{
		uint32* Value = (uint32*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FUInt64Property>())
	{
		uint64* Value = (uint64*) DataPtr;
		JsonValue->TryGetNumber(*Value);
		return;
	}

	if (Property->IsA<FEnumProperty>())
	{
		UEnum* Enum = ((FEnumProperty*)Property)->GetEnum();
		FString ValueString;
		if (JsonValue->TryGetString(ValueString))
		{
			int64 Index = Enum->GetIndexByNameString(ValueString);
			if (Index != INDEX_NONE)
			{
				int64 Value = Enum->GetValueByIndex(Index);
				((FEnumProperty*)Property)->GetUnderlyingProperty()->SetIntPropertyValue(DataPtr, Value);
			}
		}
		return;
	}

	if (Property->IsA<FObjectPropertyBase>())
	{
		FString PathString;
		if (JsonValue->TryGetString(PathString))
		{
			Property->ImportText_Direct(*PathString, DataPtr, Owner, 0);
		}
		return;
	}

	if (Property->IsA<FStructProperty>())
	{
		const TSharedPtr<FJsonObject>* ObjectJsonValue;
		if (JsonValue->TryGetObject(ObjectJsonValue))
		{
			ReadStruct(*ObjectJsonValue, ((FStructProperty*)Property)->Struct, DataPtr, Owner);
		}
		else if (JsonValue->Type == EJson::String)
		{
			FString ImportTextString;
			if (JsonValue->TryGetString(ImportTextString))
			{
				Property->ImportText_Direct(*ImportTextString, DataPtr, Owner, 0);
			}
		}
		return;
	}

	if (Property->IsA<FArrayProperty>())
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayJsonValue;
		if (JsonValue->TryGetArray(ArrayJsonValue))
		{
			FProperty* InnerProperty = ((FArrayProperty*)Property)->Inner;
			FScriptArrayHelper ArrayHelper((FArrayProperty*)Property, DataPtr);

			ArrayHelper.EmptyAndAddValues(ArrayJsonValue->Num());

			for (int32 Idx = 0; Idx < ArrayHelper.Num(); ++Idx)
			{
				TSharedPtr<FJsonValue> Value = (*ArrayJsonValue)[Idx];
				ReadValue(Value, InnerProperty, ArrayHelper.GetRawPtr(Idx), Owner);
			}
		}
		return;
	}

	if (Property->IsA<FSetProperty>())
	{
		const TArray<TSharedPtr<FJsonValue>>* SetJsonValue;
		if (JsonValue->TryGetArray(SetJsonValue))
		{
			const FProperty* InnerProperty = ((FSetProperty*)Property)->ElementProp;
			FScriptSetHelper SetHelper((FSetProperty*)Property, DataPtr);
			SetHelper.EmptyElements(SetJsonValue->Num());
			
			TArray<uint8> TempBuffer;
			TempBuffer.AddUninitialized(InnerProperty->GetElementSize());

			for (int32 Idx = 0; Idx < SetJsonValue->Num(); ++Idx)
			{
				InnerProperty->InitializeValue(TempBuffer.GetData());

				TSharedPtr<FJsonValue> Value = (*SetJsonValue)[Idx];
				ReadValue(Value, InnerProperty, TempBuffer.GetData(), Owner);

				SetHelper.AddElement(TempBuffer.GetData());

				InnerProperty->DestroyValue(TempBuffer.GetData());
			}
		}
		return;
	}

	if (Property->IsA<FMapProperty>())
	{
		FMapProperty* MapProperty = (FMapProperty*)Property;
		const FProperty* KeyProperty = MapProperty->KeyProp;
		const FProperty* ValueProperty = MapProperty->ValueProp;

		FScriptMapHelper MapHelper(MapProperty, DataPtr);
		const TSharedPtr<FJsonObject>* JsonObjectValue;
		if (JsonValue->TryGetObject(JsonObjectValue))
		{
			MapHelper.EmptyValues((*JsonObjectValue)->Values.Num());

			// temporary buffers to read elements into
			TArray<uint8> TempKey;
			TempKey.AddZeroed(KeyProperty->GetElementSize());

			TArray<uint8> TempValue;
			TempValue.AddZeroed(ValueProperty->GetElementSize());

			for (const TPair<FString, TSharedPtr<FJsonValue>>& JsonPair : (*JsonObjectValue)->Values)
			{
				KeyProperty->InitializeValue(TempKey.GetData());
				KeyProperty->ImportText_Direct(*JsonPair.Key, TempKey.GetData(), Owner, 0);

				ValueProperty->InitializeValue(TempValue.GetData());
				ReadValue(JsonPair.Value, ValueProperty, TempValue.GetData(), Owner);

				MapHelper.AddPair(TempKey.GetData(), TempValue.GetData());

				KeyProperty->DestroyValue(TempKey.GetData());
				ValueProperty->DestroyValue(TempValue.GetData());
			}

			return;
		}

		const TArray<TSharedPtr<FJsonValue>>* JsonArrayPtr = nullptr;
		if (JsonValue->TryGetArray(JsonArrayPtr))
		{
			MapHelper.EmptyValues(JsonArrayPtr->Num());

			TArray<uint8> TempKey;
			TempKey.AddUninitialized(KeyProperty->GetElementSize());

			TArray<uint8> TempValue;
			TempValue.AddUninitialized(ValueProperty->GetElementSize());

			for (const TSharedPtr<FJsonValue>& JsonElement : *JsonArrayPtr)
			{
				TSharedPtr<FJsonObject>* JsonObject = nullptr;
				if (JsonElement->TryGetObject(JsonObject))
				{
					TSharedPtr<FJsonValue> JsonKeyField = (*JsonObject)->TryGetField(TEXT("$key"));
					TSharedPtr<FJsonValue> JsonValueField = (*JsonObject)->TryGetField(TEXT("$value"));

					if (JsonKeyField.IsValid() && JsonValueField.IsValid())
					{
						KeyProperty->InitializeValue(TempKey.GetData());
						ReadValue(JsonKeyField, KeyProperty, TempKey.GetData(), Owner);

						ValueProperty->InitializeValue(TempValue.GetData());
						ReadValue(JsonValueField, ValueProperty, TempValue.GetData(), Owner);

						MapHelper.AddPair(TempKey.GetData(), TempValue.GetData());

						KeyProperty->DestroyValue(TempKey.GetData());
						ValueProperty->DestroyValue(TempValue.GetData());
					}
				}
			}

			return;
		}
	}

	ensureAlwaysMsgf(false, TEXT("Property type is unsupported: %s, type: %s"), *Property->GetPathName(), *Property->GetClass()->GetName());
}

TSharedPtr<FJsonValue> FNativeAPIUtilities::WriteArray(const FArrayProperty* ArrayProperty, const void* DataPtr)
{
	const FProperty* InnerProperty = ArrayProperty->Inner;
	FScriptArrayHelper ArrayHelper(ArrayProperty, DataPtr);

	TArray<TSharedPtr<FJsonValue>> JsonValuesArray;
	JsonValuesArray.Reserve(ArrayHelper.Num());

	for (int32 Idx = 0; Idx < ArrayHelper.Num(); ++Idx)
	{
		if (ArrayHelper.IsValidIndex(Idx))
		{
			TSharedPtr<FJsonValue> ElementValue = WriteValue(InnerProperty, ArrayHelper.GetRawPtr(Idx), nullptr);
			check(ElementValue.IsValid());
			JsonValuesArray.Add(ElementValue);
		}
	}

	return MakeShared<FJsonValueArray>(JsonValuesArray);
}

TSharedPtr<FJsonValue> FNativeAPIUtilities::WriteSet(const FSetProperty* SetProperty, const void* DataPtr)
{
	const FProperty* InnerProperty = SetProperty->ElementProp;
	FScriptSetHelper SetHelper(SetProperty, DataPtr);

	TArray<TSharedPtr<FJsonValue>> JsonValuesArray;
	JsonValuesArray.Reserve(SetHelper.Num());

	for (int32 Idx = 0; Idx < SetHelper.Num(); ++Idx)
	{
		if (SetHelper.IsValidIndex(Idx))
		{
			TSharedPtr<FJsonValue> ElementValue = WriteValue(InnerProperty, SetHelper.GetElementPtr(Idx), nullptr);
			check(ElementValue.IsValid());
			JsonValuesArray.Add(ElementValue);
		}
	}

	return MakeShared<FJsonValueArray>(JsonValuesArray);
}

TSharedPtr<FJsonValue> FNativeAPIUtilities::WriteMap(const FMapProperty* MapProperty, const void* DataPtr)
{
	TSharedPtr<FJsonValue> ResultValue;

	const FProperty* KeyProperty = MapProperty->KeyProp;
	const FProperty* ValueProperty = MapProperty->ValueProp;

	FScriptMapHelper MapHelper(MapProperty, DataPtr);

	if (MapHelper.Num() == 0)
	{
		ResultValue = MakeShared<FJsonValueObject>(MakeShared<FJsonObject>());
	}
	else
	{
		TArray<TSharedPtr<FJsonValue>> JsonKeysArray;
		JsonKeysArray.Reserve(MapHelper.Num());

		TArray<TSharedPtr<FJsonValue>> JsonValuesArray;
		JsonValuesArray.Reserve(MapHelper.Num());

		for (int32 Idx = 0; Idx < MapHelper.Num(); ++Idx)
		{
			if (MapHelper.IsValidIndex(Idx))
			{
				TSharedPtr<FJsonValue> JsonKey = WriteValue(KeyProperty, MapHelper.GetKeyPtr(Idx), nullptr);
				check(JsonKey.IsValid());
				JsonKeysArray.Add(JsonKey);

				TSharedPtr<FJsonValue> JsonValue = WriteValue(ValueProperty, MapHelper.GetValuePtr(Idx), nullptr);
				check(JsonValue.IsValid());
				JsonValuesArray.Add(JsonValue);
			}
		}

		// maps can either be stored as $key, $value pairs or, if the keys can be string field, as a JSON object
		// check Filter we should use based on the first element
		const EJson KeyType = JsonKeysArray[0]->Type;
		if (KeyType == EJson::Object)
		{
			TArray<TSharedPtr<FJsonValue>> ResultArray;
			ResultArray.Reserve(MapHelper.Num());

			for (int32 Idx = 0; Idx < MapHelper.Num(); ++Idx)
			{
				if (MapHelper.IsValidIndex(Idx))
				{
					TSharedPtr<FJsonObject> ElementObject = MakeShared<FJsonObject>();
					ElementObject->SetField(TEXT("$key"), JsonKeysArray[Idx]);
					ElementObject->SetField(TEXT("$value"), JsonValuesArray[Idx]);

					ResultArray.Add(MakeShared<FJsonValueObject>(ElementObject));
				}
			}

			ResultValue = MakeShared<FJsonValueArray>(ResultArray);
		}
		else if (KeyType == EJson::Boolean ||
			KeyType == EJson::Number ||
			KeyType == EJson::String)
		{
			TSharedPtr<FJsonObject> ResultObject = MakeShared<FJsonObject>();

			for (int32 Idx = 0; Idx < MapHelper.Num(); ++Idx)
			{
				if (MapHelper.IsValidIndex(Idx))
				{
					FString KeyString;
					const bool bGetStringSuccess = JsonKeysArray[Idx]->TryGetString(KeyString);
					check(bGetStringSuccess);

					ResultObject->SetField(KeyString, JsonValuesArray[Idx]);
				}
			}

			ResultValue = MakeShared<FJsonValueObject>(ResultObject);
		}

		ensureMsgf(ResultValue.IsValid(), TEXT("Map key type is invalid."));
	}

	return ResultValue;
}

TSharedPtr<FJsonValue> FNativeAPIUtilities::WriteValue(const FProperty* Property, const void* DataPtr, const void* DefaultPtr)
{
	TSharedPtr<FJsonValue> ResultValue;
	/**if (DefaultPtr != nullptr && Property->Identical(DataPtr, DefaultPtr))
	{
		return ResultValue;
	}*/

	if (const FStrProperty* StrProperty = CastField<FStrProperty>(Property))
	{
		FString* Value = (FString*) DataPtr;
		ResultValue = MakeShared<FJsonValueString>(*Value);
	}
	else if (const FNameProperty* NameProperty = CastField<FNameProperty>(Property))
	{
		const FName* Value = (FName*) DataPtr;
		ResultValue = MakeShared<FJsonValueString>(Value->ToString());
	}
	else if (const FTextProperty* TextProperty = CastField<FTextProperty>(Property))
	{
		const FText* Value = (FText*) DataPtr;
		ResultValue = MakeShared<FJsonValueString>(Value->ToString());
	}
	else if (const FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
	{
		bool Value = BoolProperty->GetPropertyValue(DataPtr);
		ResultValue = MakeShared<FJsonValueBoolean>(Value);
	}
	else if (const FFloatProperty* FloatProperty = CastField<FFloatProperty>(Property))
	{
		float* Value = (float*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FDoubleProperty* DoubleProperty = CastField<FDoubleProperty>(Property))
	{
		double* Value = (double*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	} 
	else if (const FInt8Property* Int8Property = CastField<FInt8Property>(Property))
	{
		int8* Value = (int8*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FInt16Property* Int16Property = CastField<FInt16Property>(Property))
	{
		int16* Value = (int16*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FIntProperty* Int32Property = CastField<FIntProperty>(Property))
	{
		int32* Value = (int32*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FInt64Property* Int64Property = CastField<FInt64Property>(Property))
	{
		int64* Value = (int64*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FByteProperty* ByteProperty = CastField<FByteProperty>(Property))
	{
		uint8* Value = (uint8*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FUInt16Property* Uint16Property = CastField<FUInt16Property>(Property))
	{
		uint16* Value = (uint16*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FUInt32Property* Uint32Property = CastField<FUInt32Property>(Property))
	{
		uint32* Value = (uint32*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FUInt64Property* Uint64Property = CastField<FUInt64Property>(Property))
	{
		uint64* Value = (uint64*) DataPtr;
		ResultValue = MakeShared<FJsonValueNumber>(*Value);
	}
	else if (const FEnumProperty* EnumProperty = CastField<FEnumProperty>(Property))
	{
		const UEnum* Enum = EnumProperty->GetEnum();
		const int64 Value = EnumProperty->GetUnderlyingProperty()->GetSignedIntPropertyValue(DataPtr);
		const FName ValueName = Enum->GetNameByValue(Value);
		ResultValue = MakeShared<FJsonValueString>(ValueName.ToString());
	}
	else if (const FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(Property))
	{
		FString ObjectPath;
		ObjectProperty->ExportTextItem_Direct(ObjectPath, DataPtr, nullptr, nullptr, PPF_None, nullptr);
		ResultValue = MakeShared<FJsonValueString>(ObjectPath);
	}
	else if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property))
	{
		ResultValue = MakeShared<FJsonValueObject>(WriteStruct(StructProperty->Struct, DataPtr, DefaultPtr));
	}
	else if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
	{
		ResultValue = WriteArray(ArrayProperty, DataPtr);
	}
	else if (const FSetProperty* SetProperty = CastField<FSetProperty>(Property))
	{
		ResultValue = WriteSet(SetProperty, DataPtr);
	}
	else if (const FMapProperty* MapProperty = CastField<FMapProperty>(Property))
	{
		ResultValue = WriteMap(MapProperty, DataPtr);
	}

	ensureAlwaysMsgf(ResultValue.IsValid(), TEXT("Property type is unsupported: %s, type: %s"), *Property->GetPathName(), *Property->GetClass()->GetName());
	return ResultValue;
}

TSharedPtr<FJsonObject> FNativeAPIUtilities::WriteFunction(const UFunction* Function, const void* Defaults)
{
	const TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	
	// Default initialize a struct here if we weren't passed one. 
	// This is necessary because structs can contain default initializations, eg.:
	// struct Foo { float Bar = 5.0f; }
	// The Bar FProperty does not store this value itself, only the struct does.

	if (Defaults == nullptr)
	{
		TArray<uint8> TempDefaults;
		TempDefaults.AddZeroed(Function->GetStructureSize());
		Function->InitializeStruct(TempDefaults.GetData());

		Defaults = TempDefaults.GetData();
	}

	FStructOnScope FuncParams(Function);

	for (TFieldIterator<FProperty> It(Function); It; ++It)
	{
		const FProperty* Property = *It;

		const void* ValuePtr = Property->ContainerPtrToValuePtr<void>(FuncParams.GetStructMemory());
		const void* PropertyDefaultPtr = Property->ContainerPtrToValuePtr<void>(Defaults);

		TSharedPtr<FJsonValue> PropertyValue = WriteValue(Property, ValuePtr, PropertyDefaultPtr);
		
		if (PropertyValue.IsValid())
		{
			Json->SetField(Property->GetName(), PropertyValue);
		}
	}

	return Json;
}

TSharedPtr<FJsonObject> FNativeAPIUtilities::WriteStruct(const UStruct* Struct, const void* Instance, const void* Defaults) 
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("$type"), Struct->GetName());
	
	// Default initialize a struct here if we weren't passed one. 
	// This is necessary because structs can contain default initializations, eg.:
	// struct Foo { float Bar = 5.0f; }
	// The Bar FProperty does not store this value itself, only the struct does.

	if (Defaults == nullptr)
	{
		TArray<uint8> TempDefaults;
		TempDefaults.AddZeroed(Struct->GetStructureSize());
		Struct->InitializeStruct(TempDefaults.GetData());

		Defaults = TempDefaults.GetData();
	}
	
	bool bAnyWritten = false;

	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		const FProperty* Property = *It;

		bAnyWritten = true;
		
		const void* ValuePtr = Property->ContainerPtrToValuePtr<void>(Instance);
		const void* PropertyDefaultPtr = Property->ContainerPtrToValuePtr<void>(Defaults);

		TSharedPtr<FJsonValue> PropertyValue = WriteValue(Property, ValuePtr, PropertyDefaultPtr);
		if (PropertyValue.IsValid())
		{
			JsonObject->SetField(Property->GetName(), PropertyValue);
		}
	}

	ensureAlwaysMsgf(bAnyWritten, TEXT("Struct type has no properties to serialize: %s"), *Struct->GetName());

	return JsonObject;
}

/* 
 * This exists because of sparse class data that can exist for UObjects only, which is handled in ContainerPtrToValuePtr.
 */
TSharedPtr<FJsonObject> FNativeAPIUtilities::WriteUObject(const UClass* Class, const UObject* Instance) 
{
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("$type"), Class->GetName());

	const UObject* Defaults = Class->GetDefaultObject();

	bool bAnyWritten = false;

	for (TFieldIterator<FProperty> It(Class); It; ++It)
	{
		const FProperty* Property = *It;

		bAnyWritten = true;

		const void* ValuePtr = Property->ContainerPtrToValuePtr<void>(Instance);
		const void* PropertyDefaultPtr = Property->ContainerPtrToValuePtr<void>(Defaults);

		TSharedPtr<FJsonValue> PropertyValue = WriteValue(Property, ValuePtr, PropertyDefaultPtr);
		if (PropertyValue.IsValid())
		{
			JsonObject->SetField(Property->GetName(), PropertyValue);
		}
	}

	ensureAlwaysMsgf(bAnyWritten, TEXT("UObject type has no properties to serialize: %s"), *Class->GetName());

	return JsonObject;
}

bool FNativeAPIUtilities::ConvertNativeAPIJsonToPayload(const TSharedPtr<FJsonObject>& InJson,FNativeAPIPayload& OutPayload)
{
	check(InJson.IsValid())

	if(!IsNativeAPIJson(InJson))
	{
		return false;
	}

	// Step 1 : 确认该 NativeAPI Payload 的类型. 在整个 NativeAPI 任务中, ClassType 是必须确定的.
	{
		FString EntityClass;
		if(!InJson->TryGetStringField(NATIVE_API_ENTITY_CLASS_FIELD, EntityClass) || EntityClass.IsEmpty())
		{
			return false;
		}
		
		FSoftClassPath ClassPath;
		
		if(FPackageName::IsShortPackageName(EntityClass))
		// 如果这是一个短包名, 尝试转换为完整的包名. ( eg : BP_NativeAPI_C => /NativeAPI/BP_NativeAPI.BP_NativeAPI_C )
		{
#if !UE_BUILD_SHIPPING
			FTopLevelAssetPath ClassAsset;
			// todo : 注意蓝图类会出现该情况 => 在插件 A 和 B中同时存在两个名为 BP_Test 的蓝图. 该函数按 Pak 挂载点排序找到并返回第一个结果.
			// '/A/BP_Test.BP_Test_C'				'/B/BP_Test.BP_Test_C'
			// 这种不确定因素可能会导致在 FindClass 时返回一个错误的 UClass 对象.
			ClassAsset = UClass::TryConvertShortTypeNameToPathName<UStruct>(EntityClass, ELogVerbosity::Warning, TEXT("NativeAPIImpl"));
			
			GenericLOG(LogNativeAPI, Warning, TEXT("在处理 EntityClass 时, 检测到使用了短包名. 请修改为使用完整的类包名进行访问!"))

			ClassPath.SetPath(ClassAsset);
#endif
		}
		else
		{
			ClassPath.SetPath(EntityClass);
		}
		
		if(!ClassPath.IsAsset())
		{
			GenericLOG(LogNativeAPI, Error, TEXT("EntityClass 无法确定执行对象的类型!"));
			return false;
		}
		
		OutPayload.EntityClassPath = ClassPath;

		// Set Entity ...
		FString Entity;
		InJson->TryGetStringField(NATIVE_API_ENTITY_FIELD, Entity);
		OutPayload.Entity = Entity.IsEmpty() ? ClassPath.GetAssetFName() : FName(Entity);
	}

	// Step 2 : 我们在这一步至少要解析出 最少一个 "API_" Json对象, 否则这个消息没有任何意义.
	{
		TArray<FNativeAPITask> APITaskList;
		for(auto It = InJson->Values.CreateConstIterator(); It; ++It)
		{
			FString Key = It.Key();
			TSharedPtr<FJsonValue> Value = It.Value();
		
			if(IsNativeAPIFunctionName(*Key))
			{
				FName APIName = FName(Key);
				TSharedPtr<FJsonObject>* JsonObject;
				if(Value->TryGetObject(JsonObject) && JsonObject->IsValid())
				{
					FNativeAPITask NewTask;
					NewTask.FuncName = APIName;
					NewTask.ParamJson = *JsonObject;
					APITaskList.Add(NewTask);
				}
				else
				{
					// todo : @ChangQing -> Error !!!;
					GenericLOG(LogNativeAPI, Error, TEXT(" 'API_' 字段必须是  JsonObject 对象. "))
				}
			}
		}

		if(APITaskList.IsEmpty())
		{
			GenericLOG(LogNativeAPI, Error, TEXT("没有分析出任何有效的 NativeAPI 任务!"))
			return false;
		}

		OutPayload.TaskList = APITaskList;
	}
	
	// Step 3 : 解析 EntityPath, 如果存在的话.
	FString EntityPath;
	{
		if(InJson->TryGetStringField(NATIVE_API_ENTITY_PATH_FIELD, EntityPath) && !EntityPath.IsEmpty())
		{
			FSoftObjectPath SoftPath(EntityPath);
			
			if(!SoftPath.IsSubobject())
			{
				GenericLOG(LogNativeAPI, Warning, TEXT("invalid entity path : %s, entity path subobjectstring is can not empty"), *EntityPath);
				return false;
			}

#if WITH_EDITOR
			// 修复为编辑器 PIE 路径...
			SoftPath.FixupForPIE();
#endif

			// 顶级路径就是该对象所在的 UWorld.
			OutPayload.WorldPath = SoftPath.GetWithoutSubPath();
			OutPayload.EntityObjectPath = SoftPath;

			// check...
			if(!OutPayload.IsValidEntityPath())
			{
				GenericLOG(LogNativeAPI, Error, TEXT("EntityClass 存在字段, 但无法处理这个可执行对象路径!"));
				return false;
			}
		}
	}

	// Step 4 : 解析 World Path, 如果存在
	FString WorldPath;
	{
		if(InJson->TryGetStringField(NATIVE_API_WORLD_PATH_FIELD, WorldPath) && !WorldPath.IsEmpty())
		{
			FSoftObjectPath SoftPath(WorldPath);

			if(SoftPath.IsAsset())
			{
				if(!OutPayload.GetWorldPath().IsValid())
				{
					OutPayload.WorldPath = SoftPath;
				}
				else if(OutPayload.GetWorldPath() != WorldPath)
				{
					GenericLOG(LogNativeAPI, Error, TEXT("EntityPath 和 WorldPath 所在世界路径不一致!"))
					return false;
				}
			}
		}
	}
	
	return true;
}

#undef NATIVE_API_ENTITY_CLASS_FIELD
#undef NATIVE_API_ENTITY_PATH_FIELD
#undef NATIVE_API_ENTITY_FIELD
#undef NATIVE_API_PREFIX