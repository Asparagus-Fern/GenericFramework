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
}

void UGameplayTagEditorManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}