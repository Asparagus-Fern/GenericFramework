// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "PropertyType.generated.h"

PROPERTYSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogProperty, Log, All);

template <typename T>
struct ExtractFromTObjectPtr
{
	using Type = void;
};

template <typename T>
struct ExtractFromTObjectPtr<TObjectPtr<T>>
{
	using Type = T;
};

template <typename T>
struct ExtractFromRawPtr
{
	using Type = void;
};

template <typename T>
struct ExtractFromRawPtr<T*>
{
	using Type = T;
};

template <typename T>
struct TMVVMRegisterTypeExtractor
{
private:
	using TObjectPtrType = typename ExtractFromTObjectPtr<T>::Type;
	using RawPtrType = typename ExtractFromRawPtr<T>::Type;

public:
	using Type = typename std::conditional<
		!std::is_same_v<TObjectPtrType, void>,
		TObjectPtrType,
		RawPtrType
	>::type;
};

#define MVVM_REGISTRY(Handle, ViewModel, Value, FunctionName) \
{ \
using ViewModelClass = typename TMVVMRegisterTypeExtractor<decltype(ViewModel)>::Type; \
Handle = ViewModel->AddFieldValueChangedDelegate(ViewModelClass::FFieldNotificationClassDescriptor::Value,ViewModelClass::FFieldValueChangedDelegate::CreateUObject(this,&ThisClass::FunctionName)); \
FunctionName(this,ViewModelClass::FFieldNotificationClassDescriptor::Value); \
}

#define MVVM_REGISTRY_ONLY(Handle, ViewModel, Value, FunctionName) \
{ \
using ViewModelClass = typename TMVVMRegisterTypeExtractor<decltype(ViewModel)>::Type; \
Handle = ViewModel->AddFieldValueChangedDelegate(ViewModelClass::FFieldNotificationClassDescriptor::Value,ViewModelClass::FFieldValueChangedDelegate::CreateUObject(this,&ThisClass::FunctionName)); \
}

#define MVVM_UNREGISTRY(Handle,ViewModel, Value) \
{ \
using ViewModelClass = typename TMVVMRegisterTypeExtractor<decltype(ViewModel)>::Type; \
ViewModel->RemoveFieldValueChangedDelegate(ViewModelClass::FFieldNotificationClassDescriptor::Value, Handle); \
}
