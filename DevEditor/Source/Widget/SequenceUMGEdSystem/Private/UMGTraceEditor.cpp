#include "UMGTraceEditor.h"

#include "MovieSceneUMGSection.h"
#include "MovieSceneSpawnableAnnotation.h"
#include "WidgetBlueprint.h"

#define LOCTEXT_NAMESPACE "UMGTrackEditor"

FUMGTraceEditor::FUMGTraceEditor(TSharedRef<ISequencer> InSequencer)
	: FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())
{
}

TSharedRef<ISequencerTrackEditor> FUMGTraceEditor::CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer)
{
	return MakeShared<FUMGTraceEditor>(OwningSequencer);
}

TArray<FAnimatedPropertyKey, TInlineAllocator<1>> FUMGTraceEditor::GetAnimatedPropertyTypes()
{
	FAnimatedPropertyKey Key = FAnimatedPropertyKey::FromPropertyType(FSoftObjectProperty::StaticClass());
	Key.ObjectTypeName = UWidgetBlueprint::StaticClass()->GetFName();

	return TArray<FAnimatedPropertyKey, TInlineAllocator<1>>({Key, FAnimatedPropertyKey::FromObjectType(UWidgetBlueprint::StaticClass())});
}

void FUMGTraceEditor::GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys)
{
	UWidgetBlueprint* NewReferencedActor = Cast<UWidgetBlueprint>(PropertyChangedParams.GetPropertyValue<UObject*>());
	if ( NewReferencedActor != nullptr )
	{
		TSharedPtr<ISequencer> SequencerPtr = GetSequencer();
		FMovieSceneObjectBindingID Binding;

		TOptional<FMovieSceneSpawnableAnnotation> Spawnable = FMovieSceneSpawnableAnnotation::Find(NewReferencedActor);
		if (Spawnable.IsSet())
		{
			// Check whether the spawnable is underneath the current sequence, if so, we can remap it to a local sequence ID
			Binding = UE::MovieScene::FRelativeObjectBindingID(SequencerPtr->GetFocusedTemplateID(), Spawnable->SequenceID, Spawnable->ObjectBindingID, *SequencerPtr);
		}
		else
		{
			FGuid ParentActorId = FindOrCreateHandleToObject(NewReferencedActor).Handle;
			Binding = UE::MovieScene::FRelativeObjectBindingID(ParentActorId);
		}

		if (Binding.IsValid())
		{
			FMovieSceneUMGKey NewKey;
			NewKey.Object = Binding;
			OutGeneratedKeys.Add(FMovieSceneChannelValueSetter::Create<FMovieSceneUMGData>(0, NewKey, true));
		}
	}
}

/*TSharedPtr<SWidget> FUMGTraceEditor::BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params)
{
	UMovieSceneUMGTrack* MPCTrack = Cast<UMovieSceneUMGTrack>(Track);
	const FOnGetContent MenuContent = FOnGetContent::CreateSP(this, &FUMGTraceEditor::OnGetSubMenuContent, MPCTrack, Params.RowIndex, Params.TrackInsertRowIndex);

	return FSequencerUtilities::MakeAddButton(LOCTEXT("AddUMGButton", "Track"), MenuContent, Params.NodeIsHovered, GetSequencer());
}

TSharedRef<ISequencerSection> FUMGTraceEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding)
{
	UMovieSceneUMGSection* MovieSceneUMGSection = Cast<UMovieSceneUMGSection>(&SectionObject);
	checkf(MovieSceneUMGSection != nullptr, TEXT("Unsupported section type."));

	return MakeShareable(new FUMGSection(*MovieSceneUMGSection));
}

bool FUMGTraceEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const
{
	return Type == UMovieSceneUMGTrack::StaticClass();
}

bool FUMGTraceEditor::SupportsSequence(UMovieSceneSequence* InSequence) const
{
	const ETrackSupport TrackSupported = InSequence ? InSequence->IsTrackSupported(UMovieSceneUMGTrack::StaticClass()) : ETrackSupport::NotSupported;
	return TrackSupported != ETrackSupport::NotSupported;
}

TSharedRef<SWidget> CreateAssetPicker(FOnAssetSelected OnAssetSelected, FOnAssetEnterPressed OnAssetEnterPressed, TWeakPtr<ISequencer> InSequencer)
{
	UMovieSceneSequence* Sequence = InSequencer.IsValid() ? InSequencer.Pin()->GetFocusedMovieSceneSequence() : nullptr;

	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	FAssetPickerConfig AssetPickerConfig;
	{
		AssetPickerConfig.SelectionMode = ESelectionMode::Single;
		AssetPickerConfig.OnAssetSelected = OnAssetSelected;
		AssetPickerConfig.OnAssetEnterPressed = OnAssetEnterPressed;
		AssetPickerConfig.bAllowNullSelection = false;
		AssetPickerConfig.bAddFilterUI = true;
		AssetPickerConfig.InitialAssetViewType = EAssetViewType::Tile;
		AssetPickerConfig.Filter.bRecursiveClasses = true;
		AssetPickerConfig.Filter.ClassPaths.Add(UWidgetBlueprint::StaticClass()->GetClassPathName());
		AssetPickerConfig.SaveSettingsName = TEXT("SequencerAssetPicker");
		AssetPickerConfig.AdditionalReferencingAssets.Add(FAssetData(Sequence));
	}

	const FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	return SNew(SBox)
		.WidthOverride(300.0f)
		.HeightOverride(300.f)
		[
			ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
		];
}

void FUMGTraceEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder)
{
	auto SubMenuCallback = [this](FMenuBuilder& SubMenuBuilder)
	{
		SubMenuBuilder.AddWidget(CreateAssetPicker(FOnAssetSelected::CreateRaw(this, &FUMGTraceEditor::AddTrackToSequence), FOnAssetEnterPressed::CreateRaw(this, &FUMGTraceEditor::AddTrackToSequenceEnterPressed), GetSequencer()), FText::GetEmpty(), true);
	};

	MenuBuilder.AddSubMenu(
		LOCTEXT("AddUMGTrack", "UMG Track"),
		LOCTEXT("AddUMGTrackToolTip", "Adds a new track that controls parameters within a UMG."),
		FNewMenuDelegate::CreateLambda(SubMenuCallback),
		false,
		FSlateIconFinder::FindIconForClass(UUserWidget::StaticClass())
	);
}

const FSlateBrush* FUMGTraceEditor::GetIconBrush() const
{
	return FSlateIconFinder::FindIconForClass(UUserWidget::StaticClass()).GetIcon();
}

bool FUMGTraceEditor::HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid)
{
	UWidgetBlueprint* WidgetBlueprint = Cast<UWidgetBlueprint>(Asset);
	if (WidgetBlueprint)
	{
		AddTrackToSequence(FAssetData(WidgetBlueprint));
	}

	return WidgetBlueprint != nullptr;
}

void FUMGTraceEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track)
{
	UMovieSceneUMGTrack* MovieSceneUMGTrack = Cast<UMovieSceneUMGTrack>(Track);

	auto AssignAsset = [MovieSceneUMGTrack](const FAssetData& InAssetData)
	{
		if (UUserWidget* UserWidget = Cast<UUserWidget>(InAssetData.GetAsset()))
		{
			FScopedTransaction Transaction(LOCTEXT("SetAssetTransaction", "Assign UMG"));
			MovieSceneUMGTrack->Modify();
			MovieSceneUMGTrack->SetDisplayName(FText::FromString(UserWidget->GetName()));
			MovieSceneUMGTrack->UserWidget = UserWidget;
		}

		FSlateApplication::Get().DismissAllMenus();
	};

	auto AssignAssetEnterPressed = [AssignAsset](const TArray<FAssetData>& InAssetData)
	{
		if (InAssetData.Num() > 0)
		{
			AssignAsset(InAssetData[0].GetAsset());
		}
	};

	auto SubMenuCallback = [this, AssignAsset, AssignAssetEnterPressed](FMenuBuilder& SubMenuBuilder)
	{
		SubMenuBuilder.AddWidget(CreateAssetPicker(FOnAssetSelected::CreateLambda(AssignAsset), FOnAssetEnterPressed::CreateLambda(AssignAssetEnterPressed), GetSequencer()), FText::GetEmpty(), true);
	};

	UUserWidget* UserWidget = MovieSceneUMGTrack ? MovieSceneUMGTrack->UserWidget : nullptr;

	MenuBuilder.AddMenuEntry(
		FText::Format(LOCTEXT("SelectAssetFormat", "Select {0}"), UserWidget ? FText::FromString(UserWidget->GetName()) : FText::GetEmpty()),
		FText::Format(LOCTEXT("SelectAssetTooltipFormat", "Select {0}"), UserWidget ? FText::FromString(UserWidget->GetName()) : FText::GetEmpty()),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FUMGTraceEditor::OnSelectUserWidget, UserWidget),
			FCanExecuteAction::CreateLambda([UserWidget] { return UserWidget != nullptr; }
			)
		)
	);

	MenuBuilder.AddSubMenu(
		LOCTEXT("SetAsset", "Set Asset"),
		LOCTEXT("SetAsset_ToolTip", "Sets the UMG that this track animates."),
		FNewMenuDelegate::CreateLambda(SubMenuCallback)
	);
}

TSharedRef<SWidget> FUMGTraceEditor::OnGetSubMenuContent(UMovieSceneUMGTrack* UMGTrack, int32 RowIndex, int32 TrackInsertRowIndex)
{
	FMenuBuilder MenuBuilder(true, nullptr);

	const FMovieSceneBlendTypeField SupportedBlendTypes = UMGTrack->GetSupportedBlendTypes();
	if (SupportedBlendTypes.Num() > 1)
	{
		const TWeakPtr<ISequencer> WeakSequencer = GetSequencer();
		FSequencerUtilities::PopulateMenu_CreateNewSection(MenuBuilder, TrackInsertRowIndex, UMGTrack, WeakSequencer);

		MenuBuilder.AddSeparator();
	}

	return MenuBuilder.MakeWidget();
}

void FUMGTraceEditor::OnSelectUserWidget(UUserWidget* UserWidget)
{
	if (!UserWidget)
	{
		return;
	}

	TArray<UObject*> ObjectsToFocus;
	ObjectsToFocus.Add(UserWidget);

	GEditor->SyncBrowserToObjects(ObjectsToFocus);
}

void FUMGTraceEditor::AddTrackToSequence(const FAssetData& InAssetData)
{
	FSlateApplication::Get().DismissAllMenus();

	UWidgetBlueprint* WidgetBlueprint = Cast<UWidgetBlueprint>(InAssetData.GetAsset());
	if (!WidgetBlueprint)
	{
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	TSubclassOf<UUserWidget> UserWidgetClass{WidgetBlueprint->GeneratedClass};
	
	UUserWidget* UserWidget = CreateWidget(World, UserWidgetClass);
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (!UserWidget || !MovieScene)
	{
		return;
	}

	if (MovieScene->IsReadOnly())
	{
		return;
	}
	
	for (UMovieSceneTrack* Track : MovieScene->GetTracks())
	{
		if (auto* UMGTrack = Cast<UMovieSceneUMGTrack>(Track))
		{
			if (UMGTrack->UserWidget == UserWidget)
			{
				return;
			}
		}
	}

	const FScopedTransaction Transaction(LOCTEXT("AddTrackDescription", "Add UMG Track"));

	MovieScene->Modify();
	UMovieSceneUMGTrack* Track = MovieScene->AddTrack<UMovieSceneUMGTrack>();
	check(Track);

	// UMovieSceneSection* NewSection = Track->CreateNewSection();
	// check(NewSection);
	//
	// Track->AddSection(*NewSection);
	// Track->UserWidget = UserWidget;
	// Track->SetDisplayName(FText::FromString(UserWidget->GetName()));

	if (GetSequencer().IsValid())
	{
		GetSequencer()->OnAddTrack(Track, FGuid());
	}
}

void FUMGTraceEditor::AddTrackToSequenceEnterPressed(const TArray<FAssetData>& InAssetData)
{
	if (InAssetData.Num() > 0)
	{
		AddTrackToSequence(InAssetData[0].GetAsset());
	}
}*/

#undef LOCTEXT_NAMESPACE
