// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UWidget/GenericRotatorBox.h"

#include "Components/TextBlock.h"
#include "UWidget/GenericButton.h"

void UGenericRotatorBox::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetSelectedIndex(DefaultSelectedIndex);
}

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
	int32 Index;
	if (GetPreviousValidIndex(Index))
	{
		SetSelectedIndex(Index);
	}
}

void UGenericRotatorBox::RotateRight()
{
	int32 Index;
	if (GetNextValidIndex(Index))
	{
		SetSelectedIndex(Index);
	}
}

void UGenericRotatorBox::AddTextLabel(const FText& InTextLabel)
{
	TextLabels.Emplace(InTextLabel);
}

void UGenericRotatorBox::RemoveTextLabel(const FText& InTextLabel)
{
	int32 PreviousIndex = INDEX_NONE;
	GetPreviousValidIndex(PreviousIndex);

	TextLabels.RemoveAll([InTextLabel](const FText& TextLabel)
		{
			return InTextLabel.EqualTo(TextLabel);
		}
	);

	if (PreviousIndex != INDEX_NONE)
	{
		SetSelectedIndex(PreviousIndex);
	}
}

void UGenericRotatorBox::SetSelectedIndex(int32 Index)
{
	if (TextLabels.IsValidIndex(Index) && SelectedIndex != Index)
	{
		SelectedIndex = Index;
		OnSelectedIndexChanged(SelectedIndex);
		OnElementRotated.Broadcast(Index, TextLabels[Index]);
	}
}

bool UGenericRotatorBox::GetPreviousValidIndex(int32& OutIndex) const
{
	OutIndex = TextLabels.IsValidIndex(SelectedIndex - 1) ? (SelectedIndex - 1) : (bAllowWrap && !TextLabels.IsEmpty() ? TextLabels.Num() - 1 : INDEX_NONE);
	return OutIndex != INDEX_NONE;
}

bool UGenericRotatorBox::GetNextValidIndex(int32& OutIndex) const
{
	OutIndex = TextLabels.IsValidIndex(SelectedIndex + 1) ? (SelectedIndex + 1) : (bAllowWrap && !TextLabels.IsEmpty() ? 0 : INDEX_NONE);
	return OutIndex != INDEX_NONE;
}

void UGenericRotatorBox::OnSelectedIndexChanged_Implementation(int32 Index)
{
	TextBlock->SetText(TextLabels[Index]);
}
