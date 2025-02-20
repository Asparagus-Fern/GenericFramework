// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneInterface.h"
#include "Handle/MovieSceneHandleBase.h"

#include "MediaHandle.generated.h"

class UMediaPlaylist;
class UMediaSource;
class UMediaPlayer;

/**
 * 
 */
UCLASS()
class MEDIASYSTEM_API UMediaHandle : public UMovieSceneHandleBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="RegisterMediaHandle")
	static UMediaHandle* Register(FName HandleName = NAME_None);
	
	/* FMovieSceneInterface */
public:


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	UMediaPlayer* MediaPlayer = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	UMediaPlaylist* MediaPlaylist = nullptr;
};
