// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonAsset.h"

#include "GameplayTagsManager.h"
#include "GenericButtonBuilder.h"
#include "GenericButtonContainer.h"
#include "WidgetType.h"
#include "MVVM/WidgetDescriptionViewModel.h"
#include "Type/DebugType.h"

UGenericButtonAsset::UGenericButtonAsset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BuilderClass = UGenericButtonBuilder::StaticClass();
}

#if WITH_EDITOR

void UGenericButtonAsset::GenerateButtons()
{
	if (!RootButtonTag.IsValid())
	{
		GenericNOTIFY(TEXT("RootButtonTag is InValid"))
		return;
	}

	if (!IsValid(ButtonTable))
	{
		GenericNOTIFY(TEXT("MenuTagTable is InValid"))
		return;
	}

	if (!BuilderClass)
	{
		GenericNOTIFY(TEXT("BuilderClass is InValid"))
		return;
	}

	if (!ButtonTable->RowStruct->IsChildOf(FGameplayTagTableRow::StaticStruct()))
	{
		GenericNOTIFY(TEXT("MenuTagTable is not a GameplayTag Table"))
		return;
	}

	Modify();

	GameplayTagContainer = FGameplayTagContainer();
	GameplayTagContainer.AddTag(RootButtonTag);

	/* Fill Menu Tag In GameplayTagContainer */
	ButtonTable->ForeachRow<FGameplayTagTableRow>
	("", [this](FName Key, const FGameplayTagTableRow& Value)
	 {
		 const FGameplayTag ButtonTag = FGameplayTag::RequestGameplayTag(Value.Tag);

		 auto AddBuilder = [this](FGameplayTag InButtonTag, const FGameplayTagTableRow& InWidgetInfo)
		 {
			 /* Add In GameplayTagContainer And Make MenuEntity */
			 GameplayTagContainer.AddTag(InButtonTag);

			 UGenericButtonBuilder* NewBuilder = NewObject<UGenericButtonBuilder>(this, BuilderClass);;
			 NewBuilder->ButtonTag = InButtonTag;

			 if (NewBuilder->WidgetDescriptionViewModel)
			 {
				 NewBuilder->WidgetDescriptionViewModel->PrimaryName = FText::FromString(InWidgetInfo.DevComment);
			 }

			 ButtonBuilders.Add(NewBuilder);
		 };

		 /* Skip The Tag Not Under The RootMenuTag */
		 if (!ButtonTag.GetGameplayTagParents().HasTag(RootButtonTag))
		 {
			 GenericLOG(GenericLogUI, Error, TEXT("%s Is Not Under %s"), *ButtonTag.ToString(), *RootButtonTag.ToString())
			 return;
		 }

		 /* Skip The Tag Already In GameplayTagContainer */
		 if (IsContainButtonTag(ButtonTag))
		 {
			 GenericLOG(GenericLogUI, Warning, TEXT("ButtonTag : %s Is Already Generated"), *ButtonTag.ToString())
			 return;
		 }

		 AddBuilder(ButtonTag, Value);
	 }
	);

	GenericNOTIFY(TEXT("Generate Menu Finish"))
}

void UGenericButtonAsset::ClearButtons()
{
	ButtonBuilders.Reset();
	GameplayTagContainer.Reset();
}

#endif

bool UGenericButtonAsset::IsContainButtonTag(FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return false;
	}

	for (const auto& Builder : ButtonBuilders)
	{
		if (Builder->ButtonTag == InButtonTag)
		{
			return true;
		}
	}
	return false;
}
