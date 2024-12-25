// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneInterface.h"
#include "Handle/MovieSceneHandleBase.h"
#include "LevelSequenceHandle.generated.h"

class ULevelSequencePlayer;
class ALevelSequenceActor;

/**
 * 
 */
UCLASS()
class LEVELSEQUENCESYSTEM_API ULevelSequenceHandle : public UMovieSceneHandleBase
{
	GENERATED_BODY()

	/* UHandleBase */
public:
	virtual void ClearHandle_Implementation() override;

	/* FMovieSceneInterface */
public:
	virtual void OpenMovieScene_Implementation() override;

	virtual void Play_Implementation() override;
	virtual void Pause_Implementation() override;
	virtual void Stop_Implementation() override;
	virtual void Seek_Implementation(int32 InDays, int32 InHours, int32 InMinutes, int32 InSeconds, int32 InMicroSeconds) override;

public:
	virtual FTimespan GetMovieSceneCurrentTime_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	ALevelSequenceActor* LevelSequenceActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	ULevelSequencePlayer* LevelSequencePlayer = nullptr;
};
