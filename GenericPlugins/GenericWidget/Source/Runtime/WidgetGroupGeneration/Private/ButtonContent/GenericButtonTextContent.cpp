// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonContent/GenericButtonTextContent.h"

#include "Components/TextBlock.h"

bool UGenericButtonTextContent::OnInitialized()
{
	ButtonContentDataTable->ForeachRow<FButtonTextContentTableRow>
	("", [this](FName Key, const FButtonTextContentTableRow& Value)
	 {
		 if (GetButtonTag().GetTagName() == Value.ButtonTag)
		 {
			 Cache = Value;
		 }
	 }
	);

	return Super::OnInitialized();
}

TSubclassOf<UWidget> UGenericButtonTextContent::GetContentSupportClass() const
{
	return UTextBlock::StaticClass();
}

UStruct* UGenericButtonTextContent::GetContentRowSupportClass() const
{
	return FButtonTextContentTableRow::StaticStruct();
}

void UGenericButtonTextContent::OnButtonHovered_Implementation(UGenericButtonWidget* InButton)
{
	Super::OnButtonHovered_Implementation(InButton);

	UTextBlock* TextBlock = Cast<UTextBlock>(ButtonContent);
	TextBlock->SetText(Cache.Hovered);
}

void UGenericButtonTextContent::OnButtonUnhovered_Implementation(UGenericButtonWidget* InButton)
{
	Super::OnButtonUnhovered_Implementation(InButton);

	UTextBlock* TextBlock = Cast<UTextBlock>(ButtonContent);
	TextBlock->SetText(Cache.Normal);
}

void UGenericButtonTextContent::OnButtonSelectionChanged_Implementation(UGenericButtonWidget* InButton, bool InSelection)
{
	Super::OnButtonSelectionChanged_Implementation(InButton, InSelection);

	UTextBlock* TextBlock = Cast<UTextBlock>(ButtonContent);
	TextBlock->SetText(InSelection ? Cache.Selected : Cache.Normal);
}
