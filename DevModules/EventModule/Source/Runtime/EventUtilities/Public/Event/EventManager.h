// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/EngineSubsystem.h"
#include "EventManager.generated.h"

/**
 * 
 */
UCLASS()
class EVENTUTILITIES_API UEventManager : public UEngineSubsystem, public FCoreInternalManager,
{
	GENERATED_BODY()
};
