// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonCollection.h"

#include "GameplayTagsManager.h"
#include "GenericButtonAsset.h"
#include "GenericButtonGroup.h"
#include "GenericButtonBuilder.h"
#include "GenericButtonConfirm.h"
#include "GenericButtonContainer.h"
#include "GenericWidgetManager.h"
#include "BPFunctions/BPFunctions_GameplayTag.h"
#include "Manager/ManagerStatics.h"
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

	UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>();
	if (!IsValid(GenericWidgetManager))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("GenericWidgetManager Is InValid"))
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
	UGenericButtonWidget* ButtonWidget = GenericWidgetManager->GetActiveWidget<UGenericButtonWidget>(InButtonTag);

	/* Button Container Is a Container To Accept Multi Buttons Widget */
	if (UGenericButtonContainer* GroupWidget = BuildButtonGroupWidget(InButtonTag, ButtonWidget))
	{
		/* Generate Button Group And Open The Button Container Widget */
		UGenericButtonGroup* ButtonGroup = NewObject<UGenericButtonGroup>(this, ButtonBuilder->ButtonGroupClass);
		ButtonGroup->SetButtonGroupWidget(GroupWidget);
		ButtonGroup->SetButtonGroupViewModel(ButtonBuilder->ButtonGroupViewModel);

		GroupWidget->SetButtonCollection(this);
		GroupWidget->SetButtonGroup(ButtonGroup);

		/* Try To Open This Container Widget,It Will Added To GameplaySlot Through Widget Slot Tag */
		if (!GenericWidgetManager->OpenGenericWidget(GroupWidget))
		{
			GenericLOG(GenericLogUI, Error, TEXT("Open Button Container Fail"))
			ButtonGroup->MarkAsGarbage();
			GroupWidget->MarkAsGarbage();
			return;
		}

		/* Get Children Tag To Generate Child Button Widget */
		FGameplayTagContainer ChildrenTagContainer = GetChildrenButtonTag(InButtonTag);
		for (int32 It = 0; It < ChildrenTagContainer.Num(); It++)
		{
			/* Get The Child Tag And Build Child Button Widget */
			FGameplayTag ChildTag = ChildrenTagContainer.GetByIndex(It);
			if (UGenericButtonWidget* ChildButtonWidget = BuildButtonWidget(ChildTag, GroupWidget))
			{
				/* Try To Open Child Widget, It Will Added To Container Through a Valid Container Widget, See More In UGenericGameSlotManager::AddSlotWidget */
				if (!GenericWidgetManager->OpenGenericWidget(ChildButtonWidget))
				{
					GenericLOG(GenericLogUI, Error, TEXT("Open Button Widget Fail"))
					continue;
				}

				/* Add Widget To Button Group */
				ChildButtonWidget->SelfTag = ChildTag;
				ButtonGroup->AddButton(ChildButtonWidget);

				/* Create Button Confirm If Exist */
				UGenericButtonConfirm* NewButtonConfirm = ChildButtonWidget->SetButtonConfirmByClass(ButtonBuilder->ButtonConfirmClass);
				if (IsValid(NewButtonConfirm))
				{
					NewButtonConfirm->SetButtonCollection(this);
					NewButtonConfirm->SetButtonGroup(ButtonGroup);
				}

				/* Update Button Widget View Model */
				ChildButtonWidget->SetWidgetDescriptionViewModel(GetButtonBuilder(ChildTag)->WidgetDescriptionViewModel);
				ChildButtonWidget->SetWidgetRenderViewModel(GetButtonBuilder(ChildTag)->WidgetRenderViewModel);

				ChildButtonWidget->SetButtonSelectionViewModel(GetButtonBuilder(ChildTag)->ButtonSelectionViewModel);
				ChildButtonWidget->SetButtonInputViewModel(GetButtonBuilder(ChildTag)->ButtonInputViewModel);
				ChildButtonWidget->SetButtonSoundViewModel(GetButtonBuilder(ChildTag)->ButtonSoundViewModel);

				OnButtonBuilt(ChildTag, ChildButtonWidget, ButtonBuilder);
			}
		}

		/* Binding Delegate From This New Button Group */
		if (RegisterButtonGroup(InButtonTag, ButtonGroup))
		{
			OnButtonGroupBuilt(InButtonTag, ButtonGroup, ButtonBuilder);
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

	UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>();
	TObjectPtr<UGenericButtonGroup> ButtonGroup = ButtonGroups.FindRef(InButtonTag);

	OnButtonGroupDestroy(InButtonTag);

	if (IsValid(GenericWidgetManager))
	{
		UGenericButtonContainer* ButtonContainer = ButtonGroup->GetButtonGroupWidget();
		TArray<UGenericButtonWidget*> ButtonWidgets = ButtonGroup->GetAllButton();

		/* Get All Children Widgets And Close Them */
		for (auto& ButtonWidget : ButtonWidgets)
		{
			OnButtonDestroy(ButtonWidget->SelfTag);

			ButtonGroup->RemoveButton(ButtonWidget);
			ButtonContainer->RemoveChild(ButtonWidget);
			GenericWidgetManager->CloseGenericWidget(ButtonWidget);
		}

		/* Close The Container Widget */
		GenericWidgetManager->CloseGenericWidget(ButtonContainer);
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

void UGenericButtonCollection::OnButtonGroupBuilt_Implementation(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup, UGenericButtonBuilder* InBuilder)
{
	if (UButtonGroupViewModel* ButtonGroupViewModel = InBuilder->ButtonGroupViewModel)
	{
		if (ButtonGroupViewModel->bShouldHiddenParentContainer)
		{
			FGameplayTag ParentGameplayTag = UBPFunctions_GameplayTag::GetDirectGameplayTagParent(InButtonTag);
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

void UGenericButtonCollection::OnButtonBuilt_Implementation(FGameplayTag InButtonTag, UGenericButtonWidget* InButtonWidget, UGenericButtonBuilder* InBuilder)
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
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnPressedEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonReleased_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnReleasedEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonHovered_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnHoveredEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonUnhovered_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnUnhoveredEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonClicked_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnClickedEventName, InButton->SelfTag);
	if (UFunction* Function = FindFunction(NodeName))
	{
		ProcessEvent(Function, nullptr);
	}
}

void UGenericButtonCollection::OnButtonDoubleClicked_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton)
{
	FName NodeName = FButtonCollectionEvent::GetEventNodeName(FButtonCollectionEvent::OnDoubleClickedEventName, InButton->SelfTag);
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
