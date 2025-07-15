// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_GameplayTag.h"

#include "GameplayTagsManager.h"

FGameplayTagContainer UBPFunctions_GameplayTag::GetGameplayTagChildren(FGameplayTag InTag, bool bIsContainOriginal)
{
	FGameplayTagContainer GameplayTagContainer = FGameplayTagContainer();
	const FGameplayTagContainer Children = UGameplayTagsManager::Get().RequestGameplayTagChildren(InTag);

	if (bIsContainOriginal)
	{
		GameplayTagContainer.AddTagFast(InTag);
	}

	for (const auto& Tag : Children.GetGameplayTagArray())
	{
		GameplayTagContainer.AddTagFast(Tag);
	}

	return GameplayTagContainer;
}

FGameplayTagContainer UBPFunctions_GameplayTag::GetDirectGameplayTagChildren(FGameplayTag InTag, bool bIsContainOriginal)
{
	FGameplayTagContainer GameplayTagContainer = FGameplayTagContainer();
	const FGameplayTagContainer Children = UGameplayTagsManager::Get().RequestGameplayTagChildren(InTag);

	if (bIsContainOriginal)
	{
		GameplayTagContainer.AddTag(InTag);
	}

	for (const auto& Tag : Children.GetGameplayTagArray())
	{
		if (Tag.RequestDirectParent() == InTag)
		{
			GameplayTagContainer.AddTag(Tag);
		}
	}

	return GameplayTagContainer;
}

FGameplayTagContainer UBPFunctions_GameplayTag::GetGameplayTagParents(FGameplayTag InTag, bool bIsContainOriginal)
{
	FGameplayTagContainer Parent = InTag.GetGameplayTagParents();

	if (!bIsContainOriginal)
	{
		Parent.RemoveTag(InTag);
	}

	return Parent;
}

FGameplayTag UBPFunctions_GameplayTag::GetDirectGameplayTagParent(FGameplayTag InTag)
{
	return InTag.RequestDirectParent();
}

FString UBPFunctions_GameplayTag::Conv_GameplayTagToString(FGameplayTag InTag)
{
	return InTag.ToString();
}

FGameplayTag UBPFunctions_GameplayTag::Conv_StringToGameplayTag(const FString& TagName)
{
	return UGameplayTagsManager::Get().RequestGameplayTag(FName(TagName));
}

FName UBPFunctions_GameplayTag::Conv_GameplayTagToName(FGameplayTag InTag)
{
	return InTag.GetTagName();
}

FGameplayTag UBPFunctions_GameplayTag::Conv_NameToGameplayTag(const FName TagName)
{
	return UGameplayTagsManager::Get().RequestGameplayTag(TagName);
}
