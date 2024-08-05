// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LineSegment.h"
#include "AnimationLineSegment.generated.h"

/**
 * 连接多条线段，并提供线段的延展动画
 */
UCLASS()
class DEVSLATECORE_API UAnimationLineSegment : public ULineSegment
{
	GENERATED_BODY()

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetDuration", BlueprintSetter="SetDuration")
	float Duration = 1.f;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetCurveType", BlueprintSetter="SetCurveType")
	ESequenceTransitionCurve CurveType;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTransitionFinish OnTransitionFinish;

public:
	UFUNCTION(BlueprintPure)
	float GetDuration() const;

	UFUNCTION(BlueprintCallable)
	void SetDuration(float InDuration);

	UFUNCTION(BlueprintPure)
	ESequenceTransitionCurve GetCurveType() const;

	UFUNCTION(BlueprintCallable)
	void SetCurveType(ESequenceTransitionCurve InCurveType);

public:
	UFUNCTION(BlueprintCallable)
	void PlayTransition(bool PlayForward);

protected:
	virtual void HandleTransitionFinish();
};
