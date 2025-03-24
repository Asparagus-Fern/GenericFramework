// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Common/CommonPlayerInput.h"

#include "GameFramework/InputSettings.h"

UCommonPlayerInput::UCommonPlayerInput()
	: Super()
{
#if WITH_EDITOR
	UInputSettings::GetInputSettings()->SetDefaultPlayerInputClass(UCommonPlayerInput::StaticClass());
#endif
}
