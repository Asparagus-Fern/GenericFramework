// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "ISequencerSection.h"

class UMovieSceneUMGSection;

/**
 * 
 */
class FMovieSceneUMGEdSection : public FSequencerSection
{
public:
	FMovieSceneUMGEdSection(UMovieSceneSection& InSectionObject);

	virtual FText GetSectionTitle() const override;
	virtual FText GetSectionToolTip() const override;
	virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;
	virtual int32 OnPaintSection(FSequencerSectionPainter& InPainter) const override;
};

#endif
