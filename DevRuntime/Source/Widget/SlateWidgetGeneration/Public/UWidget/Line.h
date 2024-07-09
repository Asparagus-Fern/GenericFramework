// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateWidgetType.h"
#include "Components/ContentWidget.h"
#include "Slate/SCommonAnimatedSwitcher.h"
#include "Line.generated.h"

class SLine;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTransitionFinish);

/**
 * 
 */
UCLASS(MinimalAPI)
class ULine : public UContentWidget
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetThickness", BlueprintSetter="SetThickness")
	float Thickness = 1.f;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetDuration", BlueprintSetter="SetDuration")
	float Duration = 1.f;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetCurveType", BlueprintSetter="SetCurveType")
	ETransitionCurve CurveType;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetAnchor", BlueprintSetter="SetAnchor")
	FVector2D Anchor;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetLineColor", BlueprintSetter="SetLineColor")
	FLinearColor LineColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetLinePoints", BlueprintSetter="SetLinePoints")
	TArray<FLinePoint> LinePoints;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTransitionFinish OnTransitionFinish;

public:
	UFUNCTION(BlueprintPure)
	float GetThickness() const;

	UFUNCTION(BlueprintCallable)
	void SetThickness(float InThickness);

	UFUNCTION(BlueprintPure)
	float GetDuration() const;

	UFUNCTION(BlueprintCallable)
	void SetDuration(float InDuration);

	UFUNCTION(BlueprintPure)
	ETransitionCurve GetCurveType() const;

	UFUNCTION(BlueprintCallable)
	void SetCurveType(ETransitionCurve InCurveType);

	UFUNCTION(BlueprintPure)
	FVector2D GetAnchor() const;

	UFUNCTION(BlueprintCallable)
	void SetAnchor(FVector2D InAnchor);

	UFUNCTION(BlueprintPure)
	FLinearColor GetLineColor() const;

	UFUNCTION(BlueprintCallable)
	void SetLineColor(FLinearColor InLineColor);

	UFUNCTION(BlueprintPure)
	TArray<FLinePoint> GetLinePoints() const;

	UFUNCTION(BlueprintCallable)
	void SetLinePoints(TArray<FLinePoint> InLinePoints);

public:
	UFUNCTION(BlueprintCallable)
	void PlayTransition(bool bForward);

protected:
	TSharedPtr<SLine> MyLine;

	virtual void HandleTransitionFinish();
};
