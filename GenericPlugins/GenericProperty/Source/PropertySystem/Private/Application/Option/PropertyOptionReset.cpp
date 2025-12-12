// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "Application/Option/PropertyOptionReset.h"

#include "MVVM/PropertyViewModel.h"

void UPropertyOptionReset::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UPropertyOptionReset::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPropertyOptionReset::NativeOnClicked()
{
	Super::NativeOnClicked();

	if (PropertyViewModel.IsValid())
	{
		PropertyViewModel.Get()->Reset();
	}
}

void UPropertyOptionReset::OnPropertyApply_Implementation(UPropertyViewModel* InViewModel)
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPropertyOptionReset::OnPropertyReset_Implementation(UPropertyViewModel* InViewModel)
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPropertyOptionReset::OnPropertyValueChanged_Implementation(UPropertyViewModel* InViewModel, EPropertyChangedReason ChangedReason)
{
	SetVisibility(InViewModel->GetIsPropertyValueDirty() ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}
