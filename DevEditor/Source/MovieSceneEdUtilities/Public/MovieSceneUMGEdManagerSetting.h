// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerEdSetting.h"
#include "MovieSceneUMGEdManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class MOVIESCENEEDUTILITIES_API UMovieSceneUMGEdManagerSetting : public UManagerEdSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
};
