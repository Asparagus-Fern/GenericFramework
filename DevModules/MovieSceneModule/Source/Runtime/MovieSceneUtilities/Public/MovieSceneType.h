// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneType.generated.h"

class UMovieScenePanel;

/**
 * 
 */
UENUM(BlueprintType)
enum class EMovieSceneState : uint8
{
	None,
	Play,
	Pause,
	Stop,
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMovieSceneLoopSetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableLoop = false;

	/* 片段循环 */
	UPROPERTY(EditAnywhere)
	bool bLoopFragment = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLoopFragment"))
	int32 PlayNumToDelayLoop = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLoopFragment"))
	FVector2D LoopRange;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct MOVIESCENEUTILITIES_API FMovieSceneSetting
{
	GENERATED_BODY()

public:
	FMovieSceneSetting();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMovieSceneState MovieSceneState = EMovieSceneState::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "MovieSceneState == EMovieSceneState::Play"))
	TSubclassOf<UMovieScenePanel> MovieScenePanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "MovieSceneState == EMovieSceneState::Play"))
	FMovieSceneLoopSetting MovieSceneLoopSetting;
};
