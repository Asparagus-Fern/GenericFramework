// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldWidgetManager.h"
#include "Manager/ManagerEdInterface.h"
#include "WorldWidgetEdManager.generated.h"

class SWorldWidgetContainer;
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

	/* FEditorWorldWidgetPanel */
public:
	TSharedPtr<SConstraintCanvas> ConstraintCanvas = nullptr;
	FLevelEditorViewportClient* LevelEditorViewportClient = nullptr;
	TMap<AWorldWidgetPoint*, TSharedPtr<SWorldWidgetContainer>> WorldWidgetContainer;

protected:
	virtual void RefreshWorldWidgetPoint() override;
	virtual void OnWorldWidgetDoubleClicked(TSharedPtr<SWorldWidgetContainer> DoubleClickedContainer);
};

/**
 * 
 */
UCLASS()
class WORLDWIDGETEDGENERATION_API UWorldWidgetEdManager : public UWorldWidgetManager, public IManagerEdInterface
{
	GENERATED_BODY()

public:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FTickableGameObject */
public:
	virtual bool IsTickableInEditor() const override { return true; }

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;

protected:
	FDelegateHandle LevelEditorCreatedHandle;
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	FDelegateHandle LevelActorAddedHandle;
	void OnLevelActorAdded(AActor* Actor);

	FDelegateHandle ActorsMovedHandle;
	void OnActorsMoved(TArray<AActor*>& Actors);

	FDelegateHandle LevelActorDeletedHandle;
	void OnLevelActorDeleted(AActor* InActor);

	FDelegateHandle BlueprintCompiledHandle;
	void OnBlueprintCompiled();

	FDelegateHandle BeginPIEHandle;
	void BeginPIE(bool bIsSimulating);

	FDelegateHandle EndPIEHandle;
	void EndPIE(bool bIsSimulating);

	FDelegateHandle WorldWidgetPointConstructHandle;
	void OnWorldWidgetPointConstruct(AWorldWidgetPoint* WorldWidgetPoint);

protected:
	bool bIsGenerateWorldWidgetPanel = false;

	virtual void GenerateWorldWidgetPanel() override;
	virtual UWorldWidgetPanel* CreateWorldWidgetPanel() override;
};
