// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"

class FDevCoreModule : public ICommonModuleInterface
{
public:
	virtual void GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses) override;
};
