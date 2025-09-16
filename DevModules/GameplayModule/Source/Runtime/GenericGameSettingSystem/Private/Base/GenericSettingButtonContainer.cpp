// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Base/GenericSettingButtonContainer.h"

#include "GenericButtonCollection.h"
#include "GenericButtonGroup.h"
#include "Base/GenericSettingBuilder.h"
#include "UMG/PropertyCollection.h"

void UGenericSettingButtonContainer::NativeOnActived()
{
	Super::NativeOnActived();

	if (UGenericButtonGroup* ButtonGroupRef = GetButtonGroup())
	{
		ButtonGroupRef->OnButtonSelectionChanged.AddUniqueDynamic(this, &UGenericSettingButtonContainer::OnButtonSelectionChanged);
	}
}

void UGenericSettingButtonContainer::NativeOnInactived()
{
	Super::NativeOnInactived();

	if (UGenericButtonGroup* ButtonGroupRef = GetButtonGroup())
	{
		ButtonGroupRef->OnButtonSelectionChanged.RemoveAll(this);
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
					PropertyCollection_Setting->SetPropertyCollectionViewModel(ButtonBuilder->PropertyCollectionViewModel);
				}
			}
		}
		else
		{
			PropertyCollection_Setting->SetPropertyCollectionViewModel(nullptr);
		}
	}
}
