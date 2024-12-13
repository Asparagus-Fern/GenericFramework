// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LevelSequenceType.generated.h"

class ULevelSequencePlayer;
class ALevelSequenceActor;

/**
 * 
 */
USTRUCT(BlueprintType)
struct LEVELSEQUENCESYSTEM_API FLevelSequenceHandle
{
	GENERATED_BODY()

public:
	FLevelSequenceHandle();
	FLevelSequenceHandle(FName InHandleID, ALevelSequenceActor* InLevelSequenceActor, ULevelSequencePlayer* InLevelSequencePlayer);

	bool operator==(const FLevelSequenceHandle& Other) const { return HandleID == Other.HandleID; }
	bool operator==(FName Other) const { return HandleID == Other; }
	bool operator==(const ALevelSequenceActor* Other) const { return LevelSequenceActor == Other; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName HandleID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ALevelSequenceActor* LevelSequenceActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelSequencePlayer* LevelSequencePlayer = nullptr;
};
