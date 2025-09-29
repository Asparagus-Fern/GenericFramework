// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GenericButtonAsset.generated.h"

class UGenericButtonBuilderSettingAsset;
class UGenericButtonBuilder;

/**
 * Store Button Builder Data
 */
UCLASS(MinimalAPI)
class UGenericButtonAsset : public UDataAsset
{
	GENERATED_UCLASS_BODY()

public:
	/* Builder Settings Determines Which Builder Class To Generate */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UGenericButtonBuilderSettingAsset> ButtonBuilderSetting = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta = (TitleProperty = "ButtonTag"))
	TArray<TObjectPtr<UGenericButtonBuilder>> ButtonBuilders;

public:
	bool IsContainButtonTag(FGameplayTag InButtonTag);

#if WITH_EDITOR
	UFUNCTION(CallInEditor, DisplayName="Generate Buttons")
	void GenerateButtons();
#endif

	WIDGETGROUPGENERATION_API FGameplayTag GetRootButtonTag() const;
};
