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
UCLASS()
class WIDGETGENERATION_API UWidgetEntityManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	UWidgetEntity* RegisterWidgetEntity(TSubclassOf<UWidgetEntity> InWidgetEntityClass);
	void RegisterWidgetEntity(TArray<UWidgetEntity*> InWidgetEntities);
	void RegisterWidgetEntity(UWidgetEntity* InWidgetEntity);

	void UnRegisterWidgetEntity(TArray<UWidgetEntity*> InWidgetEntities);
	void UnRegisterWidgetEntity(UWidgetEntity* InWidgetEntity);

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
