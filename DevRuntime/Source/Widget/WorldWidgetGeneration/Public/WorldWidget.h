// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Group/CommonButton.h"
#include "WorldWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideCategories=(Interaction,Layout,Localization,Performance,Rendering,Navigation,Designer,Locked,Selection,Input))
class WORLDWIDGETGENERATION_API UWorldWidget : public UCommonButton
{
	GENERATED_BODY()

public:
	UWorldWidget(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Anchor = FVector2D(.5f, 0.f);

public:
	UFUNCTION(BlueprintPure)
	FVector2D GetAnchorOffset() const;
};
