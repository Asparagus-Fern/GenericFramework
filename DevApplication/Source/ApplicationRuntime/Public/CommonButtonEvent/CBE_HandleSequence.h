// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleSequence.generated.h"

class ULevelSequence;

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandleSequence : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere)
	bool bNewSequence = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "bNewSequence"))
	TObjectPtr<ULevelSequence> Sequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "bNewSequence"))
	FMovieSceneSequencePlaybackSettings Settings;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// FWidgetContainer SequenceController;

protected:
};
