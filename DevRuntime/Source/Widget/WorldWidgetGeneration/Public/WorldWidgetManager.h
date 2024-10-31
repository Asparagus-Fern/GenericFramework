// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
public:
	/* 注册一个3DUI点位 */
	virtual void RegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);

	/* 反注册一个3DUI点位 */
	virtual void UnRegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);

	TArray<AWorldWidgetPoint*> GetWorldWidgetPoints() { return WorldWidgetPoints; }

	AWorldWidgetPoint* FindWorldWidgetPoint(FGameplayTag PointTag);

	TArray<AWorldWidgetPoint*> FindWorldWidgetPoints(FGameplayTag PointTag);

protected:
	UPROPERTY(Transient)
	TArray<AWorldWidgetPoint*> WorldWidgetPoints;

	UPROPERTY(Transient)
	TArray<UWorldWidgetPanel*> WorldWidgetPanels;

protected:
	/* 在HUD创建之后创建3DUI面板 */
	virtual void GenerateWorldWidgetPanel();

	/* 创建3DUI面板 */
	virtual UWorldWidgetPanel* CreateWorldWidgetPanel();

	/* 刷新所有的3DUI面板 */
	virtual void RefreshWorldWidgetPanel();

	/* 移除指定3DUI面板 */
	virtual void RemoveWorldWidgetPanel(UWorldWidgetPanel* InWorldWidgetPanel);

	/* 清除所有3DUI面板 */
	virtual void ClearupWorldWidgetPanel();

	/* 尝试将一个3DUI添加到3DUI面板 */
	virtual void TryToAddWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);

	/* 尝试将一个3DUI从3DUI面板移除 */
	virtual void TryToRemoveWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);
};
