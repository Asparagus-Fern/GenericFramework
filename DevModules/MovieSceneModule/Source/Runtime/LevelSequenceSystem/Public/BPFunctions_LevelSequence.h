// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_LevelSequence.generated.h"

class ULevelSequence;
class ULevelSequenceHandle;

/**
 * 
 */
UCLASS()
class LEVELSEQUENCESYSTEM_API UBPFunctions_LevelSequence : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(HandleName = "DefaultLevelSequenceHandle"))
	static ULevelSequenceHandle* RegisterLevelSequenceHandle(FName HandleName, ULevelSequence* InLevelSequence, FMovieSceneSequencePlaybackSettings InSettings = FMovieSceneSequencePlaybackSettings());
};
