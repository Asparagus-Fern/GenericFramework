// Copyright ChenTaiye 2025. All Rights Reserved.

#include "MovieSceneUMGEdSubsystem.h"

#include "ISequencerModule.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "LevelSequence.h"
#include "Blueprint/UserWidget.h"
#include "BPFunctions/BPFunctions_EditorWidget.h"
#include "Sections/MovieSceneBoolSection.h"
#include "Tracks/MovieSceneSpawnTrack.h"
#include "Widgets/Layout/SConstraintCanvas.h"

void UMovieSceneUMGPanel::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();

	ConstraintCanvas = SNew(SConstraintCanvas);
	HandleAddToViewport();
}

void UMovieSceneUMGPanel::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();

	ConstraintCanvas->ClearChildren();
	HandleRemoveFromViewport();
}

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

void UMovieSceneUMGEdSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UMovieSceneUMGEdSubsystem::OnLevelEditorCreated);

	LevelViewportClientListChangedHandle = GEditor->OnLevelViewportClientListChanged().AddUObject(this, &UMovieSceneUMGEdSubsystem::OnLevelViewportClientListChanged);

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	OnSequencerCreatedHandle = SequencerModule.RegisterOnSequencerCreated(FOnSequencerCreated::FDelegate::CreateUObject(this, &UMovieSceneUMGEdSubsystem::OnSequencerCreated));

	FWorldDelegates::OnPIEStarted.AddUObject(this, &UMovieSceneUMGEdSubsystem::OnPIEStarted);
	FWorldDelegates::OnPIEEnded.AddUObject(this, &UMovieSceneUMGEdSubsystem::OnPIEEnded);
}

void UMovieSceneUMGEdSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FWorldDelegates::OnPIEStarted.RemoveAll(this);
	FWorldDelegates::OnPIEEnded.RemoveAll(this);

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnregisterOnSequencerCreated(OnSequencerCreatedHandle);

	LevelEditorCreatedHandle.Reset();
	LevelViewportClientListChangedHandle.Reset();
}

void UMovieSceneUMGEdSubsystem::OnPIEStarted(UGameInstance* InGameInstance)
{
	DestroyMovieSceneUMGPanels();
}

void UMovieSceneUMGEdSubsystem::OnPIEEnded(UGameInstance* InGameInstance)
{
	GenerateMovieSceneUMGPanels();
}

void UMovieSceneUMGEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	DestroyMovieSceneUMGPanels();
	GenerateMovieSceneUMGPanels();
}

void UMovieSceneUMGEdSubsystem::OnLevelViewportClientListChanged()
{
	DestroyMovieSceneUMGPanels();
	GenerateMovieSceneUMGPanels();
}

void UMovieSceneUMGEdSubsystem::GenerateMovieSceneUMGPanels()
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

void UMovieSceneUMGEdSubsystem::DestroyMovieSceneUMGPanels()
{
	for (const auto& MovieSceneUMGPanel : MovieSceneUMGPanels)
	{
		MovieSceneUMGPanel->NativeOnDestroy();
		MovieSceneUMGPanel->MarkAsGarbage();
	}

	MovieSceneUMGPanels.Reset();
}

UMovieSceneUMGPanel* UMovieSceneUMGEdSubsystem::CreateMovieSceneUMGPanel()
{
	UMovieSceneUMGPanel* NewMovieSceneUMGPanel = NewObject<UMovieSceneUMGPanel>(this);
	MovieSceneUMGPanels.Add(NewMovieSceneUMGPanel);

	return NewMovieSceneUMGPanel;
}

void UMovieSceneUMGEdSubsystem::RefreshMovieSceneUMGPanels()
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

void UMovieSceneUMGEdSubsystem::OnSequencerCreated(TSharedRef<ISequencer> InSequencer)
{
	InSequencer->OnCloseEvent().AddUObject(this, &UMovieSceneUMGEdSubsystem::OnSequencerClosed);
	InSequencer->OnGlobalTimeChanged().AddUObject(this, &UMovieSceneUMGEdSubsystem::OnGlobalTimeChanged);

	Sequencers.Add(TWeakPtr<ISequencer>(InSequencer));
	RefreshMovieSceneUMGPanels();
}

void UMovieSceneUMGEdSubsystem::OnSequencerClosed(TSharedRef<ISequencer> InSequencer)
{
	InSequencer->OnCloseEvent().RemoveAll(this);
	InSequencer->OnGlobalTimeChanged().RemoveAll(this);

	Sequencers.Remove(InSequencer);
	RefreshMovieSceneUMGPanels();
}

void UMovieSceneUMGEdSubsystem::OnGlobalTimeChanged()
{
	RefreshMovieSceneUMGPanels();
}
