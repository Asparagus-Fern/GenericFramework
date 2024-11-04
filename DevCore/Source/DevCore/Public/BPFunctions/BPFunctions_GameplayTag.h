// Fill out your copyright notice in the Description page of Project Settings.

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
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To GameplayTag(String)", CompactNodeTitle = "->", BlueprintAutocast))
	static FGameplayTag Conv_StringToGameplayTag(const FString& TagName);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To GameplayTag(Name)", CompactNodeTitle = "->", BlueprintAutocast))
	static FGameplayTag Conv_NameToGameplayTag(FName TagName);
};
