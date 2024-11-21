// Fill out your copyright notice in the Description page of Project Settings.


#include "UMGSection.h"

#define LOCTEXT_NAMESPACE "UMGSection"

FUMGSection::FUMGSection(UMovieSceneSection& InSectionObject)
	: FSequencerSection(InSectionObject)
{
}

#undef LOCTEXT_NAMESPACE