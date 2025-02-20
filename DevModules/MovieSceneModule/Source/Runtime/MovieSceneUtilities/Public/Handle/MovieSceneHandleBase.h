// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneInterface.h"
#include "Handle/HandleBase.h"

#include "MovieSceneHandleBase.generated.h"

class UUserWidgetBase;
/**
 * 
 */
UCLASS(Abstract)
class MOVIESCENEUTILITIES_API UMovieSceneHandleBase : public UHandleBase, public IMovieSceneInterface
{
	GENERATED_BODY()

	/* UHandleBase */
protected:
	virtual void OnRegister() override;
	virtual void OnUnRegister() override;
};
