// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieSceneUMGEdManager.h"

#include "ISequencerModule.h"
#include "ISequencerObjectChangeListener.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "LevelSequence.h"
#include "MovieSceneUMGEdManagerSetting.h"
#include "Blueprint/UserWidget.h"
#include "BPFunctions/BPFunctions_EditorWidget.h"
#include "Debug/DebugType.h"
#include "Sections/MovieSceneBoolSection.h"
#include "Tracks/MovieSceneSpawnTrack.h"
#include "Widgets/Layout/SConstraintCanvas.h"

class ILevelSequenceModule;

void UMovieSceneUMGPanel::HandleAddToViewport()
{
	if (LevelEditorViewportClient)
	{
		UBPFunctions_EditorWidget::AddToEditorViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}
}

void UMovieSceneUMGPanel::HandleRemoveFromViewport()
{
	if (LevelEditorViewportClient)
	{
		UBPFunctions_EditorWidget::RemoveFromEditorViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}
}

void UMovieSceneUMGPanel::RefreshMovieSceneUMG(TArray<UUserWidget*> InUserWidgets)
{
	if (ConstraintCanvas.IsValid())
	{
		ConstraintCanvas->ClearChildren();
	}

	for (const auto& UserWidget : InUserWidgets)
	{
		if (!IsValid(UserWidget))
		{
			continue;
		}

		ConstraintCanvas->AddSlot()
			.AutoSize(true)
			.Anchors(FAnchors(0.f, 0.f, 1.f, 1.f))
			.Alignment(FVector2D())
			.Offset(FMargin())
			.ZOrder(0)
			[
				UserWidget->TakeWidget()
			];
	}
}

bool UMovieSceneUMGEdManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UMovieSceneUMGEdManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UMovieSceneUMGEdManager::OnLevelEditorCreated);

	LevelViewportClientListChangedHandle = GEditor->OnLevelViewportClientListChanged().AddUObject(this, &UMovieSceneUMGEdManager::OnLevelViewportClientListChanged);

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	OnSequencerCreatedHandle = SequencerModule.RegisterOnSequencerCreated(FOnSequencerCreated::FDelegate::CreateUObject(this, &UMovieSceneUMGEdManager::OnSequencerCreated));
}

void UMovieSceneUMGEdManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnregisterOnSequencerCreated(OnSequencerCreatedHandle);

	LevelEditorCreatedHandle.Reset();
	LevelViewportClientListChangedHandle.Reset();
}

void UMovieSceneUMGEdManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldBeginPlay(InWorld);
	DestroyMovieSceneUMGPanels();
}

void UMovieSceneUMGEdManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);
	GenerateMovieSceneUMGPanels();
}

void UMovieSceneUMGEdManager::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	DestroyMovieSceneUMGPanels();
	GenerateMovieSceneUMGPanels();
}

void UMovieSceneUMGEdManager::OnLevelViewportClientListChanged()
{
	DestroyMovieSceneUMGPanels();
	GenerateMovieSceneUMGPanels();
}

void UMovieSceneUMGEdManager::GenerateMovieSceneUMGPanels()
{
	for (const auto& LevelEditorViewportClient : UBPFunctions_EditorWidget::GetLevelEditorViewportClients())
	{
		/* 添加到LevelEditorViewport */
		if (UMovieSceneUMGPanel* EditorWorldWidgetPanel = Cast<UMovieSceneUMGPanel>(CreateMovieSceneUMGPanel()))
		{
			EditorWorldWidgetPanel->LevelEditorViewportClient = LevelEditorViewportClient;
			EditorWorldWidgetPanel->NativeOnCreate();
		}
	}

	RefreshMovieSceneUMGPanels();
}

void UMovieSceneUMGEdManager::DestroyMovieSceneUMGPanels()
{
	for (const auto& MovieSceneUMGPanel : MovieSceneUMGPanels)
	{
		MovieSceneUMGPanel->NativeOnDestroy();
		MovieSceneUMGPanel->MarkAsGarbage();
	}

	MovieSceneUMGPanels.Reset();
}

UMovieSceneUMGPanel* UMovieSceneUMGEdManager::CreateMovieSceneUMGPanel()
{
	UMovieSceneUMGPanel* NewMovieSceneUMGPanel = NewObject<UMovieSceneUMGPanel>(this);
	MovieSceneUMGPanels.Add(NewMovieSceneUMGPanel);

	return NewMovieSceneUMGPanel;
}

void UMovieSceneUMGEdManager::RefreshMovieSceneUMGPanels()
{
	/* 需要刷新的Widget */
	TArray<UUserWidget*> UserWidgets;
	for (auto& Sequencer : Sequencers)
	{
		if (!Sequencer.IsValid())
		{
			continue;
		}

		if (const ULevelSequence* LevelSequence = Cast<ULevelSequence>(Sequencer.Pin()->GetFocusedMovieSceneSequence()))
		{
			const UMovieScene* MovieScene = LevelSequence->GetMovieScene();

			/* 遍历查找UMG Binding */
			for (auto& Binding : MovieScene->GetBindings())
			{
				UUserWidget* UserWidget = Cast<UUserWidget>(Sequencer.Pin()->FindSpawnedObjectOrTemplate(Binding.GetObjectGuid()));
				UMovieSceneSpawnTrack* MovieSceneSpawnTrack = Cast<UMovieSceneSpawnTrack>(MovieScene->FindTrack(UMovieSceneSpawnTrack::StaticClass(), Binding.GetObjectGuid(), NAME_None));

				if (!IsValid(UserWidget))
				{
					continue;
				}

				/* 没有Spawn Track默认为不生成 */
				if (!IsValid(MovieSceneSpawnTrack))
				{
					continue;
				}

				/* 从Spawn Track评估当前时间是否生成该Widget */
				for (auto& Section : MovieSceneSpawnTrack->GetAllSections())
				{
					if (UMovieSceneBoolSection* SpawnSection = Cast<UMovieSceneBoolSection>(Section))
					{
						bool bIsSpawn;
						const FFrameTime FrameTime = Sequencer.Pin()->GetGlobalTime().Time;

						/* 评估成功且生成 */
						if (SpawnSection->GetChannel().Evaluate(FrameTime, bIsSpawn) && bIsSpawn)
						{
							UserWidgets.Add(UserWidget);
						}
					}
				}
			}
		}
	}

	/* 刷新Panel */
	for (const auto& MovieSceneUMGPanel : MovieSceneUMGPanels)
	{
		MovieSceneUMGPanel->RefreshMovieSceneUMG(UserWidgets);
	}
}

void UMovieSceneUMGEdManager::OnSequencerCreated(TSharedRef<ISequencer> InSequencer)
{
	InSequencer->OnCloseEvent().AddUObject(this, &UMovieSceneUMGEdManager::OnSequencerClosed);
	InSequencer->OnGlobalTimeChanged().AddUObject(this, &UMovieSceneUMGEdManager::OnGlobalTimeChanged);

	Sequencers.Add(TWeakPtr<ISequencer>(InSequencer));
	RefreshMovieSceneUMGPanels();
}

void UMovieSceneUMGEdManager::OnSequencerClosed(TSharedRef<ISequencer> InSequencer)
{
	InSequencer->OnCloseEvent().RemoveAll(this);
	InSequencer->OnGlobalTimeChanged().RemoveAll(this);

	Sequencers.Remove(InSequencer);
	RefreshMovieSceneUMGPanels();
}

void UMovieSceneUMGEdManager::OnGlobalTimeChanged()
{
	RefreshMovieSceneUMGPanels();
}
