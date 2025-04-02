// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Generic/GenericObject.h"
#include "Interface/StateInterface.h"
#include "Manager/CoreInternalManager.h"
#include "TrackEditor/MovieSceneUMGTrackEditor.h"
#include "MovieSceneUMGEdManager.generated.h"

class SConstraintCanvas;
class ILevelEditor;
class ISequencer;

/**
 * 
 */
UCLASS(MinimalAPI)
class UMovieSceneUMGPanel : public UGenericObject, public IStateInterface
{
	GENERATED_BODY()

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* UGamePanel */
protected:
	virtual void HandleAddToViewport();
	virtual void HandleRemoveFromViewport();

public:
	FLevelEditorViewportClient* LevelEditorViewportClient = nullptr;
	virtual void RefreshMovieSceneUMG(TArray<UUserWidget*> InUserWidgets);

protected:
	TSharedPtr<SConstraintCanvas> ConstraintCanvas = nullptr;
};

/**
 * 
 */
UCLASS(MinimalAPI)
class UMovieSceneUMGEdManager : public UEditorSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/* FCoreInternalManager */
public:
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

protected:
	UPROPERTY(Transient)
	TArray<UMovieSceneUMGPanel*> MovieSceneUMGPanels;

	FDelegateHandle LevelEditorCreatedHandle;
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	FDelegateHandle LevelViewportClientListChangedHandle;
	void OnLevelViewportClientListChanged();

public:
	/* 创建Editor下LevelSequence的UMG面板 */
	void GenerateMovieSceneUMGPanels();

	/* 销毁Editor下LevelSequence的UMG面板 */
	void DestroyMovieSceneUMGPanels();

	/* 刷新Editor下LevelSequence的UMG面板 */
	void RefreshMovieSceneUMGPanels();

protected:
	virtual UMovieSceneUMGPanel* CreateMovieSceneUMGPanel();

private:
	TArray<TWeakPtr<ISequencer>> Sequencers;
	FDelegateHandle OnSequencerCreatedHandle;
	void OnSequencerCreated(TSharedRef<ISequencer> InSequencer);
	void OnSequencerClosed(TSharedRef<ISequencer> InSequencer);
	void OnGlobalTimeChanged();
};
