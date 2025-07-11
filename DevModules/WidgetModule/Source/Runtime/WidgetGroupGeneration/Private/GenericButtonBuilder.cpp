// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonBuilder.h"

#include "GenericButtonContainer.h"
#include "GenericButtonGroup.h"
#include "GenericWidgetManager.h"
#include "Manager/ManagerStatics.h"

UGenericButtonBuilder::UGenericButtonBuilder(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ButtonGroupClass = UGenericButtonContainer::StaticClass();
	ButtonClass = UGenericButtonWidget::StaticClass();
}

void UGenericButtonBuilder::BuildButtonGroup(const TArray<UGenericButtonBuilder*>& Children)
{
	if (!ButtonTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("ButtonTag Is InValid"))
		return;
	}

	if (!ButtonGroup)
	{
		ButtonGroup = NewObject<UGenericButtonGroup>(GetOuter());
	}

	if (UGenericButtonContainer* GroupWidget = BuildButtonGroupWidget())
	{
		ButtonGroup->SetButtonGroupWidget(GroupWidget);
		GetManager<UGenericWidgetManager>()->OpenUserWidget(GroupWidget);

		for (int32 It = 0; It < Children.Num(); It++)
		{
			UGenericButtonBuilder* ChildBuilder = Children[It];
			if (UGenericButtonWidget* ButtonWidget = ChildBuilder->BuildButtonWidget())
			{
				GroupWidget->AddChild(ButtonWidget, It);
				ButtonGroup->AddButton(ButtonWidget);
				GetManager<UGenericWidgetManager>()->OpenUserWidget(ButtonWidget);
			}
		}
	}

	OnButtonGroupBuiltEvent.Broadcast(ButtonTag, ButtonGroup);
}

void UGenericButtonBuilder::DestroyButtonGroup(const TArray<UGenericButtonBuilder*>& Children)
{
	if (IsValid(ButtonContainer))
	{
		for (auto& Child : Children)
		{
			ButtonGroup->RemoveButton(Child->Button);
			ButtonContainer->RemoveChild(Child->Button);
			GetManager<UGenericWidgetManager>()->CloseUserWidget(Child->Button);
		}

		GetManager<UGenericWidgetManager>()->CloseUserWidget(ButtonContainer);
		ButtonContainer = nullptr;
		ButtonGroup->SetButtonGroupWidget(nullptr);
	}
}

UGenericButtonContainer* UGenericButtonBuilder::BuildButtonGroupWidget(bool bUpdate)
{
	if (!IsValid(ButtonContainer) || (IsValid(ButtonContainer) && bUpdate))
	{
		if (BuildButtonGroupMethod == EBuildButtonMethod::UseButtonClass && ButtonClass)
		{
			ButtonContainer = CreateWidget<UGenericButtonContainer>(GetWorld(), ButtonClass);
		}
		else if (BuildButtonGroupMethod == EBuildButtonMethod::UseButtonRef && IsValid(ButtonRef))
		{
			ButtonContainer = ButtonGroupRef;
		}

		ButtonContainer->SelfTag = ButtonTag;
	}

	return ButtonContainer;
}

UGenericButtonWidget* UGenericButtonBuilder::BuildButtonWidget(bool bUpdate)
{
	if (!IsValid(Button) || (IsValid(Button) && bUpdate))
	{
		if (BuildButtonMethod == EBuildButtonMethod::UseButtonClass && ButtonClass)
		{
			Button = CreateWidget<UGenericButtonWidget>(GetWorld(), ButtonClass);
		}
		else if (BuildButtonMethod == EBuildButtonMethod::UseButtonRef && IsValid(ButtonRef))
		{
			Button = ButtonRef;
		}

		Button->SelfTag = ButtonTag;
	}

	return Button;
}

FGameplayTag UGenericButtonBuilder::GetButtonTag() const
{
	return ButtonTag;
}

void UGenericButtonBuilder::SetButtonTag(FGameplayTag InButtonTag)
{
	ButtonTag = InButtonTag;
}
