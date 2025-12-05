// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericButtonContent.h"

#include "GenericButtonWidget.h"

bool UGenericButtonContent::Initialize(UWidget* InWidget, UDataTable* InDataTable)
{
	if (!IsValid(InWidget))
	{
		return false;
	}

	if (!IsValid(InDataTable))
	{
		return false;
	}

	ButtonContent = InWidget;
	ButtonContentDataTable = InDataTable;

	if (!ButtonContent.IsA(GetContentSupportClass()))
	{
		return false;
	}

	if (!InDataTable->RowStruct->IsChildOf(GetContentRowSupportClass()))
	{
		return false;
	}

	UGenericButtonWidget* Button = GetButtonWidget();
	if (!IsValid(Button))
	{
		return false;
	}

	Button->OnButtonHovered.AddUniqueDynamic(this, &UGenericButtonContent::OnButtonHovered);
	Button->OnButtonUnhovered.AddUniqueDynamic(this, &UGenericButtonContent::OnButtonUnhovered);
	Button->OnButtonSelectionChanged.AddUniqueDynamic(this, &UGenericButtonContent::OnButtonSelectionChanged);

	return OnInitialized();
}

void UGenericButtonContent::Deinitialize()
{
	if (UGenericButtonWidget* Button = GetButtonWidget())
	{
		Button->OnButtonHovered.RemoveAll(this);
		Button->OnButtonUnhovered.RemoveAll(this);
		Button->OnButtonSelectionChanged.RemoveAll(this);
	}

	OnDeinitialized();
}

UGenericButtonWidget* UGenericButtonContent::GetButtonWidget() const
{
	return Cast<UGenericButtonWidget>(GetOuter());
}

UGenericButtonWidget* UGenericButtonContent::GetButtonWidgetByClass(TSubclassOf<UGenericButtonWidget> InClass) const
{
	ensure(InClass);
	return GetButtonWidget();
}

FGameplayTag UGenericButtonContent::GetButtonTag_Implementation() const
{
	return GetButtonWidget()->GetButtonTag();
}

bool UGenericButtonContent::OnInitialized()
{
	return true;
}

TSubclassOf<UWidget> UGenericButtonContent::GetContentSupportClass() const
{
	return UWidget::StaticClass();
}

UStruct* UGenericButtonContent::GetContentRowSupportClass() const
{
	return FButtonContentTableRow::StaticStruct();
}

void UGenericButtonContent::OnDeinitialized()
{
}

void UGenericButtonContent::OnButtonHovered_Implementation(UGenericButtonWidget* InButton)
{
}

void UGenericButtonContent::OnButtonUnhovered_Implementation(UGenericButtonWidget* InButton)
{
}

void UGenericButtonContent::OnButtonSelectionChanged_Implementation(UGenericButtonWidget* InButton, bool InSelection)
{
}
