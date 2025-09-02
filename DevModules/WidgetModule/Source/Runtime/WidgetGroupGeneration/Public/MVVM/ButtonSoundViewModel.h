// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ButtonSoundViewModel.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew)
class WIDGETGROUPGENERATION_API UButtonSoundViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Hovered Sound Override"))
	FSlateSound HoveredSlateSoundOverride;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Pressed Sound Override"))
	FSlateSound PressedSlateSoundOverride;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Selected Hovered Sound Override"))
	FSlateSound SelectedHoveredSlateSoundOverride;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Selected Pressed Sound Override"))
	FSlateSound SelectedPressedSlateSoundOverride;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Locked Hovered Sound Override"))
	FSlateSound LockedHoveredSlateSoundOverride;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Locked Pressed Sound Override"))
	FSlateSound LockedPressedSlateSoundOverride;
};
