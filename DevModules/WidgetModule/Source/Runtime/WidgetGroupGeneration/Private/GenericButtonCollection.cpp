// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonCollection.h"

#include "GameplayTagsManager.h"
#include "GenericButtonAsset.h"
#include "GenericButtonGroup.h"
#include "GenericButtonBuilder.h"
#include "GenericButtonContainer.h"
#include "GenericWidgetManager.h"
#include "BPFunctions/BPFunctions_GameplayTag.h"
#include "Manager/ManagerStatics.h"

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
}

void UGenericButtonCollection::NativeOnActived()
{
	IStateInterface::NativeOnActived();
	BuildChildButtonGroup(GetRootButtonTag());
}

void UGenericButtonCollection::NativeOnInactived()
{
	IStateInterface::NativeOnInactived();
	DestroyChildButtonGroup(GetRootButtonTag());
}

void UGenericButtonCollection::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();
}

bool UGenericButtonCollection::GetIsActived() const
{
	return IStateInterface::GetIsActived();
}

void UGenericButtonCollection::SetIsActived(const bool InActived)
{
	IStateInterface::SetIsActived(InActived);
}

void UGenericButtonCollection::BuildChildButtonGroup(FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return;
	}

	if (ButtonGroups.Contains(InButtonTag))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("This Button Group Is Already Build"))
		return;
	}

	UGenericWidgetManager* GenericWidgetManager = GetManager<UGenericWidgetManager>();
	UGenericButtonBuilder* ButtonBuilder = GetButtonBuilder(InButtonTag);

	if (!IsValid(GenericWidgetManager))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("GenericWidgetManager Is InValid"))
		return;
	}

	if (!IsValid(ButtonBuilder))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("ButtonBuilder Is InValid"))
		return;
	}

	if (UGenericButtonContainer* GroupWidget = BuildButtonGroupWidget(InButtonTag))
	{
		UGenericButtonGroup* ButtonGroup = NewObject<UGenericButtonGroup>(GetOuter());
		ButtonGroup->SetButtonGroupWidget(GroupWidget);

		if (!GenericWidgetManager->OpenUserWidget(GroupWidget))
		{
			GenericLOG(GenericLogUI, Error, TEXT("Open Button Container Fail"))
			return;
		}

		FGameplayTagContainer ChildrenTagContainer = UBPFunctions_GameplayTag::GetDirectGameplayTagChildren(InButtonTag);
		for (int32 It = 0; It < ChildrenTagContainer.Num(); It++)
		{
			FGameplayTag ChildTag = ChildrenTagContainer.GetByIndex(It);
			if (UGenericButtonWidget* ButtonWidget = BuildButtonWidget(ChildTag, GroupWidget))
			{
				if (!GenericWidgetManager->OpenUserWidget(ButtonWidget))
				{
					GenericLOG(GenericLogUI, Error, TEXT("Open Button Widget Fail"))
					continue;
				}

				ButtonWidget->SelfTag = ChildTag;
				ButtonGroup->AddButton(ButtonWidget);
				ButtonWidget->NativeConstructButtonParameters(GetButtonBuilder(ChildTag)->ButtonParameter);
			}
		}

		RegisterButtonGroup(InButtonTag, ButtonGroup);
	}
}

void UGenericButtonCollection::DestroyChildButtonGroup(FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return;
	}

	if (!ButtonGroups.Contains(InButtonTag))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("This Button Group Is Already Destroy"))
		return;
	}

	UGenericWidgetManager* GenericWidgetManager = GetManager<UGenericWidgetManager>();
	TObjectPtr<UGenericButtonGroup> ButtonGroup = ButtonGroups.FindRef(InButtonTag);

	if (IsValid(GenericWidgetManager))
	{
		UGenericButtonContainer* ButtonContainer = ButtonGroup->GetButtonGroupWidget();
		TArray<UGenericButtonWidget*> ButtonWidgets = ButtonGroup->GetAllButton();

		for (auto& ButtonWidget : ButtonWidgets)
		{
			ButtonGroup->RemoveButton(ButtonWidget);
			ButtonContainer->RemoveChild(ButtonWidget);
			GenericWidgetManager->CloseUserWidget(ButtonWidget);
		}

		GenericWidgetManager->CloseUserWidget(ButtonContainer);
		ButtonGroup->SetButtonGroupWidget(nullptr);
	}

	UnRegisterButtonGroup(InButtonTag);
}

UGenericButtonContainer* UGenericButtonCollection::BuildButtonGroupWidget(FGameplayTag InButtonTag) const
{
	UGenericButtonContainer* ButtonContainer = nullptr;
	if (UGenericButtonBuilder* Builder = GetButtonBuilder(InButtonTag))
	{
		if (Builder->ButtonGroupClass)
		{
			ButtonContainer = CreateWidget<UGenericButtonContainer>(GetWorld(), Builder->ButtonGroupClass);
		}
	}

	return ButtonContainer;
}

UGenericButtonWidget* UGenericButtonCollection::BuildButtonWidget(FGameplayTag InButtonTag, UGenericButtonContainer* GroupWidget) const
{
	UGenericButtonWidget* Button = nullptr;
	if (UGenericButtonBuilder* Builder = GetButtonBuilder(InButtonTag))
	{
		if (Builder->ButtonClass)
		{
			Button = CreateWidget<UGenericButtonWidget>(GroupWidget, Builder->ButtonClass);
		}
	}

	return Button;
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
		BuildChildButtonGroup(InButton->SelfTag);
		ProcessOnSelectionChanged(InButton->SelfTag, Selection);
	}
	else
	{
		if (ButtonGroups.Contains(InButton->SelfTag))
		{
			UGenericButtonGroup* Group = ButtonGroups.FindRef(InButton->SelfTag);
			Group->DeselectAll();
			DestroyChildButtonGroup(InButton->SelfTag);
		}

		ProcessOnSelectionChanged(InButton->SelfTag, Selection);
	}
}

TArray<FGameplayTag> UGenericButtonCollection::GetAllButtonTags() const
{
	TArray<FGameplayTag> ButtonTags;

	for (auto& ButtonBuilder : GetAllButtonBuilder())
	{
		if (ButtonBuilder->ButtonTag == GetRootButtonTag())
		{
			continue;
		}

		ButtonTags.Add(ButtonBuilder->ButtonTag);
	}

	return ButtonTags;
}

FGameplayTag UGenericButtonCollection::GetRootButtonTag() const
{
	if (WidgetAsset)
	{
		return WidgetAsset->RootButtonTag;
	}

	return FGameplayTag::EmptyTag;
}

TArray<UGenericButtonBuilder*> UGenericButtonCollection::GetAllButtonBuilder() const
{
	TArray<UGenericButtonBuilder*> Result;

	if (WidgetAsset)
	{
		return WidgetAsset->ButtonBuilders;
	}

	return Result;
}

UGenericButtonBuilder* UGenericButtonCollection::GetButtonBuilder(FGameplayTag InButtonTag) const
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return nullptr;
	}

	for (const auto& Builder : GetAllButtonBuilder())
	{
		if (Builder->ButtonTag == InButtonTag)
		{
			return Builder;
		}
	}
	return nullptr;
}

TArray<UGenericButtonBuilder*> UGenericButtonCollection::GetChildButtonBuilder(FGameplayTag InButtonTag) const
{
	TArray<UGenericButtonBuilder*> Builders;

	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return Builders;
	}

	for (const auto& Builder : GetAllButtonBuilder())
	{
		if (UBPFunctions_GameplayTag::GetDirectGameplayTagParent(Builder->ButtonTag) == InButtonTag)
		{
			Builders.Add(Builder);
		}
	}

	return Builders;
}

TArray<UGenericButtonGroup*> UGenericButtonCollection::GetAllButtonGroup() const
{
	TArray<TObjectPtr<UGenericButtonGroup>> Results;
	ButtonGroups.GenerateValueArray(Results);
	return Results;
}

UGenericButtonGroup* UGenericButtonCollection::GetButtonGroup(FGameplayTag InButtonTag) const
{
	if (ButtonGroups.Contains(InButtonTag))
	{
		return ButtonGroups.FindRef(InButtonTag);
	}

	return nullptr;
}
