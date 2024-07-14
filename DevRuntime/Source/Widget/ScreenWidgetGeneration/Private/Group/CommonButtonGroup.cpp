// Fill out your copyright notice in the Description page of Project Settings.


#include "Group/CommonButtonGroup.h"

int32 UCommonButtonGroup::GetSelectionRequiredIndex() const
{
	return SelectionRequiredIndex;
}

void UCommonButtonGroup::SetSelectionRequiredIndex(const int32 InIndex)
{
	SelectionRequiredIndex = InIndex;
}

void UCommonButtonGroup::UpdateSelectionRequired(const bool bRequireSelection)
{
	if (bSelectionRequired != bRequireSelection)
	{
		bSelectionRequired = bRequireSelection;

		if (bSelectionRequired && Buttons.Num() > 0 && SelectedButtonIndex < 0 && SelectionRequiredIndex >= 0 && SelectionRequiredIndex < Buttons.Num())
		{
			SelectButtonAtIndex(SelectionRequiredIndex);
		}
	}
}
