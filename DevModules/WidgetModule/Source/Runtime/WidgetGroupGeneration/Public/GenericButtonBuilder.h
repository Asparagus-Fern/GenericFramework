// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ButtonType.h"
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
	UGenericButtonBuilder(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditDefaultsOnly, meta=(Categories="UI.Button"))
	FGameplayTag ButtonTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGenericButtonWidget> ButtonClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGenericButtonContainer> ButtonGroupClass;

	UPROPERTY(EditDefaultsOnly)
	FButtonParameter ButtonParameter;
};
