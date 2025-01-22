// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableWidgetEntity.h"
#include "Common/CommonObject.h"
#include "Interface/StateInterface.h"
#include "InteractableWidgetEntityGroup.generated.h"

class UInteractableWidgetEntity;

/**
 * 
 */
UCLASS()
class INTERACTABLEWIDGETGENERATION_API UInteractableWidgetEntityGroup : public UCommonObject, public IStateInterface
{
	GENERATED_BODY()

	/* IStateInterface */
public:
	virtual void OnCreate_Implementation() override;
	virtual void OnDestroy_Implementation() override;

	/* UInteractableWidgetEntityGroup */
public:
	UFUNCTION(BlueprintCallable)
	void AddEntities(TArray<UInteractableWidgetEntity*> InEntities);

	UFUNCTION(BlueprintCallable)
	void AddEntity(UInteractableWidgetEntity* InEntity);

	UFUNCTION(BlueprintCallable)
	void RemoveEntities(TArray<UInteractableWidgetEntity*> InEntities);

	UFUNCTION(BlueprintCallable)
	void RemoveEntity(UInteractableWidgetEntity* InEntity);

	UFUNCTION(BlueprintCallable)
	void RemoveEntityByIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	void ClearupEntity();

	UFUNCTION(BlueprintPure)
	bool HasLastSelectedEntity() const;

	UFUNCTION(BlueprintPure)
	bool HasSelectedEntity() const;

	UFUNCTION(BlueprintCallable)
	void SetSelectedEntity(UInteractableWidgetEntity* InEntity);

	UFUNCTION(BlueprintCallable)
	void SetSelectedEntityByIndex(int32 Index);

	UFUNCTION(BlueprintPure)
	UInteractableWidgetEntity* GetLastSelectedEntity() const;

	UFUNCTION(BlueprintPure)
	int32 GetLastSelectedEntityIndex() const;

	UFUNCTION(BlueprintPure)
	UInteractableWidgetEntity* GetSelectedEntity() const;

	UFUNCTION(BlueprintPure)
	int32 GetSelectedEntityIndex() const;

	UFUNCTION(BlueprintCallable)
	void SelectPreviousEntity(bool bAllowWrapping);

	UFUNCTION(BlueprintCallable)
	void SelectLastEntity();

	UFUNCTION(BlueprintCallable)
	void SelectNextEntity(bool bAllowWrapping);

	UFUNCTION(BlueprintCallable)
	void DeselectAll();

	UFUNCTION(BlueprintPure)
	bool HasEntity(UInteractableWidgetEntity* InEntity) const;

	UFUNCTION(BlueprintPure)
	int32 GetEntityCount() const;

	UFUNCTION(BlueprintPure)
	UInteractableWidgetEntity* GetEntityByIndex(int32 Index);

	UFUNCTION(BlueprintPure)
	int32 FindEntityIndex(UInteractableWidgetEntity* InEntity) const;

	UFUNCTION(BlueprintPure)
	TArray<UInteractableWidgetEntity*> GetEntities() const;

public:
	template <typename T>
	void AddEntities(TArray<T*> InEntities)
	{
		for (auto& InEntity : InEntities)
		{
			if (!InEntity->IsA(UInteractableWidgetEntity::StaticClass()))
			{
				return;
			}

			AddEntity(InEntity);
		}
	}

	template <typename T>
	void RemoveEntities(TArray<T*> InEntities)
	{
		for (auto& InEntity : InEntities)
		{
			if (!InEntity->IsA(UInteractableWidgetEntity::StaticClass()))
			{
				return;
			}

			RemoveEntity(InEntity);
		}
	}

protected:
	UPROPERTY()
	TObjectPtr<UInteractableWidgetEntity> LastSelectedEntity = nullptr;

	UPROPERTY()
	TObjectPtr<UInteractableWidgetEntity> SelectedEntity = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UInteractableWidgetEntity>> Entities;
};
