// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Android.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMISC_API UBPFunctions_Android : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,Category="Acdroid")
	static FString GetAndroidRootDir();

	UFUNCTION(BlueprintPure,Category="Acdroid")
	static FString GetAndroidProjectDir(bool bUseExternalStorage);

	UFUNCTION(BlueprintPure,Category="Acdroid")
	static FString GetAndroidConfigDir(bool bUseExternalStorage);

	UFUNCTION(BlueprintPure,Category="Acdroid")
	static FString GetAndroidContentDir(bool bUseExternalStorage);

	UFUNCTION(BlueprintPure,Category="Acdroid")
	static FString GetAndroidSavedDir(bool bUseExternalStorage);
};
