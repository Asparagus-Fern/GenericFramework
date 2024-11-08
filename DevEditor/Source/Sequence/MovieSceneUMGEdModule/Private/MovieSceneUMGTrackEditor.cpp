// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieSceneUMGTrackEditor.h"

#include "ClassViewerModule.h"
#include "ContentBrowserDelegates.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "MovieSceneUMGTrack.h"
#include "SequencerUtilities.h"
#include "UMGSection.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "Styling/SlateIconFinder.h"

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
	const FOnGetContent MenuContent = FOnGetContent::CreateSP(this, &FMovieSceneUMGTrackEditor::CreateUMGAssetPicker);
	return FSequencerUtilities::MakeAddButton(LOCTEXT("AddUMGWidget", "UMG Widget"), MenuContent, Params.NodeIsHovered, GetSequencer());
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

	UMovieSceneUMGTrack* Track = GetOrAddMovieSceneUMGTrack(MovieScene, SelectedUMGAsset);
	check(Track);

	if (GetSequencer().IsValid())
	{
		GetSequencer()->OnAddTrack(Track, FGuid());
	}
}

void FMovieSceneUMGTrackEditor::OnUMGAssetEnterPressed(const TArray<FAssetData>& InAssetData)
{
	if (InAssetData.Num() > 0)
	{
		OnUMGAssetSelected(InAssetData[0].GetAsset());
	}
}

UMovieSceneUMGTrack* FMovieSceneUMGTrackEditor::GetOrAddMovieSceneUMGTrack(UMovieScene* InMovieScene, UUserWidgetBlueprint* InUserWidgetBP)
{
	UMovieSceneUMGTrack* UMGMasterTrack = nullptr;

	for (UMovieSceneTrack* Track : InMovieScene->GetTracks())
	{
		UMGMasterTrack = Cast<UMovieSceneUMGTrack>(Track);
		if (IsValid(UMGMasterTrack))
		{
			return UMGMasterTrack;
		}
	}

	InMovieScene->Modify();

	const FScopedTransaction Transaction(LOCTEXT("AddTrackDescription", "Add UMG Track"));
	UMGMasterTrack = InMovieScene->AddTrack<UMovieSceneUMGTrack>();
	UMGMasterTrack->AddMovieSceneUMGSection(GetTimeForKey(), InUserWidgetBP);

	return UMGMasterTrack;
}

#undef LOCTEXT_NAMESPACE
