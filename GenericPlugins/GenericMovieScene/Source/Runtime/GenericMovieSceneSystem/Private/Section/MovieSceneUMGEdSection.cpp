// Copyright ChenTaiye 2025. All Rights Reserved.

#if WITH_EDITOR

#include "Section/MovieSceneUMGEdSection.h"

#include "Section/MovieSceneUMGSection.h"

FMovieSceneUMGEdSection::FMovieSceneUMGEdSection(UMovieSceneSection& InSectionObject)
	: FSequencerSection(InSectionObject)
{
}

FText FMovieSceneUMGEdSection::GetSectionTitle() const
{
	return FSequencerSection::GetSectionTitle();
}

FText FMovieSceneUMGEdSection::GetSectionToolTip() const
{
	return FSequencerSection::GetSectionToolTip();
}

float FMovieSceneUMGEdSection::GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const
{
	return FSequencerSection::GetSectionHeight(ViewDensity);
}

int32 FMovieSceneUMGEdSection::OnPaintSection(FSequencerSectionPainter& InPainter) const
{
	return FSequencerSection::OnPaintSection(InPainter);
}

#endif
