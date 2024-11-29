// Fill out your copyright notice in the Description page of Project Settings.


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

float FUMGSection::GetSectionHeight() const
{
	return FSequencerSection::GetSectionHeight();
}

int32 FUMGSection::OnPaintSection(FSequencerSectionPainter& InPainter) const
{
	return FSequencerSection::OnPaintSection(InPainter);
}
