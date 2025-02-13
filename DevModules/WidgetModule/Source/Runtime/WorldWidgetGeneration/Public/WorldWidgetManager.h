// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WorldWidgetComponent.h"
#include "Common/ViewportPanel.h"
#include "Manager/TickableInternalManager.h"
#include "WorldWidgetManager.generated.h"

class UWorldWidgetComponent;
class UUserWidgetBase;
class UWorldWidgetManager;
class UCanvasPanel;
class UWorldWidgetComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWorldWidgetComponentRegister, UWorldWidgetComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWorldWidgetComponentRegister, UWorldWidgetComponent*, InWorldWidgetComponent);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnWorldWidgetComponentActiveStateChanged, UWorldWidgetComponent*, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnWorldWidgetComponentActiveStateChanged, UWorldWidgetComponent*, InWorldWidgetComponent, bool, IsActive);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWorldWidgetComponentUnRegister, UWorldWidgetComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWorldWidgetComponentUnRegister, UWorldWidgetComponent*, InWorldWidgetComponent);

/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UWorldWidgetPanel : public UViewportPanel
{
	GENERATED_BODY()

	friend UWorldWidgetManager;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

	/* UGamePanel */
public:
	virtual void HandleAddToViewport() override;
	virtual void HandleRemoveFromViewport() override;

	/* FWorldWidgetPanel */
protected:
	UPROPERTY()
	TMap<UWorldWidgetComponent*, UUserWidgetBase*> WorldWidgets;

public:
	TMap<UWorldWidgetComponent*, UUserWidgetBase*> GetWorldWidgets() { return WorldWidgets; }

	virtual bool IsContain(UWorldWidgetComponent* InWorldWidgetComponent);

	virtual void AddWorldWidgetComponent(AActor* InActor);

	/* 添加一个WorldWidget进入该Panel */
	virtual void AddWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	/* 从该Panel移除一个WorldWidget */
	virtual void RemoveWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	/* 刷新该Panel的一个WorldWidget */
	virtual void RefreshWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	/* 刷新该Panel的所有WorldWidget */
	virtual void RefreshAllWorldWidgetComponent();
};


/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UWorldWidgetManager : public UWorldSubsystem, public FTickableInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FTickableGameObject */
public:
	virtual bool IsTickable() const override { return true; }
	virtual void Tick(float DeltaTime) override;

	/* FCoreInternalManager */
public:
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* UWorldWidgetManager */
public:
	TArray<UWorldWidgetComponent*> GetWorldWidgetComponents() { return WorldWidgetComponents; }

	TArray<UWorldWidgetComponent*> GetWorldWidgetComponents2D();

	TArray<UWorldWidgetComponent*> GetWorldWidgetComponents3D();

	UWorldWidgetComponent* FindWorldWidgetComponent(FGameplayTag WorldWidgetTag);

	TArray<UWorldWidgetComponent*> FindWorldWidgetComponents(FGameplayTag WorldWidgetTag);

	void SetWorldWidgetComponentActiveState(AActor* InActor, bool IsActive);

	void SetWorldWidgetComponentActiveState(UWorldWidgetComponent* InWorldWidgetComponent, bool IsActive);

	void SetWorldWidgetPaintMethod(UWorldWidgetComponent* InWorldWidgetComponent, EWorldWidgetPaintMethod WorldWidgetPaintMethod);

	void SetWorldWidgetLookAtSetting(UWorldWidgetComponent* InWorldWidgetComponent, FWorldWidgetLookAtSetting WorldWidgetLookAtSetting);

public:
	inline static FDelegate_OnWorldWidgetComponentRegister Delegate_OnWorldWidgetComponentRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentRegister BPDelegate_OnWorldWidgetComponentRegister;

	inline static FDelegate_OnWorldWidgetComponentActiveStateChanged Delegate_OnWorldWidgetComponentActiveStateChanged;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentActiveStateChanged BPDelegate_OnWorldWidgetComponentActiveStateChanged;

	inline static FDelegate_OnWorldWidgetComponentUnRegister Delegate_OnWorldWidgetComponentUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWorldWidgetComponentUnRegister BPDelegate_OnWorldWidgetComponentUnRegister;

protected:
	UPROPERTY(Transient)
	TArray<UWorldWidgetComponent*> WorldWidgetComponents;

	UPROPERTY(Transient)
	TArray<UWorldWidgetPanel*> WorldWidgetPanels;

protected:
	virtual void RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	virtual void UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	virtual void TryToAddWorldWidgetComponent(AActor* InActor);

	virtual void TryToAddWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	virtual void TryToRemoveWorldWidgetComponent(AActor* InActor);

	virtual void TryToRemoveWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent);

	virtual void RefreshWorldWidgetComponents2DLookAtRotation(TArray<UWorldWidgetComponent*> InWorldWidgetComponents);

	virtual void RefreshWorldWidgetComponents3DLookAtRotation(TArray<UWorldWidgetComponent*> InWorldWidgetComponents);

	virtual void RefreshAllWorldWidgetComponents();

	/* 2D */
protected:
	/* Generate World Widget Panel Post HUD Created */
	virtual void GenerateWorldWidgetPanel();

	/* Create Panel */
	virtual UWorldWidgetPanel* CreateWorldWidgetPanel();

	/* Remove Panel */
	virtual void RemoveWorldWidgetPanel(UWorldWidgetPanel* InWorldWidgetPanel);

	/* Clear All Panel */
	virtual void ClearAllWorldWidgetPanel();
};
