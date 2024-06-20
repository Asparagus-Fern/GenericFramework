// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticFunctions/StaticFunctions_Folder.h"

bool FStaticFunctions_Folder::ExistFolder(const TCHAR* FolderFullPath)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.DirectoryExists(FolderFullPath);
}

void FStaticFunctions_Folder::CreateFolder(const TCHAR* FolderFullPath)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.CreateDirectoryTree(FolderFullPath);
}
