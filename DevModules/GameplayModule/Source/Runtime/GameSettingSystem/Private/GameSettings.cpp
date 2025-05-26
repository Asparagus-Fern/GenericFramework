// Copyright ChenTaiye 2025. All Rights Reserved.


#include "GameSettings.h"

UGameSettings* UGameSettings::GetGameSettings()
{
	return Cast<UGameSettings>(GEngine->GetGameUserSettings());
}
