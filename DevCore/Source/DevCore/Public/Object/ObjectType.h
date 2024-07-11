// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ObjectType.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInstanceObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UObject* InstanceObject;
};

/**
 * 
 */
USTRUCT()
struct FUniformInstanceObject : public FInstanceObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Row = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Column = 0;
};
