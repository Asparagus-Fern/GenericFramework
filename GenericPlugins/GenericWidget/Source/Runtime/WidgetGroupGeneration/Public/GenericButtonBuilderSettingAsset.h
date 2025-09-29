// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GenericButtonBuilderSettingAsset.generated.h"

class UGenericButtonBuilderSetting;

/**
 * Determines Which Builder Class To Generate In Button Asset
 */
UCLASS(MinimalAPI)
class UGenericButtonBuilderSettingAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	bool IsContainButtonTag(FGameplayTag InButtonTag);

#if WITH_EDITOR
	UFUNCTION(CallInEditor, DisplayName="Generate Settings")
	void GenerateBuilderSetting();
#endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Button"))
	FGameplayTag RootButtonTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> ButtonTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta = (TitleProperty = "ButtonTag"))
	TArray<TObjectPtr<UGenericButtonBuilderSetting>> GenericButtonBuilderSettings;
};
