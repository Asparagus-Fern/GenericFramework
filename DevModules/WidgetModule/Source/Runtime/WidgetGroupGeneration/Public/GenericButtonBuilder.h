// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericButtonWidget.h"
#include "Generic/GenericObject.h"
#include "GenericButtonBuilder.generated.h"

class UButtonGroupViewModel;
class UGenericButtonContainer;
class UGenericButtonWidget;

/**
 * 
 */
UCLASS(MinimalAPI, EditInlineNew)
class UGenericButtonBuilder : public UGenericObject
{
	GENERATED_BODY()

public:
	WIDGETGROUPGENERATION_API UGenericButtonBuilder(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="UI.Button"))
	FGameplayTag ButtonTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericButtonWidget> ButtonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericButtonContainer> ButtonContainerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGenericButtonGroup> ButtonGroupClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TObjectPtr<UWidgetDescriptionViewModel> WidgetDescriptionViewModel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TObjectPtr<UWidgetRenderViewModel> WidgetRenderViewModel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TObjectPtr<UButtonSelectionViewModel> ButtonSelectionViewModel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TObjectPtr<UButtonInputViewModel> ButtonInputViewModel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TObjectPtr<UButtonSoundViewModel> ButtonSoundViewModel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TObjectPtr<UButtonGroupViewModel> ButtonGroupViewModel = nullptr;
};
