// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtraProcType.generated.h"

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
		: ProcFile(InFilePath),
		  StartParams(InParams),
		  bRunInBackground(bIsRunInBackground),
		  bCreatePipe(bIsCreatePipe)
	{
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
