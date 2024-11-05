// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreManager.h"
#include "WorldWidgetManager.generated.h"

class UWorldWidgetComponent;
class UUserWidgetBase;
class UWorldWidgetManager;
class UCanvasPanel;
class UWorldWidgetComponent;

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
	TMap<UWorldWidgetComponent*, UUserWidgetBase*> WorldWidgets;

public:
	UCanvasPanel* GetPanel() const { return Panel; }
	TMap<UWorldWidgetComponent*, UUserWidgetBase*> GetWorldWidgets() { return WorldWidgets; }

protected:
	/* 添加一个WorldWidget进入该Panel */
	virtual void AddWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	/* 从该Panel移除一个WorldWidget */
	virtual void RemoveWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	/* 刷新该Panel的所有WorldWidget */
	virtual void RefreshWorldWidgetComponent();
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
	virtual void RegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetPoint);

	/* 反注册一个3DUI点位 */
	virtual void UnRegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetPoint);

	TArray<UWorldWidgetComponent*> GetWorldWidgetComponents() { return WorldWidgetComponents; }

	UWorldWidgetComponent* FindWorldWidgetComponent(FGameplayTag WorldWidgetTag);

	TArray<UWorldWidgetComponent*> FindWorldWidgetComponents(FGameplayTag WorldWidgetTag);

protected:
	UPROPERTY(Transient)
	TArray<UWorldWidgetComponent*> WorldWidgetComponents;

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
	virtual void TryToAddWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetComponent);

	/* 尝试将一个3DUI从3DUI面板移除 */
	virtual void TryToRemoveWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetComponent);
};
