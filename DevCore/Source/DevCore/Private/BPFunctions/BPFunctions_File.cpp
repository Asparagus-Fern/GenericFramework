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
