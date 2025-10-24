// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GenericTextBlockStyle.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI, Blueprintable)
class UGenericTextBlockStyle : public UObject
{
	GENERATED_BODY()

public:
	DEVSLATECORE_API void GetTextBlockStyle(FTextBlockStyle& OutTextBlockStyle) const;

public:
	/* Font family and size to be used when displaying this text. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateFontInfo Font;

	/* The color and opacity of this text */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor ColorAndOpacity;

	/* How much should the shadow be offset? An offset of 0 implies no shadow */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDeprecateSlateVector2D ShadowOffset;

	/* The color and opacity of the shadow */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor ShadowColorAndOpacity;

	/* The background color of selected text */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor SelectedBackgroundColor;

	/* The color of highlighted text */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor HighlightColor;

	/* The shape of highlighted text */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush HighlightShape;

	/* The brush used to draw an strike through the text (if any) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush StrikeBrush;

	/* The brush used to draw an underline under the text (if any) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush UnderlineBrush;

	/* The Text Transform Policy (defaults to None) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETextTransformPolicy TransformPolicy;

	/* Determines what happens to text that is clipped and doesn't fit within the clip rect of a text widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ETextOverflowPolicy OverflowPolicy;
};
