// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Manager/CoreInternalManager.h"
#include "Object/GamePanel.h"
#include "TrackEditor/MovieSceneUMGTrackEditor.h"
#include "MovieSceneUMGEdManager.generated.h"

class ILevelEditor;
class ISequencer;

/**
 * 
 */
UCLASS(MinimalAPI)
class UMovieSceneUMGPanel : public UGamePanel
{
	GENERATED_BODY()

	/* UGamePanel */
protected:
	virtual void HandleAddToViewport() override;
	virtual void HandleRemoveFromViewport() override;

public:
	FLevelEditorViewportClient* LevelEditorViewportClient = nullptr;
	virtual void RefreshMovieSceneUMG(TArray<UUserWidget*> InUserWidgets);
};

/**
 * 
 */
UCLASS()
class MOVIESCENEEDUTILITIES_API UMovieSceneUMGEdManager : public UEditorSubsystem, public FCoreInternalManager
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
