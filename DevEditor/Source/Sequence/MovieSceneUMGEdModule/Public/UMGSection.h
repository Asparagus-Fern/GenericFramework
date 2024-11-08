// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISequencerSection.h"

class UMovieSceneUMGSection;

/**
 * 
 */
class FUMGSection : public FSequencerSection
{
public:
	FUMGSection(UMovieSceneSection& InSectionObject);
};
