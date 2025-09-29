// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

THIRD_PARTY_INCLUDES_START
#include <speechapi_cxx_keyword_recognition_model.h>
#include <speechapi_cxx_speech_recognizer.h>
#include <speechapi_cxx_speech_config.h>
#include <speechapi_cxx_hybrid_speech_config.h>
THIRD_PARTY_INCLUDES_END

#include "AzSpeechWakeupSubsystem.generated.h"

namespace MicrosoftSpeech = Microsoft::CognitiveServices::Speech;
using MicrosoftKeywordModelPtr = std::shared_ptr<MicrosoftSpeech::KeywordRecognitionModel>;
using MicrosoftSpeechConfigPtr = std::shared_ptr<MicrosoftSpeech::SpeechConfig>;
using MicrosoftSpeechRecognizerPtr = std::shared_ptr<MicrosoftSpeech::SpeechRecognizer>;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWakeupDelegate);

/**
 * 
 */
UCLASS()
class UEAZSPEECH_API UAzSpeechWakeupSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** 语音唤醒开始委托 */
	UPROPERTY(BlueprintAssignable, Category = "AzSpeech|AzSpeechWakeupSubsystem")
	FWakeupDelegate StartDelegate;

	/** 语音唤醒触发委托 */
	UPROPERTY(BlueprintAssignable, Category = "AzSpeech|AzSpeechWakeupSubsystem")
	FWakeupDelegate TriggerDelegate;

	/** 语音唤醒完成委托 */
	UPROPERTY(BlueprintAssignable, Category = "AzSpeech|AzSpeechWakeupSubsystem")
	FWakeupDelegate CompletedDelegate;

	/** 语音唤醒出错委托 */
	UPROPERTY(BlueprintAssignable, Category = "AzSpeech|AzSpeechWakeupSubsystem")
	FWakeupDelegate FailedDelegate;

	UAzSpeechWakeupSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** 开启异步语音唤醒任务 */
	UFUNCTION(BlueprintCallable, Category = "AzSpeech|AzSpeechWakeupSubsystem")
	void StartWakeupAsync();

	/** 停止异步语音唤醒任务 */
	UFUNCTION(BlueprintCallable, Category = "AzSpeech|AzSpeechWakeupSubsystem")
	void StopWakeupAsync();

private:
	MicrosoftKeywordModelPtr ModelPtr;
	MicrosoftSpeechConfigPtr ConfigPtr;
	MicrosoftSpeechRecognizerPtr SpeechRecognizerPtr;
	bool bIsRunning = false;
};
