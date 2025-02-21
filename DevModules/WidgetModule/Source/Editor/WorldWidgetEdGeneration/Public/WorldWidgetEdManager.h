// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldWidgetManager.h"
#include "Common/CommonObject.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "WorldWidgetEdManager.generated.h"

class SEditorWorldWidget;
class ILevelEditor;
class UUserWidgetBase;
class SConstraintCanvas;

struct FEditorWorldWidget
{
public:
	FEditorWorldWidget();
	bool operator==(const FEditorWorldWidget& Other) const { return LevelEditorViewportClient == Other.LevelEditorViewportClient; }
	bool operator==(const FLevelEditorViewportClient* Other) const { return LevelEditorViewportClient == Other; }

public:
	uint8 bInitialized : 1;
	FLevelEditorViewportClient* LevelEditorViewportClient = nullptr;
	TSharedPtr<SConstraintCanvas> ConstraintCanvas = nullptr;
	TMap<UWorldWidgetComponent*, TSharedPtr<SEditorWorldWidget>> EditorWorldWidgets;
	TMap<UWorldWidgetComponent*, SConstraintCanvas::FSlot*> EditorWorldWidgetSlots;
};

/**
 * 
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
protected:
	virtual bool IsTickable() const override { return true; }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual void Tick(float DeltaTime) override;

	/* FCoreInternalManager */
protected:
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

protected:
	TArray<FEditorWorldWidget> EditorWorldWidgets;

	FDelegateHandle LevelEditorCreatedHandle;
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	FDelegateHandle LevelViewportClientListChangedHandle;
	void OnLevelViewportClientListChanged();

	void GenerateEditorWorldWidgets();

	void InitializeEditorWorldWidgets();
	void DeinitializeEditorWorldWidgets();

	virtual void RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent) override;
	virtual void UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent) override;

	virtual void AddWorldWidgetToScreen(UWorldWidgetComponent* InWorldWidgetComponent);
	virtual void RemoveWorldWidgetFromScreen(UWorldWidgetComponent* InWorldWidgetComponent);
};
