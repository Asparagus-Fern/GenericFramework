// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableWidgetEntity.h"
#include "Common/CommonObject.h"
#include "Interface/StateInterface.h"
#include "InteractableWidgetEntityGroup.generated.h"

class UInteractableWidgetEntity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGroupEntityEvent, UInteractableWidgetEntity*, InEntity);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGroupEntitySelectionChanged, UInteractableWidgetEntity*, InEntity, bool, Selection);

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
	void AddWidgets(TArray<UInteractableWidgetBase*> InWidgets);

	UFUNCTION(BlueprintCallable)
	void AddWidget(UInteractableWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable)
	void RemoveEntities(TArray<UInteractableWidgetEntity*> InEntities);

	UFUNCTION(BlueprintCallable)
	void RemoveEntity(UInteractableWidgetEntity* InEntity);

	UFUNCTION(BlueprintCallable)
	void RemoveEntityByIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	void RemoveWidgets(TArray<UInteractableWidgetBase*> InWidgets);

	UFUNCTION(BlueprintCallable)
	void RemoveWidget(UInteractableWidgetBase* InWidget);

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
	virtual void HandleOnEntityPressed(UInteractableWidgetEntity* InEntity);
	virtual void HandleOnEntityReleased(UInteractableWidgetEntity* InEntity);
	virtual void HandleOnEntityHovered(UInteractableWidgetEntity* InEntity);
	virtual void HandleOnEntityUnhovered(UInteractableWidgetEntity* InEntity);
	virtual void HandleOnEntityClicked(UInteractableWidgetEntity* InEntity);
	virtual void HandleOnEntityDoubleClicked(UInteractableWidgetEntity* InEntity);
	virtual void HandleOnEntitySelectionChanged(UInteractableWidgetEntity* InEntity, bool Selection);

public:
	UPROPERTY(BlueprintAssignable)
	FGroupEntityEvent OnEntityPressed;

	UPROPERTY(BlueprintAssignable)
	FGroupEntityEvent OnEntityReleased;

	UPROPERTY(BlueprintAssignable)
	FGroupEntityEvent OnEntityHovered;

	UPROPERTY(BlueprintAssignable)
	FGroupEntityEvent OnEntityUnhovered;

	UPROPERTY(BlueprintAssignable)
	FGroupEntityEvent OnEntityClicked;

	UPROPERTY(BlueprintAssignable)
	FGroupEntityEvent OnEntityDoubleClicked;

	UPROPERTY(BlueprintAssignable)
	FGroupEntitySelectionChanged OnEntitySelectionChanged;

protected:
	UPROPERTY()
	TObjectPtr<UInteractableWidgetEntity> LastSelectedEntity = nullptr;

	UPROPERTY()
	TObjectPtr<UInteractableWidgetEntity> SelectedEntity = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UInteractableWidgetEntity>> Entities;
};
