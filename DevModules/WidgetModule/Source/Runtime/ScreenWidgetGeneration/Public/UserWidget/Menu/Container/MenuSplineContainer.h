// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Menu/MenuContainer.h"
#include "MenuSplineContainer.generated.h"

class USpline2D;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UMenuSplineContainer : public UMenuContainer
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;
	virtual void ConstructMenuContainer_Implementation(UMenuStyle* MenuStyle, int32 Index) override;
	virtual void DestructMenuContainer_Implementation(UMenuStyle* MenuStyle) override;

public:
	UPROPERTY(EditAnywhere)
	float SpacingAtSpline = 0.1f;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateMenuPositionAtSpline();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USpline2D> Spline2D;
};
