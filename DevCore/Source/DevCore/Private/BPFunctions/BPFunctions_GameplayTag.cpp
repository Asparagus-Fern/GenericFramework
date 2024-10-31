// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_GameplayTag.h"

#include "GameplayTagsManager.h"

FGameplayTag UBPFunctions_GameplayTag::Conv_StringToGameplayTag(const FString& TagName)
{
	return UGameplayTagsManager::Get().RequestGameplayTag(FName(TagName));
}

FGameplayTag UBPFunctions_GameplayTag::Conv_NameToGameplayTag(const FName TagName)
{
	return UGameplayTagsManager::Get().RequestGameplayTag(TagName);
}
