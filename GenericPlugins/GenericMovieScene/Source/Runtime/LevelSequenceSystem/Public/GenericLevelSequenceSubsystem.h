// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "GenericLevelSequenceSubsystem.generated.h"

class ULevelSequence;
class UGenericLevelSequenceHandle;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericLevelSequenceSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static LEVELSEQUENCESYSTEM_API UGenericLevelSequenceSubsystem* Get(const UObject* WorldContextObject);

public:
	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API UGenericLevelSequenceHandle* RegisterLevelSequenceHandle(ULevelSequence* InLevelSequence, const FMovieSceneSequencePlaybackSettings& InSettings);

	UFUNCTION(BlueprintCallable)
	LEVELSEQUENCESYSTEM_API void UnRegisterLevelSequenceHandle(UGenericLevelSequenceHandle* InHandle);
	
private:
	TArray<TObjectPtr<UGenericLevelSequenceHandle>> LevelSequenceHandles;
};
