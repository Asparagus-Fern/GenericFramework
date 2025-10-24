#include "UEFastNoise2.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FUEFastNoise2Module"

void FUEFastNoise2Module::StartupModule()
{
	const FString BaseDir = IPluginManager::Get().FindPlugin("UnrealFastNoise2")->GetBaseDir();
	const FString LibraryPath = FPaths::Combine(*BaseDir, TEXT(FASTNOISE_LIBRARY_PATH));

	FastNoiseHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (FastNoiseHandle == nullptr)
	{
		const FText ErrorFormat = NSLOCTEXT("UnrealFastNoise2Module", "ThirdPartyLibraryError", "Failed to load FastNoise library at path [{0}]");
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(ErrorFormat, FText::FromString(LibraryPath)));
	}
}

void FUEFastNoise2Module::ShutdownModule()
{
	FPlatformProcess::FreeDllHandle(FastNoiseHandle);
	FastNoiseHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUEFastNoise2Module, UEFastNoise2)
