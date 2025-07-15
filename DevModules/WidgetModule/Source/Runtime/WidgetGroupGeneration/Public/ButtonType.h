// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "ButtonType.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FButtonSelectionParameter
{
	GENERATED_BODY()

public:
	FButtonSelectionParameter() { return; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection")
	bool bSelectable = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta = (EditCondition = "bSelectable"))
	bool bToggleable = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta=(EditCondition = "bSelectable"))
	bool bDefaultSelected = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta = ( EditCondition = "bSelectable"))
	bool bShouldSelectUponReceivingFocus = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta = (EditCondition = "bSelectable"))
	bool bInteractableWhenSelected = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta = (EditCondition = "bSelectable"))
	bool bTriggerClickedAfterSelection = false;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FButtonSoundParameter
{
	GENERATED_BODY()

public:
	FButtonSoundParameter() { return; }

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Pressed Sound Override"))
	FSlateSound PressedSlateSoundOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Hovered Sound Override"))
	FSlateSound HoveredSlateSoundOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Selected Pressed Sound Override"))
	FSlateSound SelectedPressedSlateSoundOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Selected Hovered Sound Override"))
	FSlateSound SelectedHoveredSlateSoundOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Locked Pressed Sound Override"))
	FSlateSound LockedPressedSlateSoundOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Locked Hovered Sound Override"))
	FSlateSound LockedHoveredSlateSoundOverride;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FButtonInputParameter
{
	GENERATED_BODY()

public:
	FButtonInputParameter() { return; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonClickMethod::Type> ClickMethod = EButtonClickMethod::Type::DownAndUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonTouchMethod::Type> TouchMethod = EButtonTouchMethod::Type::DownAndUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonPressMethod::Type> PressMethod = EButtonPressMethod::Type::DownAndUp;
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FButtonParameter : public FWidgetParameter
{
	GENERATED_BODY()

public:
	FButtonParameter() { return; }

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FButtonSelectionParameter SelectionParameter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FButtonSoundParameter SoundParameter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FButtonInputParameter InputParameter;
};
