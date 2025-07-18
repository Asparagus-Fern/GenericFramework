// Copyright ChenTaiye 2025. All Rights Reserved.


#include "SaveGameSettings.h"

#include "GenericSaveGameManager.h"

USaveGameSettings::USaveGameSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SaveGameManagerClass = UGenericSaveGameManager::StaticClass();
}
