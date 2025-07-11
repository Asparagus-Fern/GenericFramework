// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "WidgetType.generated.h"

class UGameplayTagSlot;
class UGenericWidget;

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
	virtual bool IsValid() const { return SlotTag.IsValid() && (bool)WidgetToHandle && Slot; }

	bool operator==(const FHandleWidgetParameter& Other) const { return WidgetToHandle == Other.WidgetToHandle; }
	bool operator!=(const FHandleWidgetParameter& Other) const { return !(*this == Other); }

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
	virtual bool IsValid() const override { return bAddToViewport ? (bool)WidgetToHandle : Super::IsValid(); }

public:
	UPROPERTY()
	bool bAddToViewport = false;

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
