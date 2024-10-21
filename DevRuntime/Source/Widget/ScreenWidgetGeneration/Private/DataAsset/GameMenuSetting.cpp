// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/GameMenuSetting.h"

#include "GameplayTagsManager.h"
#include "Debug/DebugType.h"
#include "UserWidget/Menu/MenuContainer.h"
#include "UserWidget/Menu/MenuStyle.h"

#if WITH_EDITOR

void UGameMenuSetting::Generate()
{
	if (!IsValid(MenuTagTable))
	{
		DNOTIFY(TEXT("MenuTagTable is NULL"))
		return;
	}

	if (!MenuTagTable->RowStruct->IsChildOf(FGameplayTagTableRow::StaticStruct()))
	{
		DNOTIFY(TEXT("MenuTagTable is Not GameplayTag Table"))
		return;
	}

	Modify();

	GameplayTagContainer = FGameplayTagContainer();

	bool bConstructMenuContainer = MenuInfos.IsEmpty() && MenuContainerInfos.IsEmpty();

	MenuTagTable->ForeachRow<FGameplayTagTableRow>
	("", [this, bConstructMenuContainer](FName Key, const FGameplayTagTableRow& Value)
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

		 if (bConstructMenuContainer)
		 {
			 for (auto& MenuContainerInfo : MenuContainerInfos)
			 {
				 if (MenuContainerInfo.OwnerTag == MenuTag.RequestDirectParent())
				 {
					 MenuContainerInfo.MenuTags.Add(MenuTag);
					 return;
				 }
			 }

			 FMenuContainerInfo* MenuContainerInfo = new FMenuContainerInfo(MenuTag.RequestDirectParent());
			 MenuContainerInfo->MenuTags.Add(MenuTag);
			 MenuContainerInfos.Add(*MenuContainerInfo);
		 }
	 }
	);

	DNOTIFY(TEXT("Menu Generate Finish"))
}

#endif

bool UGameMenuSetting::CheckIsValidMenuTag(const FGameplayTag InMenuTag)
{
	/* 检查标签是否有效 */
	if (!InMenuTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("MenuTag Is InValid"))
		return false;
	}

	/* 检查样式是否有效 */
	FMenuInfo MenuInfo;
	if (GetMenuInfo(InMenuTag, MenuInfo))
	{
		if (!MenuInfo.StyleClass && !IsValid(MenuInfo.Style))
		{
			DLOG(DLogUI, Error, TEXT("Menu Style Is InValid"))
			return false;
		}
	}
	else
	{
		DLOG(DLogUI, Error, TEXT("Fail To GetMenuInfo"))
		return false;
	}

	/* 检查容器是否有效 */
	FMenuContainerInfo MenuContainerInfo;
	if (GetMenuContainerInfo(InMenuTag, MenuContainerInfo))
	{
		if (!MenuContainerInfo.ContainerClass && !IsValid(MenuContainerInfo.Container))
		{
			DLOG(DLogUI, Error, TEXT("Menu Container Is InValid"))
			return false;
		}
	}
	else
	{
		DLOG(DLogUI, Error, TEXT("Fail To GetMenuContainerInfo"))
		return false;
	}

	return true;
}

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

bool UGameMenuSetting::GetMenuContainerInfo(const FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo)
{
	if (const FMenuContainerInfo* Found = MenuContainerInfos.FindByKey(InMenuTag))
	{
		OutMenuContainerInfo = *Found;
		return true;
	}
	return false;
}

TArray<FMenuContainerInfo> UGameMenuSetting::GetMenuContainerInfos(const TArray<FGameplayTag>& InMenuTags)
{
	TArray<FMenuContainerInfo> OutMenuContainerInfos;

	for (auto& MenuTag : InMenuTags)
	{
		if (const FMenuContainerInfo* Found = MenuContainerInfos.FindByKey(MenuTag))
		{
			if (!OutMenuContainerInfos.Contains(*Found))
			{
				OutMenuContainerInfos.Add(*Found);
			}
		}
	}

	return OutMenuContainerInfos;
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

TArray<FGameplayTag> UGameMenuSetting::GetDirectChildMenuTags(const FGameplayTag InMenuTag, const bool bIsContainOriginal)
{
	TArray<FGameplayTag> ChildTags;
	if (bIsContainOriginal)
	{
		ChildTags.Add(InMenuTag);
	}

	for (auto& MenuInfo : MenuInfos)
	{
		if (MenuInfo.MenuTag.RequestDirectParent() == InMenuTag)
		{
			ChildTags.Add(MenuInfo.MenuTag);
		}
	}

	return ChildTags;
}

TArray<FMenuInfo> UGameMenuSetting::GetDirectChildMenuInfos(const FGameplayTag InMenuTag, const bool bIsContainOriginal)
{
	return GetMenuInfos(GetDirectChildMenuTags(InMenuTag, bIsContainOriginal));
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
	return GameplayTagContainer.IsValid() ? GameplayTagContainer.First() : FGameplayTag::EmptyTag;
}

TArray<FMenuInfo> UGameMenuSetting::GetRootMenuInfos()
{
	return GetDirectChildMenuInfos(GetRootMenuTag());
}
