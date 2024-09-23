// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/GameSettingToggle.h"

#include "UWidget/SimpleTextBox.h"

void UGameSettingToggle::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(SimpleTextBox))
	{
		SimpleTextBox->SetText(DefaultText);
	}
}

void UGameSettingToggle::OnClicked_Implementation()
{
	Super::OnClicked_Implementation();

	if (IsValid(SimpleTextBox))
	{
		if (bStatus)
		{
			SimpleTextBox->SetText(ToggleText);
		}
		else
		{
			SimpleTextBox->SetText(DefaultText);
		}
	}
}
