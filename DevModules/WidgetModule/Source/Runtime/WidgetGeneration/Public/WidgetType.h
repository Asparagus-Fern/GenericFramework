// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/SlateWrapperTypes.h"
#include "Slate/WidgetTransform.h"
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


/**
 * 
 */
USTRUCT(BlueprintType)
struct FWidgetDescriptionParameter
{
	GENERATED_BODY()

public:
	FWidgetDescriptionParameter() { return; }

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Description")
	FText PrimaryName = FText::FromString("PrimaryName");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Description")
	FText SecondaryName = FText::FromString("SecondaryName");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Description")
	FText TooltipText;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FWidgetRenderParameter
{
	GENERATED_BODY()

public:
	FWidgetRenderParameter() { return; }

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Render")
	ESlateVisibility Visibility = ESlateVisibility::SelfHitTestInvisible;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Render")
	FVector2D RenderTransformPivot = FVector2D(0.5f, 0.5f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Render")
	FWidgetTransform RenderTransform;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FWidgetParameter
{
	GENERATED_BODY()

public:
	FWidgetParameter() { return; }

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWidgetDescriptionParameter DescriptionParameter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWidgetRenderParameter RenderParameter;
};
