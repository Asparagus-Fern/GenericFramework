// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WidgetEntityManager.h"

bool UWidgetEntityManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWidgetEntityManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UWidgetEntityManager::Deinitialize()
{
	Super::Deinitialize();

	const TArray<TObjectPtr<UWidgetEntity>> DestoryEntities = WidgetEntities;
	UnRegisterWidgetEntity(DestoryEntities);

	UnRegisterManager();
}

bool UWidgetEntityManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

UWidgetEntity* UWidgetEntityManager::RegisterWidgetEntity(TSubclassOf<UWidgetEntity> InWidgetEntityClass)
{
	if (!InWidgetEntityClass)
	{
		GenericLOG(UILog, Error, TEXT("InWidgetEntityClass Is InValid"))
		return nullptr;
	}

	UWidgetEntity* NewEntity = NewObject<UWidgetEntity>(this, InWidgetEntityClass);
	RegisterWidgetEntity(NewEntity);

	return NewEntity;
}

void UWidgetEntityManager::RegisterWidgetEntity(TArray<UWidgetEntity*> InWidgetEntities)
{
	for (const auto& InWidgetEntity : InWidgetEntities)
	{
		RegisterWidgetEntity(InWidgetEntity);
	}
}

void UWidgetEntityManager::RegisterWidgetEntity(UWidgetEntity* InWidgetEntity)
{
	if (!IsValid(InWidgetEntity))
	{
		GenericLOG(UILog, Error, TEXT("InWidgetEntity Is InValid"))
		return;
	}

	if (WidgetEntities.Contains(InWidgetEntity))
	{
		GenericLOG(UILog, Warning, TEXT("InWidgetEntity Is Already Register"))
		return;
	}

	InWidgetEntity->NativeOnCreate();
	WidgetEntities.Add(InWidgetEntity);
}

void UWidgetEntityManager::UnRegisterWidgetEntity(TArray<UWidgetEntity*> InWidgetEntities)
{
	for (const auto& InWidgetEntity : InWidgetEntities)
	{
		UnRegisterWidgetEntity(InWidgetEntity);
	}
}

void UWidgetEntityManager::UnRegisterWidgetEntity(UWidgetEntity* InWidgetEntity)
{
	if (!IsValid(InWidgetEntity))
	{
		GenericLOG(UILog, Error, TEXT("InWidgetEntity Is InValid"))
		return;
	}

	if (!WidgetEntities.Contains(InWidgetEntity))
	{
		GenericLOG(UILog, Warning, TEXT("InWidgetEntity Is Already UnRegister"))
		return;
	}

	InWidgetEntity->NativeOnDestroy();
	WidgetEntities.Remove(InWidgetEntity);
}
