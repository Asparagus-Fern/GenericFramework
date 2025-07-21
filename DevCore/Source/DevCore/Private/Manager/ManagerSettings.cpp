// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/ManagerSettings.h"

#include "GameplayTagsSettings.h"
#include "StaticFunctions/StaticFunctions_Object.h"

void UManagerSettings::PostInitProperties()
{
	Super::PostInitProperties();

#if WITH_EDITOR
	UpdateGameplayTagSettings();
#endif
}

void UManagerSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	static FName Name_GameplayTagTables = GET_MEMBER_NAME_CHECKED(UManagerSettings, GameplayTagTables);
	if (PropertyChangedEvent.Property)
	{
		if (PropertyChangedEvent.Property->GetFName() == Name_GameplayTagTables || PropertyChangedEvent.Property->GetFName() == Name_GameplayTagTables)
		{
			UpdateGameplayTagSettings();
		}
	}
}

void UManagerSettings::UpdateGameplayTagSettings()
{
	if (UGameplayTagsSettings* GameplayTagsSettings = GetMutableDefault<UGameplayTagsSettings>())
	{
		for (auto& GameplayTagTable : GameplayTagTables)
		{
			if (UDataTable* Table = FStaticFunctions_Object::LoadObject<UDataTable>(GameplayTagTable))
			{
				if (!GameplayTagsSettings->GameplayTagTableList.Contains(Table->GetPathName()))
				{
					GameplayTagsSettings->GameplayTagTableList.Add(FSoftObjectPath(Table));
				}
			}
		}

		GameplayTagsSettings->SaveConfig();

		UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		Manager.EditorRefreshGameplayTagTree();
	}
}
