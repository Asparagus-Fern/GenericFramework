// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericButtonBuilder.h"
#include "Generic/GenericObject.h"
#include "GenericButtonBuilderSetting.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, Blueprintable, EditInlineNew)
class UGenericButtonBuilderSetting : public UGenericObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Button"))
	FGameplayTag ButtonTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DevComment;

	/* Giving a Builder Class To Generate Custom Data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGenericButtonBuilder> BuilderClass = UGenericButtonBuilder::StaticClass();
};
