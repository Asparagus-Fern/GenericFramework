// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Components/SlateWrapperTypes.h"
#include "Slate/WidgetTransform.h"
#include "WidgetType.generated.h"

class UGameplayTagSlot;
class UGenericWidget;

WIDGETGENERATION_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogUI, Log, All);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Game);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Popup);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Test);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Game_MainMenu);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Game_EscMenu);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Game_StartGame);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Game_FindSessions);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Game_Settings);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Game_About);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Popup_Dialog);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_GameHUD_Popup_Notify);

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

/**
 * Fast Binding Function To View Model
 * @param ViewModel The View Model To Bind
 * @param Value The View Model Value To Bind
 * @param FunctionName The Function To Bind
 * @param CallFunction If True, Will Call Once When Binding Finish
 */
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

/**
 * Remove All View Model Binding
 * @param ViewModel The View Model To Remove Binding
 */
#define UNREGISTER_MVVM_PROPERTY(ViewModel) \
	if(ViewModel) \
	{ \
		ViewModel->RemoveAllFieldValueChangedDelegates(this); \
	}

/** Enumeration to specify different window types for SWindows */
UENUM(BlueprintType)
enum class EWindowTypeBP: uint8
{
	/* Value indicating that this is a standard, general-purpose window */
	Normal,
	/* Value indicating that this is a window used for a popup menu */
	Menu,
	/* Value indicating that this is a window used for a tooltip */
	ToolTip,
	/* Value indicating that this is a window used for a notification toast */
	Notification,
	/* Value indicating that this is a window used for a cursor decorator */
	CursorDecorator,
	/* Value indicating that this is a game window */
	GameWindow
};

inline EWindowType ConvertToWindowType(const EWindowTypeBP EnumBP)
{
	switch (EnumBP)
	{
	case EWindowTypeBP::Normal:
		return EWindowType::Normal;
	case EWindowTypeBP::Menu:
		return EWindowType::Menu;
	case EWindowTypeBP::ToolTip:
		return EWindowType::ToolTip;
	case EWindowTypeBP::Notification:
		return EWindowType::Notification;
	case EWindowTypeBP::CursorDecorator:
		return EWindowType::CursorDecorator;
	case EWindowTypeBP::GameWindow:
		return EWindowType::GameWindow;
	}
	return EWindowType::Normal;
}

inline EWindowTypeBP ConvertToWindowTypeBP(const EWindowType Enum)
{
	switch (Enum)
	{
	case EWindowType::Normal:
		return EWindowTypeBP::Normal;
	case EWindowType::Menu:
		return EWindowTypeBP::Menu;
	case EWindowType::ToolTip:
		return EWindowTypeBP::ToolTip;
	case EWindowType::Notification:
		return EWindowTypeBP::Notification;
	case EWindowType::CursorDecorator:
		return EWindowTypeBP::CursorDecorator;
	case EWindowType::GameWindow:
		return EWindowTypeBP::GameWindow;
	}
	return EWindowTypeBP::Normal;
}

/** Enum to describe how to auto-center an SWindow */
UENUM(BlueprintType)
enum class EAutoCenterBP : uint8
{
	/* Don't auto-center the window */
	None,
	/* Auto-center the window on the primary work area */
	PrimaryWorkArea,
	/* Auto-center the window on the preferred work area, determined using GetPreferredWorkArea() */
	PreferredWorkArea,
};

inline EAutoCenter ConvertToAutoCenter(const EAutoCenterBP EnumBP)
{
	switch (EnumBP)
	{
	case EAutoCenterBP::None:
		return EAutoCenter::None;
	case EAutoCenterBP::PrimaryWorkArea:
		return EAutoCenter::PrimaryWorkArea;
	case EAutoCenterBP::PreferredWorkArea:
		return EAutoCenter::PreferredWorkArea;
	}
	return EAutoCenter::None;
}

inline EAutoCenterBP ConvertToAutoCenterBP(const EAutoCenter Enum)
{
	switch (Enum)
	{
	case EAutoCenter::None:
		return EAutoCenterBP::None;
	case EAutoCenter::PrimaryWorkArea:
		return EAutoCenterBP::PrimaryWorkArea;
	case EAutoCenter::PreferredWorkArea:
		return EAutoCenterBP::PreferredWorkArea;
	}
	return EAutoCenterBP::None;
}

/** Enum to describe how windows are sized */
UENUM(BlueprintType)
enum class ESizingRuleBP : uint8
{
	/* The windows size fixed and cannot be resized */
	FixedSize,
	/* The window size is computed from its content and cannot be resized by users */
	Autosized,
	/* The window can be resized by users */
	UserSized,
};

inline ESizingRule ConvertToSizingRule(const ESizingRuleBP EnumBP)
{
	switch (EnumBP)
	{
	case ESizingRuleBP::FixedSize:
		return ESizingRule::FixedSize;
	case ESizingRuleBP::Autosized:
		return ESizingRule::Autosized;
	case ESizingRuleBP::UserSized:
		return ESizingRule::UserSized;
	}
	return ESizingRule::Autosized;
}

inline ESizingRuleBP ConvertToSizingRuleBP(const ESizingRule Enum)
{
	switch (Enum)
	{
	case ESizingRule::FixedSize:
		return ESizingRuleBP::FixedSize;
	case ESizingRule::Autosized:
		return ESizingRuleBP::Autosized;
	case ESizingRule::UserSized:
		return ESizingRuleBP::UserSized;
	}
	return ESizingRuleBP::Autosized;
}

/** Enumeration to specify different transparency options for SWindows */
UENUM(BlueprintType)
enum class EWindowTransparencyBP : uint8
{
	/** Value indicating that a window does not support transparency */
	None,
	/** Value indicating that a window supports transparency at the window level (one opacity applies to the entire window) */
	PerWindow,
	/** Value indicating that a window supports per-pixel alpha blended transparency */
	PerPixel,
};

inline EWindowTransparency ConvertToWindowTransparency(const EWindowTransparencyBP EnumBP)
{
	switch (EnumBP)
	{
	case EWindowTransparencyBP::None:
		return EWindowTransparency::None;
	case EWindowTransparencyBP::PerWindow:
		return EWindowTransparency::PerWindow;
	case EWindowTransparencyBP::PerPixel:
		return EWindowTransparency::PerPixel;
	}
	return EWindowTransparency::None;
}

inline EWindowTransparencyBP ConvertToWindowTransparencyBP(const EWindowTransparency Enum)
{
	switch (Enum)
	{
	case EWindowTransparency::None:
		return EWindowTransparencyBP::None;
	case EWindowTransparency::PerWindow:
		return EWindowTransparencyBP::PerWindow;
	case EWindowTransparency::PerPixel:
		return EWindowTransparencyBP::PerPixel;
	}
	return EWindowTransparencyBP::None;
}

/** Enumeration to specify whether the window gets activated upon showing it */
UENUM(BlueprintType)
enum class EWindowActivationPolicyBP : uint8
{
	/** Value indicating that a window never activates when it is shown */
	Never,
	/** Value indicating that a window always activates when it is shown */
	Always,
	/** Value indicating that a window only activates when it is first shown */
	FirstShown
};

inline EWindowActivationPolicy ConvertToWindowActivationPolicy(const EWindowActivationPolicyBP EnumBP)
{
	switch (EnumBP)
	{
	case EWindowActivationPolicyBP::Never:
		return EWindowActivationPolicy::Always;
	case EWindowActivationPolicyBP::Always:
		return EWindowActivationPolicy::FirstShown;
	case EWindowActivationPolicyBP::FirstShown:
		return EWindowActivationPolicy::FirstShown;
	}
	return EWindowActivationPolicy::Never;
}

inline EWindowActivationPolicyBP ConvertToWindowActivationPolicyBP(const EWindowActivationPolicy Enum)
{
	switch (Enum)
	{
	case EWindowActivationPolicy::Never:
		return EWindowActivationPolicyBP::Never;
	case EWindowActivationPolicy::Always:
		return EWindowActivationPolicyBP::Always;
	case EWindowActivationPolicy::FirstShown:
		return EWindowActivationPolicyBP::FirstShown;
	}
	return EWindowActivationPolicyBP::Never;
}
