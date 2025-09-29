// Fill out your copyright notice in the Description page of Project Settings.


#include "AzSpeechWakeupSubsystem.h"

#include "LogUEAzSpeech.h"
#include "Async/Async.h"
#include "AzSpeech/AzSpeechHelper.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"

UAzSpeechWakeupSubsystem::UAzSpeechWakeupSubsystem()
{
}

void UAzSpeechWakeupSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAzSpeechWakeupSubsystem::Deinitialize()
{
	StopWakeupAsync();

	Super::Deinitialize();
}

void UAzSpeechWakeupSubsystem::StartWakeupAsync()
{
	if (bIsRunning)
	{
		UE_LOG(LogUEAzSpeech_Debugging, Warning, TEXT("Wakeup is running!"));
		FailedDelegate.Broadcast();
		return;
	}

	bIsRunning = true;

	// 加载配置
	this->ConfigPtr.reset();
	this->ConfigPtr = MicrosoftSpeech::SpeechConfig::FromSubscription("81099046cd34497385c7e2ca56612ed0", "southeastasia");

	// 加载自定义关键词模型
	FString AbsoluteModelPath;

#if PLATFORM_WINDOWS
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("UEAzSpeech")))
	{
		AbsoluteModelPath = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources/final_lowfa.table"));
	}
#elif PLATFORM_ANDROID
	AbsoluteModelPath = TEXT("/sdcard/Resources/final_lowfa.table");
#endif

	if (!FPaths::FileExists(AbsoluteModelPath))
	{
		ensureAlwaysMsgf(false, TEXT("Load model file failed"));
		return;
	}

	this->ModelPtr.reset();
	this->ModelPtr = MicrosoftSpeech::KeywordRecognitionModel::FromFile(TCHAR_TO_UTF8(*AbsoluteModelPath));
	ensureAlwaysMsgf(ModelPtr, TEXT("Load model file failed"));

	this->SpeechRecognizerPtr.reset();
	this->SpeechRecognizerPtr = MicrosoftSpeech::SpeechRecognizer::FromConfig(ConfigPtr);
	ensureAlwaysMsgf(SpeechRecognizerPtr, TEXT("SpeechRecognizer init failed!"));

	if (!this->SpeechRecognizerPtr)
	{
		UE_LOG(LogUEAzSpeech_Debugging, Error, TEXT("SpeechRecognizer init failed!"));
		FailedDelegate.Broadcast();
		return;
	}

	// start
	StartDelegate.Broadcast();

	SpeechRecognizerPtr->Recognized.Connect([this](const MicrosoftSpeech::SpeechRecognitionEventArgs& e)
		{
			if (e.Result->Reason == MicrosoftSpeech::ResultReason::RecognizedKeyword)
			{
				FString RecognizedText = UTF8_TO_TCHAR(e.Result->Text.c_str());
				UE_LOG(LogUEAzSpeech_Debugging, Log, TEXT("Recognized text : %s"), *RecognizedText);
				AsyncTask(ENamedThreads::GameThread, [this]()
				          {
					          this->TriggerDelegate.Broadcast();
				          }
				);

				StopWakeupAsync();
			}
		}
	);
	SpeechRecognizerPtr->Canceled.Connect([this](const MicrosoftSpeech::SpeechRecognitionCanceledEventArgs& e)
		{
			UE_LOG(LogUEAzSpeech_Debugging, Log, TEXT("CANCELED: Reason=%d"), (int)e.Reason);

			if (e.Reason == MicrosoftSpeech::CancellationReason::Error)
			{
				FString ErrorDetails = UTF8_TO_TCHAR(e.ErrorDetails.c_str());
				UE_LOG(LogUEAzSpeech_Debugging, Log, TEXT("\nCANCELED: ErrorCode=%d\nCANCELED: ErrorDetails=%s\nCANCELED: Did you update the subscription info?"), (int)e.ErrorCode, *ErrorDetails);
				AsyncTask(ENamedThreads::GameThread, [this]()
				          {
					          bIsRunning = false;
					          FailedDelegate.Broadcast();
				          }
				);
			}
		}
	);

	SpeechRecognizerPtr->SessionStarted.Connect([this](const MicrosoftSpeech::SessionEventArgs& e)
		{
			UE_LOG(LogUEAzSpeech_Debugging, Log, TEXT("Session Started"));
			AsyncTask(ENamedThreads::GameThread, [this]()
			          {
				          StartDelegate.Broadcast();
			          }
			);
		}
	);

	SpeechRecognizerPtr->SessionStopped.Connect([this](const MicrosoftSpeech::SessionEventArgs& e)
		{
			UE_LOG(LogUEAzSpeech_Debugging, Log, TEXT("Session stopped"));
			AsyncTask(ENamedThreads::GameThread, [this]()
			          {
				          bIsRunning = false;
				          CompletedDelegate.Broadcast();
			          }
			);
		}
	);

	SpeechRecognizerPtr->StartKeywordRecognitionAsync(this->ModelPtr).get();

	UE_LOG(LogUEAzSpeech_Debugging, Log, TEXT("Start wakeup"));
}

void UAzSpeechWakeupSubsystem::StopWakeupAsync()
{
	if (SpeechRecognizerPtr)
	{
		SpeechRecognizerPtr->StopKeywordRecognitionAsync().get();
	}

	SpeechRecognizerPtr.reset();
	ModelPtr.reset();
	ConfigPtr.reset();

	if (bIsRunning)
	{
		AsyncTask(ENamedThreads::GameThread, [this]()
		          {
			          this->CompletedDelegate.Broadcast();
		          }
		);
	}

	bIsRunning = false;
	UE_LOG(LogUEAzSpeech_Debugging, Log, TEXT("Keyword recognition stop"));
}
