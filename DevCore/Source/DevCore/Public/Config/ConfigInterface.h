// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
class DEVCORE_API IConfigInterface
{
public:
	virtual ~IConfigInterface() { return; }
	FString GetSaveIniPath() { return GetSaveIniBasePath() + GetSaveIniRelativePath() + GetSaveIniFileName(); }
	virtual FString GetSaveIniBasePath() { return FPaths::ProjectConfigDir(); }
	virtual FString GetSaveIniRelativePath() { return ""; }
	virtual FString GetSaveIniFileName() { return "DefaultManager.ini"; }
};
