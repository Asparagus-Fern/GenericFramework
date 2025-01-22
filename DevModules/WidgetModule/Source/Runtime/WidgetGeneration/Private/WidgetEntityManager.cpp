// Fill out your copyright notice in the Description page of Project Settings.


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
		DLOG(DLogUI, Error, TEXT("InWidgetEntityClass Is InValid"))
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
		DLOG(DLogUI, Error, TEXT("InWidgetEntity Is InValid"))
		return;
	}

	if (WidgetEntities.Contains(InWidgetEntity))
	{
		DLOG(DLogUI, Warning, TEXT("InWidgetEntity Is Already Register"))
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
		DLOG(DLogUI, Error, TEXT("InWidgetEntity Is InValid"))
		return;
	}

	if (!WidgetEntities.Contains(InWidgetEntity))
	{
		DLOG(DLogUI, Warning, TEXT("InWidgetEntity Is Already UnRegister"))
		return;
	}

	InWidgetEntity->NativeOnDestroy();
	WidgetEntities.Remove(InWidgetEntity);
}
