// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/CommonPlayerInput.h"
#include "Input/InputManager.h"
#include "Input/InputManagerSetting.h"

bool UCommonPlayerInput::InputKey(const FInputKeyParams& Params)
{
	if (UInputManager* InputManager = GetManager<UInputManager>())
	{
		if (!UInputManagerSetting::Get()->InputIdleNotInclude.Contains(Params.Key))
		{
			InputManager->RefreshIdleTime();
		}
	}
	return Super::InputKey(Params);
}
