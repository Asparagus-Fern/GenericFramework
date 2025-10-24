// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Audio.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMISC_API UBPFunctions_Audio : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AzSpeech | Audio", Meta = (DisplayName = "Convert .wav file to USoundWave"))
	static USoundWave* ConvertWavFileToSoundWave(const FString& FileName, const FString& OutputAssetName, const FString& PackagePath = "");

	UFUNCTION(BlueprintCallable)
	static USoundWave* ConvertAudioDataToSoundWave(const TArray<uint8>& RawData, const FString& OutputAssetName, const FString& PackagePath = "");
};
