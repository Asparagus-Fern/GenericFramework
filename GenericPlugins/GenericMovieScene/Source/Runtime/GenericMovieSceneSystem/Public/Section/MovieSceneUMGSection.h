// Copyright ChenTaiye 2025. All Rights Reserved.

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
