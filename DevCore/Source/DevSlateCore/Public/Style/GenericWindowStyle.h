// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GenericWindowStyle.generated.h"

class UGenericTextBlockStyle;
class UGenericButtonStyle;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI, Blueprintable)
class UGenericWindowStyle : public UObject
{
	GENERATED_BODY()

public:
	DEVSLATECORE_API void GetWindowStyle(FWindowStyle& OutWindowStyle) const;

public:
	/* Style used to draw the window minimize button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericButtonStyle> MinimizeButtonStyleClass;

	/* Style used to draw the window maximize button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericButtonStyle> MaximizeButtonStyle;

	/* Style used to draw the window restore button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericButtonStyle> RestoreButtonStyle;

	/* Style used to draw the window close button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericButtonStyle> CloseButtonStyle;

	/* Style used to draw the window title text */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericTextBlockStyle> TitleTextStyle;

	/* Brush used to draw the window title area when the window is active */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush ActiveTitleBrush;

	/* Brush used to draw the window title area when the window is inactive */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush InactiveTitleBrush;

	/* Brush used to draw the window title area when the window is flashing */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush FlashTitleBrush;

	/* Color used to draw the window background */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor BackgroundColor = FLinearColor::White;

	/* Brush used to draw the window outline */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush OutlineBrush;

	/* Color used to draw the window outline */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor OutlineColor = FLinearColor::White;

	/* Brush used to draw the window border */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush BorderBrush;

	/* Color used to draw the window border */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor BorderColor = FLinearColor::White;

	/* Brush used to draw the window background */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush BackgroundBrush;

	/* Brush used to draw the background of child windows */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush ChildBackgroundBrush;

	/* Window corner rounding.  If this value is <= 0 no rounding will occur.Used for regular, non-maximized windows only */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CornerRadius = 5;

	/* Window corner rounding.  If this value is <= 0 no rounding will occur.Used for regular, non-maximized windows only */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FMargin BorderPadding;
};
