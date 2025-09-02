// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GenericButtonStyle.generated.h"


/**
 * 
 */
UCLASS(Abstract, MinimalAPI, Blueprintable)
class UGenericButtonStyle : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush Normal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush Hovered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateBrush Pressed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor NormalForeground;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor HoveredForeground;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor PressedForeground;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateColor DisabledForeground;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FMargin NormalPadding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FMargin PressedPadding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateSound HoveredSlateSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSlateSound PressedSlateSound;
};

