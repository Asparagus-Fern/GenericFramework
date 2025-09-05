// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/GameplayTagEditorManager.h"

#include "GameplayTagsManager.h"
#include "GameplayTagsSettings.h"
#include "Manager/ManagerSettings.h"
#include "StaticFunctions/StaticFunctions_Object.h"

bool UGameplayTagEditorManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGameplayTagEditorManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UManagerSettings::Get()->OnSettingChanged().AddUObject(this, &UGameplayTagEditorManager::OnSettingChanged);
	AddGameplayTagTables();
}

void UGameplayTagEditorManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	RemoveGameplayTagTables();
}

void UGameplayTagEditorManager::OnSettingChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent)
{
	static FName Name_GameplayTagTables = GET_MEMBER_NAME_CHECKED(UManagerSettings, GameplayTagTables);
	if (InPropertyChangedEvent.Property)
	{
		if (InPropertyChangedEvent.Property->GetFName() == Name_GameplayTagTables || InPropertyChangedEvent.Property->GetFName() == Name_GameplayTagTables)
		{
			AddGameplayTagTables();
		}
	}
}

void UGameplayTagEditorManager::AddGameplayTagTables()
{
	if (UGameplayTagsSettings* GameplayTagsSettings = GetMutableDefault<UGameplayTagsSettings>())
	{
		for (auto& GameplayTagTable : UManagerSettings::Get()->GameplayTagTables)
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

void UGameplayTagEditorManager::RemoveGameplayTagTables()
{
	if (UGameplayTagsSettings* GameplayTagsSettings = GetMutableDefault<UGameplayTagsSettings>())
	{
		for (auto& GameplayTagTable : UManagerSettings::Get()->GameplayTagTables)
		{
			if (UDataTable* Table = FStaticFunctions_Object::LoadObject<UDataTable>(GameplayTagTable))
			{
				if (GameplayTagsSettings->GameplayTagTableList.Contains(Table->GetPathName()))
				{
					GameplayTagsSettings->GameplayTagTableList.Remove(FSoftObjectPath(Table));
				}
			}
		}

		GameplayTagsSettings->SaveConfig();

		UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		Manager.EditorRefreshGameplayTagTree();
	}
}
