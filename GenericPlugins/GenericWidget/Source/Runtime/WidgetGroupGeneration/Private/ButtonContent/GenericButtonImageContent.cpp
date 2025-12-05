// Fill out your copyright notice in the Description page of Project Settings.

#include "ButtonContent/GenericButtonImageContent.h"

#include "GenericButtonWidget.h"
#include "Components/Image.h"

bool UGenericButtonImageContent::OnInitialized()
{
	ButtonContentDataTable->ForeachRow<FButtonImageContentTableRow>
	("", [this](FName Key, const FButtonImageContentTableRow& Value)
	 {
		 if (GetButtonTag().GetTagName() == Value.ButtonTag)
		 {
			 Cache = Value;
		 }
	 }
	);

	UImage* Image = Cast<UImage>(ButtonContent);
	Image->SetBrush(Cache.Normal);

	return Super::OnInitialized();
}

TSubclassOf<UWidget> UGenericButtonImageContent::GetContentSupportClass() const
{
	return UImage::StaticClass();
}

UStruct* UGenericButtonImageContent::GetContentRowSupportClass() const
{
	return FButtonImageContentTableRow::StaticStruct();
}

void UGenericButtonImageContent::OnButtonHovered_Implementation(UGenericButtonWidget* InButton)
{
	Super::OnButtonHovered_Implementation(InButton);

	if (!GetButtonWidget()->GetIsSelected())
	{
		UImage* Image = Cast<UImage>(ButtonContent);
		Image->SetBrush(Cache.Hovered);
	}
}

void UGenericButtonImageContent::OnButtonUnhovered_Implementation(UGenericButtonWidget* InButton)
{
	Super::OnButtonUnhovered_Implementation(InButton);

	if (!GetButtonWidget()->GetIsSelected())
	{
		UImage* Image = Cast<UImage>(ButtonContent);
		Image->SetBrush(Cache.Normal);
	}
}

void UGenericButtonImageContent::OnButtonSelectionChanged_Implementation(UGenericButtonWidget* InButton, bool InSelection)
{
	Super::OnButtonSelectionChanged_Implementation(InButton, InSelection);

	UImage* Image = Cast<UImage>(ButtonContent);
	Image->SetBrush(InSelection ? Cache.Selected : Cache.Normal);
}
