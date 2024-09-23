// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameSettingMenu.h"

#include "Base/GameSettingValue.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Spacer.h"
#include "DataAsset/GameSettingValueMapping.h"
#include "UWidget/SimpleTextBox.h"

bool UGameSettingMenu::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		UHorizontalBox* HorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>();
		WidgetTree->RootWidget = HorizontalBox;

		SimpleTextBox = WidgetTree->ConstructWidget<USimpleTextBox>();
		SimpleTextBox->SetImageVisibility(ESlateVisibility::Collapsed);

		UHorizontalBoxSlot* SimpleTextBoxSlot = HorizontalBox->AddChildToHorizontalBox(SimpleTextBox);
		SimpleTextBoxSlot->SetHorizontalAlignment(HAlign_Center);
		SimpleTextBoxSlot->SetVerticalAlignment(VAlign_Center);
		SimpleTextBoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		SimpleTextBoxSlot->SetPadding(FMargin(8.f, 4.f));

		USpacer* Spacer = WidgetTree->ConstructWidget<USpacer>();
		UHorizontalBoxSlot* SpacerSlot = HorizontalBox->AddChildToHorizontalBox(Spacer);
		SpacerSlot->SetHorizontalAlignment(HAlign_Fill);
		SpacerSlot->SetVerticalAlignment(VAlign_Fill);
		SpacerSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));

		if (IsValid(GameSettingValueMapping))
		{
			const UGameSettingValue* InstanceGameSettingValue = GameSettingValueMapping->GameSettingValue.FindRef(Tag);
			if (IsValid(InstanceGameSettingValue))
			{
				GameSettingValue = WidgetTree->ConstructWidget<UGameSettingValue>(InstanceGameSettingValue->GetClass());
				UHorizontalBoxSlot* GameSettingValueSlot = HorizontalBox->AddChildToHorizontalBox(GameSettingValue);
				GameSettingValueSlot->SetHorizontalAlignment(HAlign_Fill);
				GameSettingValueSlot->SetVerticalAlignment(VAlign_Center);
				GameSettingValueSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
			}
		}
	}

	return bInitializedThisCall;
}

void UGameSettingMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(SimpleTextBox))
	{
		SimpleTextBox->SetText(SettingName);
	}
}

void UGameSettingMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(GameSettingValueMapping))
	{
		UGameSettingValue* InstanceGameSettingValue = GameSettingValueMapping->GameSettingValue.FindRef(Tag);
		if (IsValid(InstanceGameSettingValue))
		{
			GameSettingValue = InstanceGameSettingValue;
			// UHorizontalBoxSlot* GameSettingValueSlot = HorizontalBox->AddChildToHorizontalBox(GameSettingValue);
			// GameSettingValueSlot->SetHorizontalAlignment(HAlign_Fill);
			// GameSettingValueSlot->SetVerticalAlignment(VAlign_Center);
			// GameSettingValueSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		}
	}
}

FText UGameSettingMenu::GetSettingName() const
{
	return SettingName;
}

void UGameSettingMenu::SetSettingName(const FText InSettingName)
{
	SettingName = InSettingName;
	if (IsValid(SimpleTextBox))
	{
		SimpleTextBox->SetText(InSettingName);
	}
}
