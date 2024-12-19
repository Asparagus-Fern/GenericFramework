// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "MediaManager.generated.h"

class UMediaPlayer;
class UMediaPlaylist;
class UMediaSource;
class UMediaHandle;

/**
 * 
 */
UCLASS()
class MEDIASYSTEM_API UMediaManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
public:
	virtual UMediaHandle* RegisterMedia(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource);
	virtual UMediaHandle* RegisterMedia(UMediaPlayer* InMediaPlayer, TArray<UMediaSource*> InMediaSources);
	virtual UMediaHandle* RegisterMedia(UMediaPlayer* InMediaPlayer, UMediaPlaylist* InMediaPlayList);
	virtual void UnRegisterMedia(UMediaPlayer* InMediaPlayer);
	virtual void UnRegisterMedia(UMediaHandle* InMediaHandle);

	bool IsMediaRegister(const UMediaPlayer* InMediaPlayer);
	UMediaHandle* GetMediaHandle(const UMediaPlayer* InMediaPlayer);

protected:
	UPROPERTY()
	TArray<UMediaHandle*> MediaHandles;
};
