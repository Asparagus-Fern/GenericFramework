// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericPlayerInput.h"

#include "GameFramework/InputSettings.h"

UGenericPlayerInput::UGenericPlayerInput()
	: Super()
{
#if WITH_EDITOR
	UInputSettings::GetInputSettings()->SetDefaultPlayerInputClass(UGenericPlayerInput::StaticClass());
#endif
}
