// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreManager.h"
#include "WorldWidgetManager.generated.h"

class UUserWidgetBase;
class UWorldWidgetManager;
class UCanvasPanel;
class AWorldWidgetPoint;

/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UWorldWidgetPanel : public UCommonObject, public IProcedureBaseInterface
{
	GENERATED_BODY()

	friend UWorldWidgetManager;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

	/* FWorldWidgetPanel */
protected:
	UPROPERTY()
	UCanvasPanel* Panel;

	UPROPERTY()
	TMap<AWorldWidgetPoint*, UUserWidgetBase*> WorldWidgets;

public:
	UCanvasPanel* GetPanel() const { return Panel; }
	TMap<AWorldWidgetPoint*, UUserWidgetBase*> GetWorldWidgets() { return WorldWidgets; }

protected:
	virtual void AddWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RemoveWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RefreshWorldWidgetPoint();
};


/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UWorldWidgetManager : public UCoreManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/* FTickableGameObject */
public:
	virtual bool IsTickable() const override { return true; }

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnRefresh() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UWorldWidgetManager */
protected:
	UPROPERTY(Transient)
	TArray<AWorldWidgetPoint*> WorldWidgetPoints;

	UPROPERTY(Transient)
	TArray<UWorldWidgetPanel*> WorldWidgetPanels;

protected:
	/* 在HUD创建之后创建3DUI面板 */
	UFUNCTION()
	virtual void GenerateWorldWidgetPanel();

	virtual UWorldWidgetPanel* CreateWorldWidgetPanel();
	virtual void RefreshWorldWidgetPanel();
	virtual void RemoveWorldWidgetPanel(UWorldWidgetPanel* InWorldWidgetPanel);
	virtual void ClearupWorldWidgetPanel();

	virtual void RegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);
	virtual void UnRegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);

	virtual void TryToAddWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);
	virtual void TryToRemoveWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);
};
