// Copyright ChenTaiye 2025. All Rights Reserved.

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

#define LOCTEXT_NAMESPACE "FMovieSceneEdUtilitiesModule"

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
	/* 仅在LevelSequence可使用 */
	if (!IsValid(Cast<ULevelSequence>(GetSequencer()->GetFocusedMovieSceneSequence())))
	{
		return;
	}

	/* 在MasterTrack中添加一个UI来添加UMG Track */
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

	/* 创建资产筛选器，选择UMG添加进Sequence */
	return SNew(SBox)
		.WidthOverride(300.0f)
		.HeightOverride(300.f)
		[
			ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
		];
}

void FMovieSceneUMGTrackEditor::OnUMGAssetSelected(const FAssetData& InAssetData)
{
	/* 关闭所有菜单 */
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

	/* 当UMG Binding存在时，不再重复绑定 */
	if (IsUMGBindingExist(SelectedUMGAsset))
	{
		//todo:选中该Binding?
		return;
	}

	/* 添加一个UMG Binding */
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

	/* 从Movie Scene UMG Spawner创建UMG */
	GetFocusedMovieScene()->Modify();
	GetSequencer()->MakeNewSpawnable(*InUserWidgetBP);
}

#undef LOCTEXT_NAMESPACE
