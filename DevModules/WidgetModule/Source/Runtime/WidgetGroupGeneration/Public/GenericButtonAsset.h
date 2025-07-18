// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GenericButtonAsset.generated.h"

class UGenericButtonContainer;
class UGenericButtonWidget;
class UGenericButtonBuilder;

/**
 * 
 */
UCLASS()
class WIDGETGROUPGENERATION_API UGenericButtonAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Button"))
	FGameplayTag RootButtonTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> ButtonTable = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGenericButtonWidget> DefaultButtonClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGenericButtonContainer> DefaultButtonGroupClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta = (TitleProperty = "ButtonTag"))
	TArray<TObjectPtr<UGenericButtonBuilder>> ButtonBuilders;

public:
#if WITH_EDITOR
	UFUNCTION(CallInEditor)
	void GenerateButtons();

	UFUNCTION(CallInEditor)
	void ClearButtons();
#endif

protected:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	FGameplayTagContainer GameplayTagContainer;
#endif

protected:
	bool IsContainButtonTag(FGameplayTag InButtonTag);
};
