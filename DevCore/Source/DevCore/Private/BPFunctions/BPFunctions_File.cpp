// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_File.h"

bool UBPFunctions_File::ExistFolder(const FString& Directory)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.DirectoryExists(*Directory);
}

bool UBPFunctions_File::CreateFolder(const FString& Directory)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.CreateDirectoryTree(*Directory);
}

bool UBPFunctions_File::DeleteFolder(const FString& Directory)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.DeleteDirectory(*Directory);
}

bool UBPFunctions_File::DeleteFolderRecursively(const FString& Directory)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.DeleteDirectoryRecursively(*Directory);
}

TArray<FString> UBPFunctions_File::FindFiles(const FString& Path, const FString& Extension)
{
	TArray<FString> Result;
	IFileManager::Get().FindFiles(Result, *Path, *Extension);
	return Result;
}

TArray<FString> UBPFunctions_File::FindFilesRecursive(const FString& Path, const FString& Extension, const bool Files, const bool Directories, const bool bClearFileNames)
{
	TArray<FString> Result;
	IFileManager& FileManager = IFileManager::Get();
	if (FileManager.DirectoryExists(*Path))
	{
		FileManager.FindFilesRecursive(Result, *Path, *Extension, Files, Directories, bClearFileNames);
	}
	return Result;
}

bool UBPFunctions_File::CopyFile(const FString FileSource, const FString FileDest, const bool Replace, const bool EvenIfReadOnly)
{
	IFileManager& FileManager = IFileManager::Get();
	return FileManager.Copy(*FileDest, *FileSource, Replace, EvenIfReadOnly) == COPY_OK;
}

bool UBPFunctions_File::MoveFile(const FString FileSource, const FString FileDest, const bool Replace, const bool EvenIfReadOnly)
{
	IFileManager& FileManager = IFileManager::Get();
	return FileManager.Move(*FileDest, *FileSource, Replace, EvenIfReadOnly);
}

bool UBPFunctions_File::DeleteFile(const FString FileName, const bool RequireExists, const bool EvenReadOnly)
{
	IFileManager& FileManager = IFileManager::Get();
	return FileManager.Delete(*FileName, RequireExists, EvenReadOnly);
}

bool UBPFunctions_File::IsFileReadOoly(const FString& FileName)
{
	IFileManager& FileManager = IFileManager::Get();
	return FileManager.IsReadOnly(*FileName);
}
