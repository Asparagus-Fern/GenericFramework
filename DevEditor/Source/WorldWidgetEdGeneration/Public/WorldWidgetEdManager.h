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
struct FEditorWorldWidgetPanel : public FWorldWidgetPanel
{
public:
	FEditorWorldWidgetPanel(UWorldWidgetEdManager* InOwner, FLevelEditorViewportClient* InLevelEditorViewportClient);
	virtual ~FEditorWorldWidgetPanel() override;

public:
	bool operator==(const FEditorWorldWidgetPanel Other) const { return LevelEditorViewportClient == Other.LevelEditorViewportClient; }
	bool operator==(const FLevelEditorViewportClient* OtherLevelEditorViewportClient) const { return LevelEditorViewportClient == OtherLevelEditorViewportClient; }

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
protected:
	TSharedPtr<SConstraintCanvas> ConstraintCanvas;
	FLevelEditorViewportClient* LevelEditorViewportClient = nullptr;

protected:
	virtual void AddPanelToViewport();
	virtual void RemovePanelFromViewport();

	virtual void AddWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint) override;
	virtual void RemoveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint) override;
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
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	static UWorldWidgetEdManager* Get();

	/* FTickableGameObject */
public:
	virtual bool IsTickableInEditor() const override { return true; }

	/* IManagerInterface */
public:
	virtual bool IsEditorManager() override { return true; }

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnRefresh() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UWorldWidgetEdManager */
protected:
	FDelegateHandle LevelEditorCreatedHandle;
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	/* 为每个LevelViewportClient创建Panel */
	FDelegateHandle LevelViewportClientListChangedHandle;
	void OnLevelViewportClientListChanged();

	/* 蓝图编译时更新 */
	FDelegateHandle BlueprintCompiledHandle;
	void OnBlueprintCompiled();

	/* 在Actor被删除时更新 */
	FDelegateHandle LevelActorDeletedHandle;
	void OnLevelActorDeleted(AActor* InActor);

	/* 在WorldWidgetPoint属性改变时更新 */
	FDelegateHandle WorldWidgetPointConstructionHandle;;
	void OnWorldWidgetPointConstruction(AWorldWidgetPoint* InWorldWidgetPoint);

protected:
	TMap<FLevelEditorViewportClient*, FWorldWidgetPanel*> EditorWorldWidgetPanelMapping;
	virtual void ReCreateEditorWorldWidgetPanel();
	virtual FEditorWorldWidgetPanel* CreateEditorWorldWidgetPanel(FLevelEditorViewportClient* InLevelEditorViewportClient);
	virtual void CollectWorldWidgetPoints();
};
