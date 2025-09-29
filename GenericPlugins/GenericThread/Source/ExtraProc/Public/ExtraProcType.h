// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtraProcType.generated.h"

EXTRAPROC_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogExtraProc, Log, All);

/**
 * 
 */
USTRUCT(BlueprintType)
struct EXTRAPROC_API FProcStartUpInfo
{
	GENERATED_BODY()

public:
	FProcStartUpInfo()
		: bRunInBackground(false),
		  bCreatePipe(false)
	{
	}

	FProcStartUpInfo(const FString& InFilePath, const TMap<FString, FString>& InParams, bool bIsRunInBackground, bool bIsCreatePipe)
		: StartParams(InParams),
		  bRunInBackground(bIsRunInBackground),
		  bCreatePipe(bIsCreatePipe)
	{
		ProcFile.FilePath = InFilePath;
	}

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(RelativeToGameDir, FilePathFilter= "Proc Files (*.exe, *.bat)|*.exe;*.bat;"), Category = "ExtraProc")
	FFilePath ProcFile;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "ExtraProc")
	TMap<FString, FString> StartParams;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "ExtraProc")
	bool bRunInBackground;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "ExtraProc")
	bool bCreatePipe;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct EXTRAPROC_API FProcAutoStartUpInfo
{
	GENERATED_BODY()

	FProcAutoStartUpInfo()
		: bAutoLaunch(false)
	{
	}

public:
	UPROPERTY(Config, EditAnywhere, Category = "ExtraProc")
	bool bAutoLaunch;

	UPROPERTY(Config, EditAnywhere, Category = "ExtraProc")
	FProcStartUpInfo ExtraStartProcInfo;
};
