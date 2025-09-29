// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "GenericLocalPlayerSettings.generated.h"

#define GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetterName, SetterName) \
	UPropertyDataSource::Create \
	( \
		UGenericLocalPlayerSettings::Get(), \
		GET_FUNCTION_NAME_STRING_CHECKED(UGenericLocalPlayerSettings, GetterName), \
		GET_FUNCTION_NAME_STRING_CHECKED(UGenericLocalPlayerSettings, SetterName) \
	)

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericLocalPlayerSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	static GENERICGAMEPLAYSYSTEM_API UGenericLocalPlayerSettings* Get();
};
