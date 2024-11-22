// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldWidgetManager.h"
#include "WorldWidgetEdManager.generated.h"

class SWorldWidgetContainer;
class UWorldWidgetEdManager;
class UWorldWidgetComponent;
class ILevelEditor;
class SConstraintCanvas;
class SLevelViewport;


/**
 * 将WorldWidget显示Level Editor Viewport的面板
 */
UCLASS(MinimalAPI)
class UEditorWorldWidgetPanel : public UWorldWidgetPanel
{
	GENERATED_BODY()

	friend UWorldWidgetEdManager;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

	/* UGamePanel */
public:
	virtual void HandleAddToViewport() override;
	virtual void HandleRemoveFromViewport() override;

	/* FEditorWorldWidgetPanel */
public:
	FLevelEditorViewportClient* LevelEditorViewportClient = nullptr;
	TMap<UWorldWidgetComponent*, TSharedPtr<SWorldWidgetContainer>> WorldWidgetContainer;

protected:
	virtual void AddWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent) override;
	virtual void RemoveWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent) override;
	virtual void RefreshWorldWidgetComponent() override;

	virtual void OnWorldWidgetMiddleClicked(TSharedPtr<SWorldWidgetContainer> DoubleClickedContainer);
};

/**
 * WorldWidget在编辑器的管理类，将WorldWidget显示在编辑器视口
 */
UCLASS(MinimalAPI)
class UWorldWidgetEdManager : public UWorldWidgetManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FTickableGameObject */
public:
	virtual bool IsTickableInEditor() const override { return true; }

	/* FCoreInternalManager */
public:
	virtual void OnWorldBeginPlay(UWorld* InWorld) override;
	virtual void OnWorldEndPlay(UWorld* InWorld) override;

protected:
	/* 编辑器创建时 */
	FDelegateHandle LevelEditorCreatedHandle;
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	FDelegateHandle LevelViewportClientListChangedHandle;
	void OnLevelViewportClientListChanged();
	
	/* 关卡添加Actor时 */
	FDelegateHandle LevelActorAddedHandle;
	void OnLevelActorAdded(AActor* Actor);

	/* Actor被移动时 */
	FDelegateHandle ActorsMovedHandle;
	void OnActorsMoved(TArray<AActor*>& Actors);

	/* Actor被删除时 */
	FDelegateHandle LevelActorDeletedHandle;
	void OnLevelActorDeleted(AActor* InActor);

	/* 蓝图编译时 */
	FDelegateHandle BlueprintCompiledHandle;
	void OnBlueprintCompiled();

	FDelegateHandle LevelsChangedHandle;
	void OnLevelsChanged();
	
	/* WorldWidgetComponent注册时 */
	FDelegateHandle WorldWidgetComponentRegisterHandle;
	void OnWorldWidgetComponentRegister(UWorldWidgetComponent* WorldWidgetComponent);

protected:
	virtual void GenerateWorldWidgetPanel() override;
	virtual UWorldWidgetPanel* CreateWorldWidgetPanel() override;
};
