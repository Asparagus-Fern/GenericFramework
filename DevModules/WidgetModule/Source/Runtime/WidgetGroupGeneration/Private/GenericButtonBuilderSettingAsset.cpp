// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonBuilderSettingAsset.h"

#include "GameplayTagsManager.h"
#include "GenericButtonBuilderSetting.h"
#include "WidgetType.h"
#include "Type/DebugType.h"

bool UGenericButtonBuilderSettingAsset::IsContainButtonTag(FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return false;
	}

	for (const auto& BuilderSetting : GenericButtonBuilderSettings)
	{
		if (BuilderSetting->ButtonTag == InButtonTag)
		{
			return true;
		}
	}

	return false;
}

#if WITH_EDITOR

void UGenericButtonBuilderSettingAsset::GenerateBuilderSetting()
{
	if (!IsValid(ButtonTable))
	{
		GenericNOTIFY(TEXT("MenuTagTable is InValid"))
		return;
	}

	if (!ButtonTable->RowStruct->IsChildOf(FGameplayTagTableRow::StaticStruct()))
	{
		GenericNOTIFY(TEXT("MenuTagTable is not a Gameplay Tag Table"))
		return;
	}

	Modify();

	/* Fill Menu Tag In GameplayTagContainer */
	ButtonTable->ForeachRow<FGameplayTagTableRow>
	("", [this](FName Key, const FGameplayTagTableRow& Value)
	 {
		 const FGameplayTag ButtonTag = FGameplayTag::RequestGameplayTag(Value.Tag);

		 /* Skip The Tag Not Under The RootMenuTag */
		 if (!ButtonTag.GetGameplayTagParents().HasTag(RootButtonTag))
		 {
			 GenericLOG(GenericLogUI, Error, TEXT("%s Is Not Under %s"), *ButtonTag.ToString(), *RootButtonTag.ToString())
			 return;
		 }

		 if (IsContainButtonTag(ButtonTag))
		 {
			 return;
		 }

		 UGenericButtonBuilderSetting* NewSetting = NewObject<UGenericButtonBuilderSetting>(this);
		 NewSetting->ButtonTag = ButtonTag;
		 NewSetting->DevComment = Value.DevComment;
		 GenericButtonBuilderSettings.Add(NewSetting);
	 }
	);

	GenericNOTIFY(TEXT("Generate Finish"))
}

#endif
