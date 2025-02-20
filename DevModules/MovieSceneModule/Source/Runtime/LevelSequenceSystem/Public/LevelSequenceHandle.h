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

public:
	UFUNCTION(BlueprintCallable, DisplayName="RegisterLevelSequenceHandle")
	static ULevelSequenceHandle* Register(FName HandleName = NAME_None);

	/* FMovieSceneInterface */
public:
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	ALevelSequenceActor* LevelSequenceActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	ULevelSequencePlayer* LevelSequencePlayer = nullptr;
};
