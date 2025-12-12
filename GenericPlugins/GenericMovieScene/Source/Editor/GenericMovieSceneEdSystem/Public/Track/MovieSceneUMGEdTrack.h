// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneTrackEditor.h"

class UUserWidgetBlueprint;
class UMovieSceneUMGTrack;

/**
 * 
 */
class FMovieSceneUMGEdTrack : public FMovieSceneTrackEditor
{
public:
	FMovieSceneUMGEdTrack(TSharedRef<ISequencer> InSequencer);
	static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);

	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;
	virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;
	virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;
	virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;

private:
	TSharedRef<SWidget> CreateUMGAssetPicker();
	void OnUMGAssetSelected(const FAssetData& InAssetData);
	void OnUMGAssetEnterPressed(const TArray<FAssetData>& InAssetData);

	bool IsUMGBindingExist(UUserWidgetBlueprint* InUserWidgetBP);
	void AddUMGBinding(UUserWidgetBlueprint* InUserWidgetBP);
};
