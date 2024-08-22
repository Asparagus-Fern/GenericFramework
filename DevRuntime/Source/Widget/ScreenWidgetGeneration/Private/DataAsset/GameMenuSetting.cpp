// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/GameMenuSetting.h"

#include "GameplayTagsManager.h"
#include "Debug/DebugType.h"
#include "UserWidget/Menu/MenuContainer.h"

#if WITH_EDITOR

void UGameMenuSetting::GenerateMenu()
{
	if (!IsValid(MenuTagTable))
	{
		NOTIFY(TEXT("MenuTagTable is NULL"))
		return;
	}

	if (!MenuTagTable->RowStruct->IsChildOf(FGameplayTagTableRow::StaticStruct()))
	{
		NOTIFY(TEXT("MenuTagTable is Not GameplayTag Table"))
		return;
	}

	Modify();

	GameplayTagContainer = FGameplayTagContainer();

	MenuTagTable->ForeachRow<FGameplayTagTableRow>
	("", [this](FName Key, const FGameplayTagTableRow& Value)
	 {
		 const FGameplayTag MenuTag = FGameplayTag::RequestGameplayTag(Value.Tag);
		 GameplayTagContainer.AddTag(MenuTag);

		 /* 跳过根节点 */
		 if (MenuTag == TAG_Menu)
		 {
			 return;
		 }

		 /* 不在UI.Menu子项下 */
		 if (!MenuTag.GetGameplayTagParents().HasTag(TAG_Menu))
		 {
			 return;
		 }

		 /* 跳过已存在MenuInfo */
		 if (MenuInfos.Contains(MenuTag))
		 {
			 return;
		 }

		 /* 添加新的MenuInfo */
		 FMenuInfo* NewMenuInfo = new FMenuInfo(MenuTag);
		 NewMenuInfo->MenuMainName = FText::FromString(Value.DevComment);
		 MenuInfos.Add(*NewMenuInfo);
	 }
	);

	NOTIFY(TEXT("Menu Generate Finish"))
}

#endif

bool UGameMenuSetting::GetMenuInfo(FGameplayTag InMenuTag, FMenuInfo& OutMenuInfo)
{
	for (auto& MenuInfo : MenuInfos)
	{
		if (MenuInfo.MenuTag == InMenuTag)
		{
			OutMenuInfo = MenuInfo;
			return true;
		}
	}

	return false;
}

TArray<FMenuInfo> UGameMenuSetting::GetMenuInfos(const TArray<FGameplayTag>& InMenuTags)
{
	TArray<FMenuInfo> OutMenuInfos;

	for (auto& MenuInfo : MenuInfos)
	{
		if (InMenuTags.Contains(MenuInfo.MenuTag))
		{
			OutMenuInfos.Add(MenuInfo);
		}
	}

	return OutMenuInfos;
}

TArray<FGameplayTag> UGameMenuSetting::GetChildMenuTags(const FGameplayTag InMenuTag, const bool bIsContainOriginal)
{
	TArray<FGameplayTag> OutMenuTags;
	if (bIsContainOriginal)
	{
		OutMenuTags.Add(InMenuTag);
	}

	TArray<FGameplayTag> ChildTags;
	UGameplayTagsManager::Get().RequestGameplayTagChildren(InMenuTag).GetGameplayTagArray(ChildTags);

	OutMenuTags.Append(ChildTags);
	return OutMenuTags;
}

TArray<FMenuInfo> UGameMenuSetting::GetChildMenuInfos(const FGameplayTag InMenuTag, const bool bIsContainOriginal)
{
	return GetMenuInfos(GetChildMenuTags(InMenuTag, bIsContainOriginal));
}

TArray<FGameplayTag> UGameMenuSetting::GetChildMenuTagsInDictionary(const FGameplayTag InMenuTag, const bool bIsContainOriginal)
{
	TArray<FGameplayTag> OutMenuTags;
	if (bIsContainOriginal)
	{
		OutMenuTags.Add(InMenuTag);
	}

	TArray<FGameplayTag> ChildTags;
	UGameplayTagsManager::Get().RequestGameplayTagChildrenInDictionary(InMenuTag).GetGameplayTagArray(ChildTags);

	OutMenuTags.Append(ChildTags);
	return OutMenuTags;
}

TArray<FMenuInfo> UGameMenuSetting::GetChildMenuInfosInDictionary(const FGameplayTag InMenuTag, const bool bIsContainOriginal)
{
	return GetMenuInfos(GetChildMenuTagsInDictionary(InMenuTag, bIsContainOriginal));
}

TArray<FGameplayTag> UGameMenuSetting::GetParentMenuTags(const FGameplayTag InMenuTag, const bool bIsContainOriginal)
{
	TArray<FGameplayTag> OutMenuTags;
	if (bIsContainOriginal)
	{
		OutMenuTags.Add(InMenuTag);
	}

	TArray<FGameplayTag> ChildTags;
	UGameplayTagsManager::Get().RequestGameplayTagParents(InMenuTag).GetGameplayTagArray(ChildTags);

	OutMenuTags.Append(ChildTags);
	return OutMenuTags;
}

TArray<FMenuInfo> UGameMenuSetting::GetParentMenuInfos(const FGameplayTag InMenuTag, const bool bIsContainOriginal)
{
	return GetMenuInfos(GetParentMenuTags(InMenuTag, bIsContainOriginal));
}

FGameplayTag UGameMenuSetting::GetDirectParentMenuTag(const FGameplayTag InMenuTag)
{
	return UGameplayTagsManager::Get().RequestGameplayTagDirectParent(InMenuTag);
}

bool UGameMenuSetting::GetDirectParentMenuInfo(const FGameplayTag InMenuTag, FMenuInfo& OutMenuInfo)
{
	return GetMenuInfo(GetDirectParentMenuTag(InMenuTag), OutMenuInfo);
}

FGameplayTag UGameMenuSetting::GetRootMenuTag() const
{
	return RootMenuTag.IsValid() ? RootMenuTag : (GameplayTagContainer.IsValid() ? GameplayTagContainer.First() : FGameplayTag::EmptyTag);
}

TArray<FMenuInfo> UGameMenuSetting::GetRootMenuInfos()
{
	return GetChildMenuInfos(GetRootMenuTag());
}
