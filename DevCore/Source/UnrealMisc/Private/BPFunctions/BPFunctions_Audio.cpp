// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "BPFunctions/BPFunctions_Audio.h"

#include "AudioDeviceManager.h"
#include "AudioThread.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "BPFunctions/BPFunctions_Device.h"
#include "Components/AudioComponent.h"
#include "EditorFramework/AssetImportData.h"
#include "Type/AudioType.h"
#include "Type/DebugType.h"
#include "UObject/SavePackage.h"

USoundWave* UBPFunctions_Audio::ConvertWavFileToSoundWave(const FString& FileName, const FString& OutputAssetName, const FString& PackagePath)
{
#if PLATFORM_ANDROID
	if (!UBPFunctions_Device::CheckAndroidPermission("android.permission.WRITE_EXTERNAL_STORAGE"))
	{
		GenericLOG(GenericLogAudio, Error, TEXT("No Permission for : android.permission.WRITE_EXTERNAL_STORAGE"));
		return nullptr;
	}
#endif

	if (IFileManager::Get().FileExists(*FileName))
	{
		if (TArray<uint8> RawData; FFileHelper::LoadFileToArray(RawData, *FileName))
		{
			if (USoundWave* const SoundWave = ConvertAudioDataToSoundWave(RawData, OutputAssetName, PackagePath))
			{
#if WITH_EDITORONLY_DATA
				SoundWave->AssetImportData->Update(FileName);
#endif
				return SoundWave;
			}
		}
	}

	return nullptr;
}

USoundWave* UBPFunctions_Audio::ConvertAudioDataToSoundWave(const TArray<uint8>& RawData, const FString& OutputAssetName, const FString& PackagePath)
{
#if PLATFORM_ANDROID
	if (!UBPFunctions_Device::CheckAndroidPermission("android.permission.WRITE_EXTERNAL_STORAGE"))
	{
		GenericLOG(GenericLogAudio, Error, TEXT("No Permission for : android.permission.WRITE_EXTERNAL_STORAGE"));
		return nullptr;
	}
#endif

	if (RawData.IsEmpty())
	{
		GenericLOG(GenericLogAudio, Error, TEXT("RawData is empty"));
		return nullptr;
	}

	USoundWave* SoundWave = nullptr;
	TArray<UAudioComponent*> AudioComponentsToRestart;

	FWaveModInfo WaveInfo;
	WaveInfo.ReadWaveInfo(RawData.GetData(), RawData.Num());

	const int32 ChannelCount = *WaveInfo.pChannels;
	const int32 SizeOfSample = (*WaveInfo.pBitsPerSample) / 8;
	const int32 NumSamples = WaveInfo.SampleDataSize / SizeOfSample;
	const int32 NumFrames = NumSamples / ChannelCount;

	bool bCreatedNewPackage = false;

	if (PackagePath.IsEmpty())
	{
		//Create a new object from the transient package
		SoundWave = NewObject<USoundWave>(GetTransientPackage(), *OutputAssetName);
	}
	else
	{
		FString TargetFilename = FPaths::Combine(PackagePath, OutputAssetName);
		FPaths::NormalizeFilename(TargetFilename);

		UPackage* const Package = CreatePackage(*TargetFilename);

		if (USoundWave* const ExistingSoundWave = FindObject<USoundWave>(Package, *OutputAssetName))
		{
			if (FAudioDeviceManager* const AudioDeviceManager = GEngine->GetAudioDeviceManager())
			{
				AudioDeviceManager->StopSoundsUsingResource(ExistingSoundWave, &AudioComponentsToRestart);
			}

			FAudioThread::RunCommandOnAudioThread([ExistingSoundWave]() { ExistingSoundWave->FreeResources(); });
			SoundWave = ExistingSoundWave;
		}
		else
		{
			SoundWave = NewObject<USoundWave>(Package, *OutputAssetName, RF_Public | RF_Standalone);
		}

		bCreatedNewPackage = true;
	}

	if (SoundWave)
	{
#if WITH_EDITORONLY_DATA
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1)
		SoundWave->RawData.UpdatePayload(FSharedBuffer::Clone(RawData.GetData(), RawData.Num()));
#else
        SoundWave->RawData.Lock(LOCK_READ_WRITE);
        void* LockedData = SoundWave->RawData.Realloc(RawData.Num());
        FMemory::Memcpy(LockedData, RawData.GetData(), RawData.Num());
        SoundWave->RawData.Unlock();
#endif
#endif

		SoundWave->RawPCMDataSize = WaveInfo.SampleDataSize;
		SoundWave->RawPCMData = static_cast<uint8*>(FMemory::Malloc(WaveInfo.SampleDataSize));
		FMemory::Memcpy(SoundWave->RawPCMData, WaveInfo.SampleDataStart, WaveInfo.SampleDataSize);

		SoundWave->Duration = static_cast<float>(NumFrames) / *WaveInfo.pSamplesPerSec;
		SoundWave->SetSampleRate(*WaveInfo.pSamplesPerSec);
		SoundWave->NumChannels = ChannelCount;
		SoundWave->TotalSamples = *WaveInfo.pSamplesPerSec * SoundWave->Duration;

#if ENGINE_MAJOR_VERSION >= 5
		SoundWave->SetImportedSampleRate(*WaveInfo.pSamplesPerSec);

#if ENGINE_MINOR_VERSION <= 3
		SoundWave->CuePoints.Reset(WaveInfo.WaveCues.Num());
		for (FWaveCue& WaveCue : WaveInfo.WaveCues)
		{
			FSoundWaveCuePoint NewCuePoint;
			NewCuePoint.CuePointID = static_cast<int32>(WaveCue.CuePointID);
			NewCuePoint.FrameLength = static_cast<int32>(WaveCue.SampleLength);
			NewCuePoint.FramePosition = static_cast<int32>(WaveCue.Position);
			NewCuePoint.Label = WaveCue.Label;

			SoundWave->CuePoints.Add(NewCuePoint);
		}
#endif
#endif

#if WITH_EDITORONLY_DATA && (ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1))
		if (WaveInfo.TimecodeInfo.IsValid())
		{
			SoundWave->SetTimecodeInfo(*WaveInfo.TimecodeInfo);
		}
#endif

		if (bCreatedNewPackage)
		{
#if WITH_EDITORONLY_DATA && ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1)
			if (const UAudioSettings* const AudioSettings = GetDefault<UAudioSettings>())
			{
				FAudioThread::RunCommandOnAudioThread([AudioSettings, SoundWave]()
					{
						SoundWave->SetSoundAssetCompressionType(Audio::ToSoundAssetCompressionType(AudioSettings->DefaultAudioCompressionType));
					}
				);
			}
			else
			{
				FAudioThread::RunCommandOnAudioThread([SoundWave]()
					{
						SoundWave->SetSoundAssetCompressionType(ESoundAssetCompressionType::BinkAudio);
					}
				);
			}

#elif ENGINE_MAJOR_VERSION == 5
            FAudioThread::RunCommandOnAudioThread([SoundWave]() { SoundWave->SetSoundAssetCompressionType(ESoundAssetCompressionType::BinkAudio); });
#endif

			SoundWave->MarkPackageDirty();
			FAssetRegistryModule::AssetCreated(SoundWave);

			const FString TempPackageName = SoundWave->GetPackage()->GetName();
			const FString TempPackageFilename = FPackageName::LongPackageNameToFilename(TempPackageName, FPackageName::GetAssetPackageExtension());

#if ENGINE_MAJOR_VERSION >= 5
			FSavePackageArgs SaveArgs;
			SaveArgs.SaveFlags = RF_Public | RF_Standalone;
			UPackage::SavePackage(SoundWave->GetPackage(), SoundWave, *TempPackageFilename, SaveArgs);
#else
            UPackage::SavePackage(SoundWave->GetPackage(), SoundWave, RF_Public | RF_Standalone, *TempPackageFilename);
#endif

#if WITH_EDITOR
			TArray<FAssetData> SyncAssets;
			SyncAssets.Add(FAssetData(SoundWave));
			GEditor->SyncBrowserToObjects(SyncAssets);
#endif
		}

		for (UAudioComponent* const& AudioComponent : AudioComponentsToRestart)
		{
			AudioComponent->Play();
		}

		return SoundWave;
	}

	GenericLOG(GenericLogAudio, Error, TEXT("Cannot create a new Sound Wave"));
	return nullptr;
}
