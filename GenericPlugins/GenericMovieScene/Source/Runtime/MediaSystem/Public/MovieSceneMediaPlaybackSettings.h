// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MovieSceneMediaPlaybackSettings.generated.h"

USTRUCT(BlueprintType)
struct FMovieSceneMediaPlaybackSettings
{
	GENERATED_BODY()

public:
	FMovieSceneMediaPlaybackSettings();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoPlay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLoop = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition= "bIsLoop", UIMin = "-1", ClampMin = "-1"))
	int32 LoopNum = -1;
};
