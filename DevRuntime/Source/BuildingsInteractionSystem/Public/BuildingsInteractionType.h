// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingsInteractionType.generated.h"

USTRUCT(BlueprintType)
struct FFloorStaticMeshInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Transform;
};
