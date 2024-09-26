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

	/* File */
public:
	UFUNCTION(BlueprintPure)
	static TArray<FString> FindFiles(const FString& Path, const FString& Extension);

	UFUNCTION(BlueprintPure)
	static TArray<FString> FindFilesRecursive(const FString& Path, const FString& Extension, bool Files, bool Directories, bool bClearFileNames = true);

	UFUNCTION(BlueprintCallable)
	static bool CopyFile(FString FileSource, FString FileDest, bool Replace = true, bool EvenIfReadOnly = false);

	UFUNCTION(BlueprintCallable)
	static bool MoveFile(FString FileSource, FString FileDest, bool Replace = true, bool EvenIfReadOnly = false);

	UFUNCTION(BlueprintCallable)
	static bool DeleteFile(FString FileName, bool RequireExists = false, bool EvenReadOnly = false);

	UFUNCTION(BlueprintPure)
	static bool IsFileReadOoly(const FString& FileName);
};
