// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/GameSettingValueMapping.h"

#include "GameplayTagsManager.h"
#include "Debug/DebugType.h"

#if WITH_EDITOR

void UGameSettingValueMapping::Generate()
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

	MenuTagTable->ForeachRow<FGameplayTagTableRow>
	("", [this](FName Key, const FGameplayTagTableRow& Value)
	 {
		 const FGameplayTag Tag = FGameplayTag::RequestGameplayTag(Value.Tag);

		 if (GameSettingValue.Contains(Tag))
		 {
			 return;
		 }

		 GameSettingValue.FindOrAdd(Tag) = nullptr;
	 }
	);

	NOTIFY(TEXT("Generate Finish"))
}

#endif
