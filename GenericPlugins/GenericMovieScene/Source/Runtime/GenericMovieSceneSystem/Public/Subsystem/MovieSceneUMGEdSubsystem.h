// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "Interface/StateInterface.h"
#include "Obect/GenericObject.h"
#include "Track/MovieSceneUMGEdTrack.h"
#include "Subsystem/GenericEditorSubsystem.h"
#include "MovieSceneUMGEdSubsystem.generated.h"

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
class UMovieSceneUMGEdSubsystem : public UGenericEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	virtual void OnPIEStarted(UGameInstance* InGameInstance);
	virtual void OnPIEEnded(UGameInstance* InGameInstance);

protected:
#if WITH_EDITORONLY_DATA
	UPROPERTY(Transient)
	TArray<UMovieSceneUMGPanel*> MovieSceneUMGPanels;
#endif

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

#endif
