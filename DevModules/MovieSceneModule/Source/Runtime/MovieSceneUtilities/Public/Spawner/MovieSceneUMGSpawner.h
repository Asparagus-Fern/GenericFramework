// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMovieSceneObjectSpawner.h"

class UUserWidgetBlueprint;

/**
 * 
 */
class MOVIESCENEUTILITIES_API FMovieSceneUMGSpawner : public IMovieSceneObjectSpawner
{
public:
	static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();

	virtual UClass* GetSupportedTemplateType() const override;
	virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, IMovieScenePlayer& Player) override;
	virtual void DestroySpawnedObject(UObject& Object) override;

private:
	ULevelStreaming* GetLevelStreaming(const FName& DesiredLevelName, const UWorld* World);
};
