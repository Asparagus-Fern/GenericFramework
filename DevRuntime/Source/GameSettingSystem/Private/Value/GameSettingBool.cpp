// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/GameSettingBool.h"

#include "Components/Button.h"

void UGameSettingBool::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(Button))
	{
		Button->OnClicked.AddDynamic(this, &UGameSettingBool::OnClicked);
	}
}

void UGameSettingBool::OnClicked_Implementation()
{
	bStatus = !bStatus;
}
