// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Section/UMGSection.h"

#include "Section/MovieSceneUMGSection.h"

FUMGSection::FUMGSection(UMovieSceneSection& InSectionObject)
	: FSequencerSection(InSectionObject)
{
}

FText FUMGSection::GetSectionTitle() const
{
	return FSequencerSection::GetSectionTitle();
}

FText FUMGSection::GetSectionToolTip() const
{
	return FSequencerSection::GetSectionToolTip();
}

float FUMGSection::GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const
{
	return FSequencerSection::GetSectionHeight(ViewDensity);
}

int32 FUMGSection::OnPaintSection(FSequencerSectionPainter& InPainter) const
{
	return FSequencerSection::OnPaintSection(InPainter);
}
