// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "RoadNetworkType.generated.h"

UENUM(BlueprintType)
enum class ERoadNetworkType:uint8
{
	Highway UMETA(DisplayName="公路"),
	Waterway UMETA(DisplayName="水路"),
	Railway UMETA(DisplayName="铁路"),
	Aerialway UMETA(DisplayName="航空路线"),
};
