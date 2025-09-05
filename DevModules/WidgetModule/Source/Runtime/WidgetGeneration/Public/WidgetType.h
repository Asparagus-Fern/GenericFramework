// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/SlateWrapperTypes.h"
#include "Slate/WidgetTransform.h"
#include "WidgetType.generated.h"

class UGameplayTagSlot;
class UGenericWidget;

WIDGETGENERATION_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogUI, Log, All);

DECLARE_DELEGATE_OneParam(FOnWidgetActiveStateChanged, UGenericWidget*);

/**
 * 
 */
USTRUCT()
struct FHandleWidgetParameter
{
	GENERATED_BODY()

public:
	FHandleWidgetParameter() { return; }
	virtual ~FHandleWidgetParameter() = default;
	virtual bool IsValid() const { return (bool)WidgetToHandle; }

	bool operator==(const FHandleWidgetParameter& Other) const { return WidgetToHandle == Other.WidgetToHandle; }
	bool operator==(const UGenericWidget* Other) const { return WidgetToHandle == Other; }
	bool operator!=(const FHandleWidgetParameter& Other) const { return !(*this == Other); }
	bool operator!=(const UGenericWidget* Other) const { return !(*this == Other); }

public:
	UPROPERTY()
	FGameplayTag SlotTag;

	UPROPERTY()
	TObjectPtr<UGameplayTagSlot> Slot = nullptr;

	UPROPERTY()
	TObjectPtr<UGenericWidget> WidgetToHandle = nullptr;

	FOnWidgetActiveStateChanged OnFinish;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FOpenWidgetParameter : public FHandleWidgetParameter
{
	GENERATED_BODY()

public:
	FOpenWidgetParameter() : FHandleWidgetParameter() { return; }
	bool NeedDestroyOldWidget() const { return (bool)WidgetToRemove; }

public:
	UPROPERTY()
	bool bOpenResult = false;

	UPROPERTY()
	TObjectPtr<UGenericWidget> WidgetToRemove = nullptr;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FCloseWidgetParameter : public FHandleWidgetParameter
{
	GENERATED_BODY()

public:
	FCloseWidgetParameter() : FHandleWidgetParameter() { return; }

public:
	UPROPERTY()
	bool bMarkAsGarbage = true;
};


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

#define REGISTER_MVVM_PROPERTY(ViewModel, Value, FunctionName, CallFunction) \
{ \
	if(ViewModel) \
	{ \
		using ViewModelClass = typename TMVVMRegisterTypeExtractor<decltype(ViewModel)>::Type; \
		ViewModelClass* ViewModelRef = ViewModel; \
		ViewModel->AddFieldValueChangedDelegate \
		( \
			ViewModelClass::FFieldNotificationClassDescriptor::Value, \
			ViewModelClass::FFieldValueChangedDelegate::CreateLambda \
			( \
				[this, ViewModelRef](UObject* InObject, UE::FieldNotification::FFieldId InFieldId) \
				{ \
					FunctionName(ViewModelRef->Value); \
				} \
			) \
		); \
		if(CallFunction) \
		{ \
			FunctionName(ViewModel->Value); \
		} \
	} \
}

#define REGISTER_MVVM_PROPERTY_LAMBDA(ViewModel, Value, Lambda, CallFunction) \
{ \
	if(ViewModel) \
	{ \
		using ViewModelClass = typename TMVVMRegisterTypeExtractor<decltype(ViewModel)>::Type; \
		ViewModelClass* ViewModelRef = ViewModel; \
		ViewModel->AddFieldValueChangedDelegate \
		( \
			ViewModelClass::FFieldNotificationClassDescriptor::Value, \
			ViewModelClass::FFieldValueChangedDelegate::CreateLambda \
			( \
				[ViewModelRef, Lambda](UObject* InObject, UE::FieldNotification::FFieldId InFieldId) \
				{ \
					Lambda(ViewModelRef->Value); \
				} \
			) \
		); \
		if(CallFunction) \
		{ \
			Lambda(ViewModel->Value); \
		} \
	} \
}

#define UNREGISTER_MVVM_PROPERTY(ViewModel) \
	if(ViewModel) \
	{ \
		ViewModel->RemoveAllFieldValueChangedDelegates(this); \
	}
