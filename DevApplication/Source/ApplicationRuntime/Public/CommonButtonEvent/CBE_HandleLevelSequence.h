// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "MovieSceneType.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleLevelSequence.generated.h"

class ULevelSequence;

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandleLevelSequence : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere)
	EMovieSceneState MovieSceneState = EMovieSceneState::Play;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ULevelSequence> Sequence = nullptr;

	UPROPERTY()
	bool bNewSequencePlaybackSettings = false;

	UPROPERTY(EditAnywhere, meta=(EditCondition = "bNewSequencePlaybackSettings"))
	FMovieSceneSequencePlaybackSettings Settings;

private:
	void OnPlayFinish();
};
