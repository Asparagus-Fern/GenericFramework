// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GameplayTag.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_GameplayTag : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Gets a Tag Container Containing The All Tags In The Hierarchy That Are Children of This Tag. */
	UFUNCTION(BlueprintPure, Category="Function Library | GameplayTag")
	static FGameplayTagContainer GetGameplayTagChildren(FGameplayTag InTag, bool bIsContainOriginal = false);

	/* Gets a Tag Container Containing The All Tags In The Hierarchy That Are Direct Children of This Tag. */
	UFUNCTION(BlueprintPure, Category="Function Library | GameplayTag")
	static FGameplayTagContainer GetDirectGameplayTagChildren(FGameplayTag InTag, bool bIsContainOriginal = false);

	/* Gets a Tag Container Containing The All Tags In The Hierarchy That Are Parent of This Tag. */
	UFUNCTION(BlueprintPure, Category="Function Library | GameplayTag")
	static FGameplayTagContainer GetGameplayTagParents(FGameplayTag InTag, bool bIsContainOriginal = false);

	/* Gets a Tag Container Containing The All Tags In The Hierarchy That Are Direct Parent of This Tag. */
	UFUNCTION(BlueprintPure, Category="Function Library | GameplayTag")
	static FGameplayTag GetDirectGameplayTagParent(FGameplayTag InTag);

public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String(FGameplayTag)", CompactNodeTitle = "->", BlueprintAutocast), Category="Function Library | GameplayTag")
	static FString Conv_GameplayTagToString(FGameplayTag InTag);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To GameplayTag(String)", CompactNodeTitle = "->", BlueprintAutocast), Category="Function Library | GameplayTag")
	static FGameplayTag Conv_StringToGameplayTag(const FString& TagName);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Name(FGameplayTag)", CompactNodeTitle = "->", BlueprintAutocast), Category="Function Library | GameplayTag")
	static FName Conv_GameplayTagToName(FGameplayTag InTag);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To GameplayTag(Name)", CompactNodeTitle = "->", BlueprintAutocast), Category="Function Library | GameplayTag")
	static FGameplayTag Conv_NameToGameplayTag(FName TagName);
};
