// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "LocalPlayer/GenericLocalPlayerSettings.h"

#define LOCTEXT_NAMESPACE "FGenericGenericGameplay"

UGenericLocalPlayerSettings* UGenericLocalPlayerSettings::Get()
{
	return GEngine ? Cast<UGenericLocalPlayerSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

#undef LOCTEXT_NAMESPACE
