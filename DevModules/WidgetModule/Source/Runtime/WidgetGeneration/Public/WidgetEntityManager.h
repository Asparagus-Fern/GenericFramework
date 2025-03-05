// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/WidgetEntity.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "WidgetEntityManager.generated.h"

class UWidgetEntity;

/**
 * 
 */
UCLASS(MinimalAPI)
class UWidgetEntityManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	WIDGETGENERATION_API UWidgetEntity* RegisterWidgetEntity(TSubclassOf<UWidgetEntity> InWidgetEntityClass);
	WIDGETGENERATION_API void RegisterWidgetEntity(TArray<UWidgetEntity*> InWidgetEntities);
	WIDGETGENERATION_API void RegisterWidgetEntity(UWidgetEntity* InWidgetEntity);

	WIDGETGENERATION_API void UnRegisterWidgetEntity(TArray<UWidgetEntity*> InWidgetEntities);
	WIDGETGENERATION_API void UnRegisterWidgetEntity(UWidgetEntity* InWidgetEntity);

public:
	template <typename T>
	void RegisterWidgetEntity(TArray<T*> InWidgetEntities)
	{
		for (auto& InWidgetEntity : InWidgetEntities)
		{
			if (!InWidgetEntity->IsA(UWidgetEntity::StaticClass()))
			{
				return;
			}

			RegisterWidgetEntity(InWidgetEntity);
		}
	}

	template <typename T>
	void UnRegisterWidgetEntity(TArray<T*> InWidgetEntities)
	{
		for (auto& InWidgetEntity : InWidgetEntities)
		{
			if (!InWidgetEntity->IsA(UWidgetEntity::StaticClass()))
			{
				return;
			}

			UnRegisterWidgetEntity(InWidgetEntity);
		}
	}

protected:
	UPROPERTY()
	TArray<TObjectPtr<UWidgetEntity>> WidgetEntities;
};
