// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericButtonWidget.h"
#include "Generic/GenericObject.h"
#include "GenericButtonBuilder.generated.h"

class UGenericButtonContainer;
class UGenericButtonWidget;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericButtonBuilder : public UGenericObject
{
	GENERATED_BODY()

public:
	WIDGETGROUPGENERATION_API UGenericButtonBuilder(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditDefaultsOnly, meta=(Categories="UI.Button"))
	FGameplayTag ButtonTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGenericButtonWidget> ButtonClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGenericButtonContainer> ButtonGroupClass;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TObjectPtr<UButtonSelectionViewModel> ButtonSelectionViewModel = nullptr;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TObjectPtr<UButtonInputViewModel> ButtonInputViewModel = nullptr;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TObjectPtr<UButtonSoundViewModel> ButtonSoundViewModel = nullptr;
};
