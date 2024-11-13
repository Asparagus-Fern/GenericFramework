// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackEditor/MovieSceneUMGTrackEditor.h"

#include "ClassViewerModule.h"
#include "ContentBrowserDelegates.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "LevelSequence.h"
#include "SequencerUtilities.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "Section/UMGSection.h"
#include "Styling/SlateIconFinder.h"
#include "Track/MovieSceneUMGTrack.h"
#include "Tracks/MovieSceneSpawnTrack.h"

#define LOCTEXT_NAMESPACE "UMGTrackEditor"

FMovieSceneUMGTrackEditor::FMovieSceneUMGTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{
}

TSharedRef<ISequencerTrackEditor> FMovieSceneUMGTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FMovieSceneUMGTrackEditor(InSequencer));
}

bool FMovieSceneUMGTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const
{
	return UMovieSceneUMGTrack::StaticClass() == TrackClass;
}

TSharedRef<ISequencerSection> FMovieSceneUMGTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding)
{
	return MakeShareable(new FUMGSection(SectionObject));
}

void FMovieSceneUMGTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder)
{
	auto SubMenuCallback = [this](FMenuBuilder& SubMenuBuilder)
	{
		SubMenuBuilder.AddWidget(CreateUMGAssetPicker(), FText::GetEmpty(), true);
	};

	MenuBuilder.AddSubMenu(
		LOCTEXT("AddUMGTrack", "UMG Track"),
		LOCTEXT("AddUMGTrackToolTip", "Adds a new track that controls parameters within a UMG."),
		FNewMenuDelegate::CreateLambda(SubMenuCallback),
		false,
		FSlateIconFinder::FindIconForClass(UUserWidget::StaticClass())
	);
}

TSharedPtr<SWidget> FMovieSceneUMGTrackEditor::BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params)
{
	return FSequencerUtilities::MakeAddButton(LOCTEXT("AddUMGWidget", "UMG Widget"), FOnGetContent(), Params.NodeIsHovered, GetSequencer());
}

TSharedRef<SWidget> FMovieSceneUMGTrackEditor::CreateUMGAssetPicker()
{
	UMovieSceneSequence* Sequence = GetSequencer().IsValid() ? GetSequencer()->GetFocusedMovieSceneSequence() : nullptr;

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	FAssetPickerConfig AssetPickerConfig;
	{
		AssetPickerConfig.SelectionMode = ESelectionMode::Single;
		AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateRaw(this, &FMovieSceneUMGTrackEditor::OnUMGAssetSelected);
		AssetPickerConfig.OnAssetEnterPressed = FOnAssetEnterPressed::CreateRaw(this, &FMovieSceneUMGTrackEditor::OnUMGAssetEnterPressed);
		AssetPickerConfig.bAllowNullSelection = false;
		AssetPickerConfig.bAddFilterUI = true;
		AssetPickerConfig.InitialAssetViewType = EAssetViewType::Tile;
		AssetPickerConfig.Filter.bRecursiveClasses = true;
		AssetPickerConfig.Filter.ClassPaths.Add(UUserWidgetBlueprint::StaticClass()->GetClassPathName());
		AssetPickerConfig.SaveSettingsName = TEXT("SequencerAssetPicker");
		AssetPickerConfig.AdditionalReferencingAssets.Add(FAssetData(Sequence));
	}

	return SNew(SBox)
		.WidthOverride(300.0f)
		.HeightOverride(300.f)
		[
			ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
		];
}

void FMovieSceneUMGTrackEditor::OnUMGAssetSelected(const FAssetData& InAssetData)
{
	FSlateApplication::Get().DismissAllMenus();
	UUserWidgetBlueprint* SelectedUMGAsset = Cast<UUserWidgetBlueprint>(InAssetData.GetAsset());
	UMovieScene* MovieScene = GetFocusedMovieScene();

	if (!SelectedUMGAsset || !MovieScene)
	{
		return;
	}

	if (MovieScene->IsReadOnly())
	{
		return;
	}

	if (IsUMGBindingExist(SelectedUMGAsset))
	{
		return;
	}

	AddUMGBinding(SelectedUMGAsset);
}

void FMovieSceneUMGTrackEditor::OnUMGAssetEnterPressed(const TArray<FAssetData>& InAssetData)
{
	if (InAssetData.Num() > 0)
	{
		OnUMGAssetSelected(InAssetData[0].GetAsset());
	}
}

bool FMovieSceneUMGTrackEditor::IsUMGBindingExist(UUserWidgetBlueprint* InUserWidgetBP)
{
	UMovieSceneSequence* Sequence = GetSequencer()->GetFocusedMovieSceneSequence();
	UMovieScene* MovieScene = Sequence->GetMovieScene();

	for (auto& MovieSceneBinding : MovieScene->GetBindings())
	{
		if (UUserWidget* BindingWidget = Cast<UUserWidget>(GetSequencer()->FindSpawnedObjectOrTemplate(MovieSceneBinding.GetObjectGuid())))
		{
			if (BindingWidget->GetClass() == InUserWidgetBP->GeneratedClass)
			{
				return true;
			}
		}
	}

	return false;
}

void FMovieSceneUMGTrackEditor::AddUMGBinding(UUserWidgetBlueprint* InUserWidgetBP)
{
	const FScopedTransaction Transaction(LOCTEXT("AddTrackDescription", "Add UMG Track"));
	
	UMovieSceneSequence* Sequence = GetSequencer()->GetFocusedMovieSceneSequence();
	UMovieScene* MovieScene = GetFocusedMovieScene();

	ULevelSequence* LevelSequence = Cast<ULevelSequence>(Sequence);

	MovieScene->Modify();

	FGuid BindingID = GetSequencer()->MakeNewSpawnable(*InUserWidgetBP);
	AddUMGBindingDefaultTrack(BindingID);

	// FGuid UserWidgetGuid = ActiveSequencer->CreateBinding(*InUserWidgetBP,InUserWidgetBP->GetName());

	// UMovieSceneUMGTrack* NewUMGTrack = 	InMovieScene->AddTrack<UMovieSceneUMGTrack>(UserWidgetGuid);
	// NewUMGTrack->UserWidgetBP = InUserWidgetBP;
	// NewUMGTrack->SetDisplayName(FText::FromString(InUserWidgetBP->GetName()));

	// FGuid BindingID = Sequence->CreateSpawnable(InUserWidgetBP);

	// FGuid BindingID = ActiveSequencer->CreateBinding(*InUserWidgetBP, InUserWidgetBP->GetName());
	// Sequence->BindPossessableObject(BindingID, *InUserWidgetBP, GetSequencer()->GetPlaybackContext());

	// FMovieSceneBinding* Binding = InMovieScene->FindBinding(BindingID);
	// if (UMovieSceneUMGTrack* Track = Cast<UMovieSceneUMGTrack>(InMovieScene->FindTrack(UMovieSceneUMGTrack::StaticClass(), BindingID, NAME_None)))
	// {
	// 	Track->UserWidgetBP = InUserWidgetBP;
	// 	Track->SetDisplayName(FText::FromString(InUserWidgetBP->GetName()));
	// }
}

void FMovieSceneUMGTrackEditor::AddUMGBindingDefaultTrack(FGuid BindingID)
{
	UMovieSceneSequence* Sequence = GetSequencer()->GetFocusedMovieSceneSequence();
	UMovieScene* MovieScene = GetFocusedMovieScene();
}

#undef LOCTEXT_NAMESPACE
