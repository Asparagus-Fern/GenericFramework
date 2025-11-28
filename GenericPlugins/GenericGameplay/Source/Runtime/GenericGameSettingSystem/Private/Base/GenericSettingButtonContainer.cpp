// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Base/GenericSettingButtonContainer.h"

#include "GenericButtonCollection.h"
#include "GenericButtonGroup.h"
#include "GenericButtonWidget.h"
#include "Base/GenericSettingBuilder.h"
#include "UMG/PropertyCollection.h"

void UGenericSettingButtonContainer::NativeOnActived()
{
	Super::NativeOnActived();

	if (UGenericButtonGroup* ButtonGroupRef = GetButtonGroup())
	{
		ButtonGroupRef->OnButtonSelectionChanged.AddUniqueDynamic(this, &UGenericSettingButtonContainer::OnButtonSelectionChanged);
	}

	if (Button_Apply)
	{
		Button_Apply->OnButtonClicked.AddUniqueDynamic(this, &UGenericSettingButtonContainer::OnApplyButtonClicked);
	}

	if (Button_Reset)
	{
		Button_Reset->OnButtonClicked.AddUniqueDynamic(this, &UGenericSettingButtonContainer::OnResetButtonClicked);
	}
}

void UGenericSettingButtonContainer::NativeOnInactived()
{
	Super::NativeOnInactived();

	if (UGenericButtonGroup* ButtonGroupRef = GetButtonGroup())
	{
		ButtonGroupRef->OnButtonSelectionChanged.RemoveAll(this);
	}

	if (Button_Apply)
	{
		Button_Apply->OnButtonClicked.RemoveAll(this);
	}

	if (Button_Reset)
	{
		Button_Reset->OnButtonClicked.RemoveAll(this);
	}
}

void UGenericSettingButtonContainer::OnButtonSelectionChanged_Implementation(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton, bool InSelection)
{
	if (PropertyCollection_Setting)
	{
		if (InSelection)
		{
			if (UGenericButtonCollection* ButtonCollectionRef = GetButtonCollection())
			{
				if (UGenericSettingBuilder* ButtonBuilder = Cast<UGenericSettingBuilder>(ButtonCollectionRef->GetButtonBuilder(InButton->SelfTag)))
				{
					PropertyCollection_Setting->SetPropertyCollectionAsset(ButtonBuilder->GameSettingDataCollection);
					return;
				}
			}
		}

		PropertyCollection_Setting->ClearPropertyCollectionViewModel();
	}
}

void UGenericSettingButtonContainer::OnApplyButtonClicked(UGenericButtonWidget* InButton)
{
	if (PropertyCollection_Setting)
	{
		PropertyCollection_Setting->ApplyPropertyChanged();
	}
}

void UGenericSettingButtonContainer::OnResetButtonClicked(UGenericButtonWidget* InButton)
{
	if (PropertyCollection_Setting)
	{
		PropertyCollection_Setting->ResetPropertyChanged();
	}
}
