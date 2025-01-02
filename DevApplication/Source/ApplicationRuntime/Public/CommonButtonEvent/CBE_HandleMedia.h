// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneType.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleMedia.generated.h"

class UMovieScenePanel;
class UMediaSource;
class UMediaPlayer;

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UCBE_HandleMedia : public UCommonButtonEvent
{
	GENERATED_UCLASS_BODY()
	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMediaPlayer> MediaPlayer = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UMediaSource>> MediaSources;

	UPROPERTY(EditAnywhere)
	FMovieSceneSetting MovieSceneSetting;
};
