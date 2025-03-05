// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sections/MovieSceneHookSection.h"
#include "MovieSceneUMGSection.generated.h"

class UUserWidgetBlueprint;

/**
 * 
 */
UCLASS(MinimalAPI)
class UMovieSceneUMGSection : public UMovieSceneSection
{
	GENERATED_BODY()

public:
	UMovieSceneUMGSection(const FObjectInitializer& ObjInit);
};
