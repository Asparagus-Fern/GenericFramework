// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UWidget/GenericRotatorBox.h"

#include "UWidget/GenericButton.h"

void UGenericRotatorBox::NativeConstruct()
{
	Super::NativeConstruct();

	GenericButton_Left->OnClicked.AddUniqueDynamic(this, &UGenericRotatorBox::OnButtonLeftClicked);
	GenericButton_Right->OnClicked.AddUniqueDynamic(this, &UGenericRotatorBox::OnButtonRightClicked);
}

void UGenericRotatorBox::NativeDestruct()
{
	Super::NativeDestruct();

	GenericButton_Left->OnClicked.RemoveAll(this);
	GenericButton_Right->OnClicked.RemoveAll(this);
}

void UGenericRotatorBox::OnButtonLeftClicked()
{
	RotateLeft();
}

void UGenericRotatorBox::OnButtonRightClicked()
{
	RotateRight();
}

void UGenericRotatorBox::RotateLeft()
{
	if (!bAllowWrap && (GetSelectedIndex() - 1 < 0))
	{
		return;
	}

	ShiftTextLeft();
}

void UGenericRotatorBox::RotateRight()
{
	if (!bAllowWrap && (GetSelectedIndex() + 1 >= TextLabels.Num()))
	{
		return;
	}

	ShiftTextRight();
}

void UGenericRotatorBox::SetIsAllowWrap(bool InIsAllowWrap)
{
	bAllowWrap = InIsAllowWrap;
}

void UGenericRotatorBox::AddTextLabel(const FText& InTextLabel, int32 Index)
{
	if (Index >= 0)
	{
		TextLabels.EmplaceAt(Index, InTextLabel);
	}
	else
	{
		TextLabels.Emplace(InTextLabel);
	}

	OnOptionAdded(InTextLabel);

	SetSelectedItem(GetSelectedIndex());
}

void UGenericRotatorBox::RemoveTextLabel(FText InTextLabel)
{
	TextLabels.RemoveAll([InTextLabel](const FText& TextLabel)
		{
			return InTextLabel.EqualTo(TextLabel);
		}
	);

	OnOptionRemoved(InTextLabel);

	SetSelectedItem(GetSelectedIndex());
}
