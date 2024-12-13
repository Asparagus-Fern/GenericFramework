// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_PlayLevelSequence.generated.h"

class UMovieSceneController;
class ULevelSequence;

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_PlayLevelSequence : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere)
	FName SequenceID = NAME_None;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UMovieSceneController> LevelSequenceController;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ULevelSequence> Sequence = nullptr;

	UPROPERTY()
	bool bNewSequencePlaybackSettings = true;

	UPROPERTY(EditAnywhere, meta=(EditCondition = "bNewSequencePlaybackSettings"))
	FMovieSceneSequencePlaybackSettings Settings;

private:
	UFUNCTION()
	void OnLevelSequenceFinish();
};
