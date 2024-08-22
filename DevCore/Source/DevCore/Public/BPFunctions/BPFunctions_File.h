// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_File.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_File : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* Folder */
public:
	UFUNCTION(BlueprintPure)
	static bool ExistFolder(const FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool CreateFolder(const FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool DeleteFolder(const FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool DeleteFolderRecursively(const FString& Directory);

public:
};
