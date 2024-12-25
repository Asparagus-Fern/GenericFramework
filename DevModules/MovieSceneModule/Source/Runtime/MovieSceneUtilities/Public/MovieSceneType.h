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
struct FMovieSceneTime
{
	GENERATED_BODY()

public:
	FMovieSceneTime();
	FMovieSceneTime(int32 InDay, int32 InHour, int32 InMinute, int32 InSecond, int32 InMicroSecond);
	FMovieSceneTime(FTimespan InTimeSpan);

	// bool operator>(const FMovieSceneTime& Other) const;
	// bool operator<(const FMovieSceneTime& Other) const;
	// bool operator==(const FMovieSceneTime& Other) const;
	// bool operator!=(const FMovieSceneTime& Other) const;
	// bool operator>=(const FMovieSceneTime& Other) const;
	// bool operator<=(const FMovieSceneTime& Other) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Day = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hour = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Minute = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Second = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MicroSecond = 0;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "bLoopFragment"))
	int32 PlayNumToDelayLoop = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bLoopFragment"))
	FVector2D LoopRange;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "bLoopFragment"))
	// FMovieSceneTime LoopTimeStart;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "bLoopFragment"))
	// FMovieSceneTime LoopTimeEnd;
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
