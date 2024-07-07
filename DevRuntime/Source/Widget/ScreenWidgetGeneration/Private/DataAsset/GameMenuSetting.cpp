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
		DEBUG_Notify(Debug_UI, Error, TEXT("MenuTagTable is NULL"))
		return;
	}

	if (!MenuTagTable->RowStruct->IsChildOf(FGameplayTagTableRow::StaticStruct()))
	{
		DEBUG_Notify(Debug_UI, Error, TEXT("MenuTagTable is Not GameplayTag Table"))
		return;
	}

	// TSubclassOf<UMenuContainer> MenuContainerClass = LoadClass<UMenuContainer>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/DevRuntime/ScreenWidgetGeneration/Widget/MenuContainerTemplate/WBP_ContainerTemplate_StackBox.WBP_ContainerTemplate_StackBox_C'"));
	MenuTagTable->ForeachRow<FGameplayTagTableRow>
	("", [this](FName Key, const FGameplayTagTableRow& Value)
	 {
		 const FGameplayTag MenuTag = FGameplayTag::RequestGameplayTag(Value.Tag);

		 /* 跳过根节点 */
		 if (MenuTag.RequestDirectParent() == TAG_Menu)
		 {
			 return;
		 }

		 /* 生成新的组 */
		 if (!MenuContainerInfos.Contains(MenuTag.RequestDirectParent()))
		 {
			 MenuContainerInfos.Add(FMenuContainerInfo(MenuTag.RequestDirectParent()));
		 }

		 FMenuContainerInfo* FoundMenuContainerInfo = MenuContainerInfos.FindByKey(MenuTag.RequestDirectParent());
		 if (FoundMenuContainerInfo)
		 {
			 /* 跳过已生成的 */
			 if (FoundMenuContainerInfo->MenuInfos.Contains(MenuTag))
			 {
				 return;
			 }
		 }
		 else
		 {
			 DEBUG_Notify(Debug_UI, Error, TEXT("Unknown Error"))
			 return;
		 }

		 /* 添加新的MenuInfo */
		 FMenuInfo* NewMenuInfo = new FMenuInfo(MenuTag);
		 NewMenuInfo->MenuMainName = FText::FromString(Value.DevComment);
		 FoundMenuContainerInfo->MenuInfos.Add(*NewMenuInfo);
	 }
	);

	Modify();
}

#endif

FMenuContainerInfo* UGameMenuSetting::GetRootContainerInfo()
{
	for (auto& MenuContainerInfo : MenuContainerInfos)
	{
		if (MenuContainerInfo.ContainerTag.RequestDirectParent() == TAG_Menu)
		{
			return &MenuContainerInfo;
		}
	}

	return nullptr;
}

FMenuContainerInfo* UGameMenuSetting::GetContainerInfo(FGameplayTag InContainerTag)
{
	for (auto& MenuContainerInfo : MenuContainerInfos)
	{
		if (MenuContainerInfo.ContainerTag == InContainerTag)
		{
			return &MenuContainerInfo;
		}
	}

	return nullptr;
}
