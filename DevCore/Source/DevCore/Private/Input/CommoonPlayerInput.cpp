// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/DEnhancedPlayerInput.h"
#include "Input/InputManager.h"
#include "Input/InputManagerSetting.h"

bool UDEnhancedPlayerInput::InputKey(const FInputKeyParams& Params)
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
