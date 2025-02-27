// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/CommonPlayerInput.h"

#include "GameFramework/InputSettings.h"

UCommonPlayerInput::UCommonPlayerInput()
	: Super()
{
#if WITH_EDITOR
	UInputSettings::GetInputSettings()->SetDefaultPlayerInputClass(UCommonPlayerInput::StaticClass());
#endif
}
