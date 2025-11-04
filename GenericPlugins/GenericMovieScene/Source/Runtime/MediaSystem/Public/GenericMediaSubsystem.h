// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "GenericMediaSubsystem.generated.h"

class UMediaSource;
class UMediaPlayer;
class UGenericMediaHandle;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericMediaSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static MEDIASYSTEM_API UGenericMediaSubsystem* Get(const UObject* WorldContextObject);

public:
	UFUNCTION(BlueprintCallable)
	MEDIASYSTEM_API UGenericMediaHandle* RegisterMediaHandle(UMediaPlayer* InMediaPlayer, UMediaSource* InMediaSource, const FMediaPlayerOptions& InOptions);

	UFUNCTION(BlueprintCallable)
	MEDIASYSTEM_API void UnRegisterMediaHandle(UGenericMediaHandle* InHandle);
	
private:
	TArray<TObjectPtr<UGenericMediaHandle>> MediaHandles;
};
