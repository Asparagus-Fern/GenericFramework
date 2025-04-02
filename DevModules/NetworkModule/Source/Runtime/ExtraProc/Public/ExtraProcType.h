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
struct EXTRAPROC_API FExtraProcHandle
{
	GENERATED_BODY()

public:
	FExtraProcHandle()
	{
	}

	FExtraProcHandle(uint16 InProcID)
		: ProcID(InProcID)
	{
	}

	bool operator==(const FExtraProcHandle& Other) const { return Other.ProcID == ProcID; }
	bool operator!=(const FExtraProcHandle& Other) const { return !operator==(Other); }
	uint16 GetProcId() const { return ProcID; }
	bool IsValid() const { return ProcID != MIN_uint16; }

private:
	uint16 ProcID = MIN_uint16;
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
