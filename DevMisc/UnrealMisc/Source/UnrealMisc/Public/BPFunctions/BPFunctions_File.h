// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_File.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMISC_API UBPFunctions_File : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* Directory */
public:
	UFUNCTION(BlueprintPure, Category="Directory")
	static bool ExistDirectory(const FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool CreateDirectory(const FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool DeleteDirectory(const FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool DeleteDirectoryRecursively(const FString& Directory);

	/**
	 * 
	 * @param DirectoryPath 文件夹绝对路径
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Directory")
	static bool OpenDirectoryDialog(FString& DirectoryPath);

public:
	UFUNCTION(BlueprintPure, Category="Directory")
	static bool GetPluginBaseDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool GetPluginBinariesDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool GetPluginContentDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool GetPluginIntermediateDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool GetPluginResourcesDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool GetPluginSourceDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure, Category="Directory")
	static bool GetPluginExtraDir(const FString& InPluginName, FString& Directory);
	
	/* File */
public:
	UFUNCTION(BlueprintPure, Category="File")
	static TArray<FString> FindFiles(const FString& Path, const FString& Extension);

	UFUNCTION(BlueprintPure, Category="File")
	static TArray<FString> FindFilesRecursive(const FString& Path, const FString& Extension, bool Files, bool Directories, bool bClearFileNames = true);

	UFUNCTION(BlueprintCallable, Category="File")
	static bool CopyFile(FString FileSource, FString FileDest, bool Replace = true, bool EvenIfReadOnly = false);

	UFUNCTION(BlueprintCallable, Category="File")
	static bool MoveFile(FString FileSource, FString FileDest, bool Replace = true, bool EvenIfReadOnly = false);

	UFUNCTION(BlueprintCallable, Category="File")
	static bool DeleteFile(FString FileName, bool RequireExists = false, bool EvenReadOnly = false);

	UFUNCTION(BlueprintPure, Category="File")
	static bool IsFileReadOoly(const FString& FileName);

	/**
	 * 
	 * @param FileType 筛选文件格式
	 * @param FilePaths 文件绝对路径
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="File")
	static bool OpenFileDialog(FString FileType, TArray<FString>& FilePaths);

	/**
	 * 
	 * @param FileName 文件名
	 * @param FileType 文件后缀
	 * @param FilePaths 文件保存绝对路径
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="File")
	static bool SaveFileDialog(FString FileName, FString FileType, TArray<FString>& FilePaths);
};
