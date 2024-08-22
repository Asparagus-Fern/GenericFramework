// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldWidgetManager.h"
#include "Manager/ManagerEdInterface.h"
#include "WorldWidgetEdManager.generated.h"

class UWorldWidgetEdManager;
class AWorldWidgetPoint;
class ILevelEditor;
class SConstraintCanvas;
class SLevelViewport;


/**
 * One Level Editor Viewport Client Has a Standalone Editor World Widget Panel
 * it will Created / Remove While :
 * 1. On Level Editor Created
 * 2. On Level Viewport Client List Changed
 * 3. On Editor Map Changed
 */
UCLASS()
class UEditorWorldWidgetPanel : public UWorldWidgetPanel
{
	GENERATED_BODY()

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* FEditorWorldWidgetPanel */
public:
	TSharedPtr<SConstraintCanvas> ConstraintCanvas;
	FLevelEditorViewportClient* LevelEditorViewportClient = nullptr;

protected:
	virtual bool AddPanelToViewport();
	virtual bool RemovePanelFromViewport();

	virtual void AddWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint) override;
	virtual void RemoveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint) override;

private:
	uint8 bRegisterInViewport : 1;
};

/**
 * 
 */
UCLASS()
class WORLDWIDGETEDGENERATION_API UWorldWidgetEdManager : public UWorldWidgetManager, public IManagerEdInterface
{
	GENERATED_BODY()

public:
	UWorldWidgetEdManager();
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FTickableGameObject */
public:
	virtual bool IsTickableInEditor() const override { return true; }

	/* IManagerInterface */
	// public:
	// 	virtual FText GetManagerDisplayName() override;
	// 	virtual bool DoesSupportWorldType(EWorldType::Type InWorldType) override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;

	/* IManagerEdInterface */
	// public:
	// virtual void NativeOnEditorActived() override;
	// virtual void NativeOnEditorInactived() override;

	/* UWorldWidgetEdManager */
protected:
	FDelegateHandle LevelEditorCreatedHandle;
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	/* 为每个LevelViewportClient创建Panel */
	FDelegateHandle LevelViewportClientListChangedHandle;
	void OnLevelViewportClientListChanged();

	FTimerHandle LevelViewportClientListChangedNextTickHandle;
	void HandleLevelViewportClientListChangedNextTick();

	/* 蓝图编译时更新 */
	FDelegateHandle BlueprintCompiledHandle;
	void OnBlueprintCompiled();

	/* 在Actor被删除时更新 */
	FDelegateHandle LevelActorDeletedHandle;
	void OnLevelActorDeleted(AActor* InActor);

	/* 在WorldWidgetPoint属性改变时更新 */
	FDelegateHandle WorldWidgetPointConstructionHandle;;
	void OnWorldWidgetPointConstruction(AWorldWidgetPoint* InWorldWidgetPoint);

	FDelegateHandle WorldWidgetPointDestroyedHandle;;
	void OnWorldWidgetPointDestroyed(AWorldWidgetPoint* InWorldWidgetPoint);

protected:
	uint8 bInitializeEditorWorldWidgetPanel : 1;
	TArray<FLevelEditorViewportClient*> HandleLevelEditorViewportClients;
	TMap<FLevelEditorViewportClient*, UWorldWidgetPanel*> EditorWorldWidgetPanelMapping;
	virtual void ReCreateEditorWorldWidgetPanel();
	virtual UEditorWorldWidgetPanel* CreateEditorWorldWidgetPanel(FLevelEditorViewportClient* InLevelEditorViewportClient);
	virtual void RemoveEditorWorldWidgetPanel(FLevelEditorViewportClient* InLevelEditorViewportClient);
	virtual void CollectWorldWidgetPoints();
};
