// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonCollection.h"

#include "GameplayTagsManager.h"
#include "GenericButtonAsset.h"
#include "GenericButtonGroup.h"
#include "GenericButtonBuilder.h"
#include "GenericButtonContainer.h"
#include "GenericButtonWidget.h"
#include "GenericWidgetSubsystem.h"
#include "BPFunctions/BPFunctions_GameplayTag.h"

#include "MVVM/ButtonGroupViewModel.h"

FName FButtonCollectionEvent::OnPressedEventName = FName(TEXT("OnPressed"));
FName FButtonCollectionEvent::OnReleasedEventName = FName(TEXT("OnReleased"));
FName FButtonCollectionEvent::OnHoveredEventName = FName(TEXT("OnHovered"));
FName FButtonCollectionEvent::OnUnhoveredEventName = FName(TEXT("OnUnhovered"));
FName FButtonCollectionEvent::OnClickedEventName = FName(TEXT("OnClicked"));
FName FButtonCollectionEvent::OnDoubleClickedEventName = FName(TEXT("OnDoubleClicked"));
FName FButtonCollectionEvent::OnSelectionChangedEventName = FName(TEXT("OnSelectionChanged"));

FName FButtonCollectionEvent::GetEventNodeName(const FName EventName, const FGameplayTag ButtonTag)
{
	return FName(EventName.ToString() + "_" + ButtonTag.ToString());
}

void UGenericButtonCollection::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();
	OnButtonCollectionRegister.Broadcast();
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
	OnButtonCollectionUnRegister.Broadcast();
}

bool UGenericButtonCollection::GetIsActived() const
{
	return IStateInterface::GetIsActived();
}

void UGenericButtonCollection::SetIsActived(const bool InActived)
{
	IStateInterface::SetIsActived(InActived);
}

void UGenericButtonCollection::BuildChildButtonGroup(const FGameplayTag InButtonTag)
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

	UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this);
	if (!IsValid(GenericWidgetSubsystem))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("GenericWidgetSubsystem Is InValid"))
		return;
	}

	UGenericButtonBuilder* ButtonBuilder = GetButtonBuilder(InButtonTag);
	if (!IsValid(ButtonBuilder))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("ButtonBuilder Is InValid"))
		return;
	}

	if (!IsValid(ButtonBuilder->ButtonGroupClass))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("Button Group Class Is InValid"))
		return;
	}

	/* Get This Actived Button Widget */
	UGenericButtonWidget* ButtonWidget = GenericWidgetSubsystem->GetActiveWidget<UGenericButtonWidget>(InButtonTag);

	/* Button Container Is a Container To Accept Multi Buttons Widget */
	if (UGenericButtonContainer* ButtonContainer = BuildButtonGroupWidget(InButtonTag, ButtonWidget))
	{
		/* Generate Button Group And Open The Button Container Widget */
		UGenericButtonGroup* ButtonGroup = NewObject<UGenericButtonGroup>(this, ButtonBuilder->ButtonGroupClass);
		ButtonGroup->SetButtonGroupWidget(ButtonContainer);
		ButtonGroup->SetButtonGroupViewModel(ButtonBuilder->ButtonGroupViewModel);

		ButtonContainer->SetButtonCollection(this);
		ButtonContainer->SetButtonGroup(ButtonGroup);

		/* Try To Open This Container Widget,It Will Add To GameplaySlot Through Widget Slot Tag */
		if (!GenericWidgetSubsystem->OpenGenericWidget(ButtonContainer))
		{
			GenericLOG(GenericLogUI, Error, TEXT("Open Button Container Fail"))
			ButtonGroup->MarkAsGarbage();
			ButtonContainer->MarkAsGarbage();
			return;
		}

		/* Get Children Tag To Generate Child Button Widget */
		FGameplayTagContainer ChildrenTagContainer = GetChildrenButtonTag(InButtonTag);
		for (int32 It = 0; It < ChildrenTagContainer.Num(); It++)
		{
			/* Get The Child Tag And Build Child Button Widget */
			FGameplayTag ChildButtonTag = ChildrenTagContainer.GetByIndex(It);
			if (UGenericButtonWidget* ChildButtonWidget = BuildButtonWidget(ChildButtonTag, ButtonContainer))
			{
				/* Try To Open Child Widget, It Will Add To Container Through a Valid Container Widget, See More In UGenericGameSlotSubsystem::AddSlotWidget */
				ChildButtonWidget->SetButtonTag(ChildButtonTag);
				if (!GenericWidgetSubsystem->OpenGenericWidget(ChildButtonWidget))
				{
					GenericLOG(GenericLogUI, Error, TEXT("Open Button Widget Fail"))
					continue;
				}

				/* Add Widget To Button Group */
				ButtonGroup->AddButton(ChildButtonWidget);

				if (UGenericButtonBuilder* ChildButtonBuilder = GetButtonBuilder(ChildButtonTag))
				{
					/* Update Button Widget View Model */
					ChildButtonWidget->SetWidgetDescriptionViewModel(ChildButtonBuilder->WidgetDescriptionViewModel);
					ChildButtonWidget->SetWidgetRenderViewModel(ChildButtonBuilder->WidgetRenderViewModel);

					ChildButtonWidget->SetButtonSelectionViewModel(ChildButtonBuilder->ButtonSelectionViewModel);
					ChildButtonWidget->SetButtonInputViewModel(ChildButtonBuilder->ButtonInputViewModel);
					ChildButtonWidget->SetButtonSoundViewModel(ChildButtonBuilder->ButtonSoundViewModel);

					FButtonBuildParameter ButtonBuildParameter;
					ButtonBuildParameter.ChildButtonTag = ChildButtonTag;
					ButtonBuildParameter.ChildButtonBuilder = ChildButtonBuilder;
					ButtonBuildParameter.ChildButtonWidget = ChildButtonWidget;
					OnButtonBuilt(ButtonBuildParameter);
				}
			}
		}

		/* Binding Delegate From This New Button Group */
		if (RegisterButtonGroup(InButtonTag, ButtonGroup))
		{
			FButtonGroupBuildParameter ButtonGroupBuildParameter;
			ButtonGroupBuildParameter.ButtonTag = InButtonTag;
			ButtonGroupBuildParameter.ButtonBuilder = ButtonBuilder;
			ButtonGroupBuildParameter.ButtonGroup = ButtonGroup;
			ButtonGroupBuildParameter.ButtonContainer = ButtonContainer;
			OnButtonGroupBuilt(ButtonGroupBuildParameter);
		}
	}
}

void UGenericButtonCollection::DestroyChildButtonGroup(const FGameplayTag InButtonTag)
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

	UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this);
	TObjectPtr<UGenericButtonGroup> ButtonGroup = ButtonGroups.FindRef(InButtonTag);

	OnButtonGroupDestroy(InButtonTag);

	if (IsValid(GenericWidgetSubsystem))
	{
		UGenericButtonContainer* ButtonContainer = ButtonGroup->GetButtonGroupWidget();
		TArray<UGenericButtonWidget*> ButtonWidgets = ButtonGroup->GetAllButton();

		/* Get All Children Widgets And Close Them */
		for (auto& ButtonWidget : ButtonWidgets)
		{
			OnButtonDestroy(ButtonWidget->GetButtonTag());

			ButtonGroup->RemoveButton(ButtonWidget);
			ButtonContainer->RemoveChild(ButtonWidget);
			GenericWidgetSubsystem->CloseGenericWidget(ButtonWidget);
		}

		/* Close The Container Widget */
		GenericWidgetSubsystem->CloseGenericWidget(ButtonContainer);
		ButtonGroup->SetButtonGroupWidget(nullptr);
	}

	if (UnRegisterButtonGroup(InButtonTag))
	{
		PostButtonGroupDestroy(InButtonTag);
	}
}

UGenericButtonContainer* UGenericButtonCollection::BuildButtonGroupWidget(const FGameplayTag InButtonTag, UGenericButtonWidget* ButtonWidget) const
{
	UGenericButtonContainer* ButtonContainer = nullptr;
	if (UGenericButtonBuilder* Builder = GetButtonBuilder(InButtonTag))
	{
		if (Builder->ButtonContainerClass)
		{
			/*
			 * if The Widget Is Valid, Use As Owner When Create This Button Container.
			 * Otherwise, Means That This Button Tag May be a Root Tag, Container Owner Will Be PlayerController
			 */
			if (IsValid(ButtonWidget))
			{
				ButtonContainer = CreateWidget<UGenericButtonContainer>(ButtonWidget, Builder->ButtonContainerClass);
			}
			else
			{
				/* Outer Is Player Controller */
				if (APlayerController* PC = Cast<APlayerController>(GetOuter()))
				{
					ButtonContainer = CreateWidget<UGenericButtonContainer>(PC, Builder->ButtonContainerClass);
				}
			}
		}
	}

	return ButtonContainer;
}

void UGenericButtonCollection::OnButtonGroupBuilt_Implementation(const FButtonGroupBuildParameter& ButtonGroupBuildParameter)
{
	if (UButtonGroupViewModel* ButtonGroupViewModel = ButtonGroupBuildParameter.ButtonBuilder->ButtonGroupViewModel)
	{
		if (ButtonGroupViewModel->bShouldHiddenParentContainer)
		{
			FGameplayTag ParentGameplayTag = UBPFunctions_GameplayTag::GetDirectGameplayTagParent(ButtonGroupBuildParameter.ButtonTag);
			if (UGenericButtonGroup* ParentButtonGroup = GetButtonGroup(ParentGameplayTag))
			{
				ParentButtonGroup->GetButtonGroupWidget()->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

UGenericButtonWidget* UGenericButtonCollection::BuildButtonWidget(const FGameplayTag InButtonTag, UGenericButtonContainer* GroupWidget) const
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

void UGenericButtonCollection::OnButtonBuilt_Implementation(const FButtonBuildParameter& ButtonBuildParameter)
{
}

void UGenericButtonCollection::OnButtonGroupDestroy_Implementation(FGameplayTag InButtonTag)
{
}

void UGenericButtonCollection::PostButtonGroupDestroy_Implementation(FGameplayTag InButtonTag)
{
	FGameplayTag ParentGameplayTag = UBPFunctions_GameplayTag::GetDirectGameplayTagParent(InButtonTag);
	if (UGenericButtonGroup* ParentButtonGroup = GetButtonGroup(ParentGameplayTag))
	{
		ParentButtonGroup->GetButtonGroupWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UGenericButtonCollection::OnButtonDestroy_Implementation(FGameplayTag InButtonTag)
{
}

bool UGenericButtonCollection::RegisterButtonGroup(const FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return false;
	}

	if (!IsValid(InButtonGroup))
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonGroup Is InValid"))
		return false;
	}

	if (ButtonGroups.Contains(InButtonTag))
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is Already Registered"))
		return false;
	}

	ButtonGroups.Add(InButtonTag, InButtonGroup);
	InButtonGroup->OnButtonPressed.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonPressed);
	InButtonGroup->OnButtonReleased.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonReleased);
	InButtonGroup->OnButtonHovered.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonHovered);
	InButtonGroup->OnButtonUnhovered.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonUnhovered);
	InButtonGroup->OnButtonClicked.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonClicked);
	InButtonGroup->OnButtonDoubleClicked.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonDoubleClicked);
	InButtonGroup->OnButtonSelectionChanged.AddUniqueDynamic(this, &UGenericButtonCollection::OnButtonSelectionChanged);

	InButtonGroup->NativeOnCreate();

	return true;
}

bool UGenericButtonCollection::UnRegisterButtonGroup(const FGameplayTag InButtonTag)
{
	if (!InButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return false;
	}

	if (!ButtonGroups.Contains(InButtonTag))
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is Already UnRegistered"))
		return false;
	}

	TObjectPtr<UGenericButtonGroup> ButtonGroup = ButtonGroups.FindRef(InButtonTag);
	ButtonGroup->OnButtonPressed.RemoveAll(this);
	ButtonGroup->OnButtonReleased.RemoveAll(this);
	ButtonGroup->OnButtonHovered.RemoveAll(this);
	ButtonGroup->OnButtonUnhovered.RemoveAll(this);
	ButtonGroup->OnButtonClicked.RemoveAll(this);
	ButtonGroup->OnButtonDoubleClicked.RemoveAll(this);
	ButtonGroup->OnButtonSelectionChanged.RemoveAll(this);

	ButtonGroup->NativeOnDestroy();
	ButtonGroups.Remove(InButtonTag);

	return true;
}

void UGenericButtonCollection::OnButtonPressed_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnPressedEventName, InButton->GetButtonTag());
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonReleased_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnReleasedEventName, InButton->GetButtonTag());
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonHovered_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnHoveredEventName, InButton->GetButtonTag());
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonUnhovered_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnUnhoveredEventName, InButton->GetButtonTag());
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonClicked_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnClickedEventName, InButton->GetButtonTag());
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonDoubleClicked_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnDoubleClickedEventName, InButton->GetButtonTag());
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonSelectionChanged_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton, bool Selection)
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
		BuildChildButtonGroup(InButton->GetButtonTag());
		ProcessOnSelectionChanged(InButton->GetButtonTag(), Selection);
	}
	else
	{
		if (ButtonGroups.Contains(InButton->GetButtonTag()))
		{
			UGenericButtonGroup* Group = ButtonGroups.FindRef(InButton->GetButtonTag());
			Group->DeselectAll();
			DestroyChildButtonGroup(InButton->GetButtonTag());
		}

		ProcessOnSelectionChanged(InButton->GetButtonTag(), Selection);
	}
}

APlayerController* UGenericButtonCollection::GetOwnerPlayer() const
{
	return Cast<APlayerController>(GetOuter());
}

UGenericButtonAsset* UGenericButtonCollection::GetButtonAsset() const
{
	return ButtonAsset;
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
	if (ButtonAsset)
	{
		return ButtonAsset->GetRootButtonTag();
	}

	return FGameplayTag::EmptyTag;
}

TArray<UGenericButtonBuilder*> UGenericButtonCollection::GetAllButtonBuilder() const
{
	TArray<UGenericButtonBuilder*> Result;

	if (ButtonAsset)
	{
		return ButtonAsset->ButtonBuilders;
	}

	return Result;
}

UGenericButtonBuilder* UGenericButtonCollection::GetButtonBuilder(const FGameplayTag InButtonTag) const
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

TArray<UGenericButtonGroup*> UGenericButtonCollection::GetAllButtonGroup() const
{
	TArray<TObjectPtr<UGenericButtonGroup>> Results;
	ButtonGroups.GenerateValueArray(Results);
	return Results;
}

UGenericButtonGroup* UGenericButtonCollection::GetButtonGroup(const FGameplayTag InButtonTag) const
{
	if (ButtonGroups.Contains(InButtonTag))
	{
		return ButtonGroups.FindRef(InButtonTag);
	}

	return nullptr;
}

FGameplayTagContainer UGenericButtonCollection::GetChildrenButtonTag(const FGameplayTag InButtonTag) const
{
	FGameplayTagContainer Container;

	for (auto& ButtonTag : GetAllButtonTags())
	{
		if (UBPFunctions_GameplayTag::GetDirectGameplayTagParent(ButtonTag) == InButtonTag)
		{
			Container.AddTagFast(ButtonTag);
		}
	}

	return Container;
}
