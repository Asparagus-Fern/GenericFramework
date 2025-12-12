// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IMovieSceneObjectSpawner.h"

class UUserWidgetBlueprint;

/**
 * 
 */
class GENERICMOVIESCENESYSTEM_API FMovieSceneUMGSpawner : public IMovieSceneObjectSpawner
{
public:
	static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();

	virtual UClass* GetSupportedTemplateType() const override;
	virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;
	virtual void DestroySpawnedObject(UObject& Object) override;

private:
	ULevelStreaming* GetLevelStreaming(const FName& DesiredLevelName, const UWorld* World);
};
