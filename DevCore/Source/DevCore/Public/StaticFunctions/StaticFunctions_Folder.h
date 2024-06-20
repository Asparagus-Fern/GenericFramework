// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class DEVCORE_API FStaticFunctions_Folder
{
public:
	static bool ExistFolder(const TCHAR* FolderFullPath);
	static void CreateFolder(const TCHAR* FolderFullPath);
};
