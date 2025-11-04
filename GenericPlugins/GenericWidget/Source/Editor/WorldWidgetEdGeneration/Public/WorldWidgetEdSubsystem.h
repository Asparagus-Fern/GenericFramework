// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorldWidgetSubsystem.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "WorldWidgetEdSubsystem.generated.h"

class SEditorWorldWidget;
class ILevelEditor;
class UGenericWidget;
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
class UWorldWidgetEdSubsystem : public UWorldWidgetSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FTickableGameObject */
protected:
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UWorldWidgetEdSubsystem, STATGROUP_Tickables); }
	virtual bool IsTickable() const override { return true; }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual void Tick(float DeltaTime) override;

	/* FCoreInternalManager */
protected:
	TArray<FEditorWorldWidget> EditorWorldWidgets;

	void OnPIEStarted(UGameInstance* GameInstance);
	void OnPIEEnded(UGameInstance* GameInstance);

	FDelegateHandle LevelEditorCreatedHandle;
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	FDelegateHandle LevelViewportClientListChangedHandle;
	void OnLevelViewportClientListChanged();

	FDelegateHandle OnBlueprintCompiledHandle;
	void OnBlueprintCompiled();

	void GenerateEditorWorldWidgets();

	void InitializeEditorWorldWidgets();
	void DeinitializeEditorWorldWidgets();

	virtual void RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent) override;
	virtual void UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent) override;

	virtual void AddWorldWidgetToScreen(UWorldWidgetComponent* InWorldWidgetComponent);
	virtual void RemoveWorldWidgetFromScreen(UWorldWidgetComponent* InWorldWidgetComponent);
};
