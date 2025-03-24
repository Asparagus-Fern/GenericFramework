// Copyright ChenTaiye 2025. All Rights Reserved.

#include "InteractableWidgetEntityGroupManager.h"

#include "InteractableWidgetEntityGroup.h"
#include "WidgetEntityManager.h"
#include "Manager/ManagerStatics.h"

bool UInteractableWidgetEntityGroupManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UInteractableWidgetEntityGroupManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UInteractableWidgetEntityGroupManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UInteractableWidgetEntityGroupManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

UInteractableWidgetEntityGroup* UInteractableWidgetEntityGroupManager::RegisterEntityGroup()
{
	UInteractableWidgetEntityGroup* NewEntityGroup = NewObject<UInteractableWidgetEntityGroup>(this);
	NewEntityGroup->NativeOnCreate();
	InteractableWidgetEntityGroups.Add(NewEntityGroup);

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnEntityGroupRegister, BPDelegate_OnEntityGroupRegister, NewEntityGroup)

	return NewEntityGroup;
}

UInteractableWidgetEntityGroup* UInteractableWidgetEntityGroupManager::RegisterEntityGroup(TArray<UInteractableWidgetEntity*> InEntities)
{
	UInteractableWidgetEntityGroup* NewEntityGroup = NewObject<UInteractableWidgetEntityGroup>(this);

	if (UWidgetEntityManager* WidgetEntityManager = GetManager<UWidgetEntityManager>())
	{
		WidgetEntityManager->RegisterWidgetEntity(InEntities);
	}

	NewEntityGroup->AddEntities(InEntities);
	NewEntityGroup->NativeOnCreate();

	InteractableWidgetEntityGroups.Add(NewEntityGroup);

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnEntityGroupRegister, BPDelegate_OnEntityGroupRegister, NewEntityGroup)

	return NewEntityGroup;
}

void UInteractableWidgetEntityGroupManager::UnRegisterEntityGroup(TArray<UInteractableWidgetEntityGroup*> InEntityGroups)
{
	for (const auto& InEntityGroup : InEntityGroups)
	{
		UnRegisterEntityGroup(InEntityGroup);
	}
}

void UInteractableWidgetEntityGroupManager::UnRegisterEntityGroup(UInteractableWidgetEntityGroup* InEntityGroup)
{
	if (!IsValid(InEntityGroup))
	{
		DLOG(DLogUI, Error, TEXT("InEntityGroup Is InValid"))
		return;
	}

	if (!InteractableWidgetEntityGroups.Contains(InEntityGroup))
	{
		DLOG(DLogUI, Warning, TEXT("InEntityGroup Is Already UnRegister"))
		return;
	}

	if (UWidgetEntityManager* WidgetEntityManager = GetManager<UWidgetEntityManager>())
	{
		WidgetEntityManager->UnRegisterWidgetEntity(InEntityGroup->GetEntities());
	}

	InEntityGroup->NativeOnDestroy();
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnEntityGroupUnRegister, BPDelegate_OnEntityGroupUnRegister, InEntityGroup)
	InteractableWidgetEntityGroups.Remove(InEntityGroup);
}
