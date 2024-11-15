// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/DEnhancedPlayerInput.h"
#include "Input/InputManager.h"
#include "Input/InputManagerSetting.h"
#include "Manager/ManagerProxy.h"

bool UDEnhancedPlayerInput::InputKey(const FInputKeyParams& Params)
{
	if (UInputManager* InputManager = UManagerProxy::Get()->GetManager<UInputManager>())
	{
		if (!UInputManagerSetting::Get()->InputIdleNotInclude.Contains(Params.Key))
		{
			InputManager->RefreshIdleTime();
		}
	}
	return Super::InputKey(Params);
}
