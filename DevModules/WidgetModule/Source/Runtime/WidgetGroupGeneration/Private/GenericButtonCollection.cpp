// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonCollection.h"

#include "GameplayTagsManager.h"
#include "GenericButtonGroup.h"
#include "GenericButtonBuilder.h"
#include "BPFunctions/BPFunctions_GameplayTag.h"

FName FButtonCollectionEvent::OnPressedEventName = FName(TEXT("OnPressed"));
FName FButtonCollectionEvent::OnReleasedEventName = FName(TEXT("OnReleased"));
FName FButtonCollectionEvent::OnHoveredEventName = FName(TEXT("OnHovered"));
FName FButtonCollectionEvent::OnUnhoveredEventName = FName(TEXT("OnUnhovered"));
FName FButtonCollectionEvent::OnClickedEventName = FName(TEXT("OnClicked"));
FName FButtonCollectionEvent::OnDoubleClickedEventName = FName(TEXT("OnDoubleClicked"));
FName FButtonCollectionEvent::OnSelectionChangedEventName = FName(TEXT("OnSelectionChanged"));

FName FButtonCollectionEvent::GetEventNodeName(FName EventName, FGameplayTag ButtonTag)
{
	return FName(EventName.ToString() + "_" + ButtonTag.ToString());
}

void UGenericButtonCollection::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();

	for (auto& ButtonBuilder : ButtonBuilders)
	{
		ButtonBuilder->GetOnButtonGroupBuilt().AddUObject(this, &UGenericButtonCollection::OnButtonGroupBuild);
		ButtonBuilder->GetOnButtonGroupDestroy().AddUObject(this, &UGenericButtonCollection::OnButtonGroupDestroy);
	}
}

void UGenericButtonCollection::NativeOnActived()
{
	IStateInterface::NativeOnActived();

	if (UGenericButtonBuilder* Builder = GetButtonBuilder(RootButtonTag))
	{
		Builder->BuildButtonGroup(GetChildButtonBuilder(RootButtonTag));
	}
}

void UGenericButtonCollection::NativeOnInactived()
{
	IStateInterface::NativeOnInactived();

	if (ButtonGroups.Contains(RootButtonTag))
	{
		ButtonGroups.FindRef(RootButtonTag)->DeselectAll();
	}
}

void UGenericButtonCollection::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();

	for (auto& ButtonBuilder : ButtonBuilders)
	{
		ButtonBuilder->GetOnButtonGroupBuilt().RemoveAll(this);
		ButtonBuilder->GetOnButtonGroupDestroy().RemoveAll(this);
	}
}

bool UGenericButtonCollection::GetIsActived() const
{
	return IStateInterface::GetIsActived();
}

void UGenericButtonCollection::SetIsActived(const bool InActived)
{
	IStateInterface::SetIsActived(InActived);
}

#if WITH_EDITOR

void UGenericButtonCollection::GenerateButtons()
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

		 auto AddBuilder = [this](FGameplayTag InButtonTag)
		 {
			 /* Add In GameplayTagContainer And Make MenuEntity */
			 GameplayTagContainer.AddTag(InButtonTag);

			 UGenericButtonBuilder* NewBuilder = NewObject<UGenericButtonBuilder>(this);;
			 NewBuilder->SetButtonTag(InButtonTag);
			 // NewMenu->MenuMainName = FText::FromString(Value.DevComment);

			 ButtonBuilders.Add(NewBuilder);
		 };

		 /* Skip The RootMenuTag */
		 if (ButtonTag == RootButtonTag)
		 {
			 AddBuilder(RootButtonTag);
			 return;
		 }

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

		 AddBuilder(ButtonTag);
	 }
	);

	GenericNOTIFY(TEXT("Generate Menu Finish"))
}

void UGenericButtonCollection::ClearButtons()
{
	ButtonBuilders.Reset();
	GameplayTagContainer.Reset();
}

#endif

FGameplayTag UGenericButtonCollection::GetRootGameplayTag() const
{
	return RootButtonTag;
}

UDataTable* UGenericButtonCollection::GetDataTable() const
{
	return ButtonTable;
}

TArray<FGameplayTag> UGenericButtonCollection::GetAllButtonTags()
{
	TArray<FGameplayTag> ButtonTags;

	for (auto& ButtonBuilder : ButtonBuilders)
	{
		if (ButtonBuilder->GetButtonTag() == RootButtonTag)
		{
			continue;
		}

		ButtonTags.Add(ButtonBuilder->GetButtonTag());
	}

	return ButtonTags;
}

void UGenericButtonCollection::OnButtonGroupBuild(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup)
{
	RegisterButtonGroup(InButtonTag, InButtonGroup);
}

void UGenericButtonCollection::OnButtonGroupDestroy(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup)
{
	UnRegisterButtonGroup(InButtonTag);
}

void UGenericButtonCollection::RegisterButtonGroup(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return;
	}

	if (!IsValid(InButtonGroup))
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonGroup Is InValid"))
		return;
	}

	if (ButtonGroups.Contains(InButtonTag))
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is Already Registered"))
		return;
	}

	ButtonGroups.Add(InButtonTag, InButtonGroup);
	InButtonGroup->OnButtonPressed.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonPressed);
	InButtonGroup->OnButtonReleased.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonReleased);
	InButtonGroup->OnButtonHovered.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonHovered);
	InButtonGroup->OnButtonUnhovered.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonUnhovered);
	InButtonGroup->OnButtonClicked.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonClicked);
	InButtonGroup->OnButtonDoubleClicked.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonDoubleClicked);
	InButtonGroup->OnButtonSelectionChanged.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonSelectionChanged);
}

void UGenericButtonCollection::UnRegisterButtonGroup(FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return;
	}

	if (!ButtonGroups.Contains(InButtonTag))
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is Already UnRegistered"))
		return;
	}

	TObjectPtr<UGenericButtonGroup> Group = ButtonGroups.FindRef(InButtonTag);
	Group->OnButtonPressed.RemoveAll(this);
	Group->OnButtonReleased.RemoveAll(this);
	Group->OnButtonHovered.RemoveAll(this);
	Group->OnButtonUnhovered.RemoveAll(this);
	Group->OnButtonClicked.RemoveAll(this);
	Group->OnButtonDoubleClicked.RemoveAll(this);
	Group->OnButtonSelectionChanged.RemoveAll(this);

	ButtonGroups.Remove(InButtonTag);
}

void UGenericButtonCollection::OnButtonPressed(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnPressedEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonReleased(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnReleasedEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonHovered(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnHoveredEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonUnhovered(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnUnhoveredEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonClicked(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnClickedEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonDoubleClicked(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnDoubleClickedEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonSelectionChanged(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton, bool Selection)
{
	if (!IsValid(InButton))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Button Is InValid"))
		return;
	}

	if (!IsValid(InButtonGroup))
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonGroup Is InValid"))
		return;
	}

	auto ProcessOnSelectionChanged = [this](FGameplayTag ButtonTag, bool Selection)
	{
		FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnSelectionChangedEventName, ButtonTag);
		if (UFunction* Function = FindFunction(NodeName))
		{
			ProcessEvent(Function, &Selection);
		}
	};

	if (Selection)
	{
		if (UGenericButtonBuilder* Builder = GetButtonBuilder(RootButtonTag))
		{
			Builder->BuildButtonGroup(GetChildButtonBuilder(RootButtonTag));
			ProcessOnSelectionChanged(InButton->SelfTag, Selection);
		}
	}
	else
	{
		if (ButtonGroups.Contains(InButton->SelfTag))
		{
			UGenericButtonGroup* Group = ButtonGroups.FindRef(InButton->SelfTag);
			Group->DeselectAll();
			ProcessOnSelectionChanged(InButton->SelfTag, Selection);
			GetButtonBuilder(InButton->SelfTag)->DestroyButtonGroup(GetChildButtonBuilder(InButton->SelfTag));
		}
	}
}

bool UGenericButtonCollection::IsContainButtonTag(FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return false;
	}

	for (const auto& Builder : ButtonBuilders)
	{
		if (Builder->GetButtonTag() == InButtonTag)
		{
			return true;
		}
	}
	return false;
}

UGenericButtonBuilder* UGenericButtonCollection::GetButtonBuilder(FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return nullptr;
	}

	for (const auto& Builder : ButtonBuilders)
	{
		if (Builder->GetButtonTag() == InButtonTag)
		{
			return Builder;
		}
	}
	return nullptr;
}

TArray<UGenericButtonBuilder*> UGenericButtonCollection::GetChildButtonBuilder(FGameplayTag InButtonTag)
{
	TArray<UGenericButtonBuilder*> Builders;

	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return Builders;
	}

	for (const auto& Builder : ButtonBuilders)
	{
		if (UBPFunctions_GameplayTag::GetDirectGameplayTagParent(Builder->GetButtonTag()) == InButtonTag)
		{
			Builders.Add(Builder);
		}
	}

	return Builders;
}
