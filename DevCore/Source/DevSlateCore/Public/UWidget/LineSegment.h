// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ContentWidget.h"
#include "SWidget/SLineSegment.h"
#include "LineSegment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTransitionFinish);

/**
 * 连接多条线段
 */
UCLASS(MinimalAPI)
class ULineSegment : public UContentWidget
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

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetOffset", BlueprintSetter="SetOffset")
	FVector2D Offset = FVector2D::Zero();

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetLineColor", BlueprintSetter="SetLineColor")
	FLinearColor LineColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetLinePoints", BlueprintSetter="SetLinePoints")
	TArray<FLineSegmentPoint> LinePoints;

public:
	UFUNCTION(BlueprintPure)
	float GetThickness() const;

	UFUNCTION(BlueprintCallable)
	void SetThickness(float InThickness);

	UFUNCTION(BlueprintPure)
	FVector2D GetOffset() const;

	UFUNCTION(BlueprintCallable)
	void SetOffset(FVector2D InOffset);

	UFUNCTION(BlueprintPure)
	FLinearColor GetLineColor() const;

	UFUNCTION(BlueprintCallable)
	void SetLineColor(FLinearColor InLineColor);

	UFUNCTION(BlueprintPure)
	TArray<FLineSegmentPoint> GetLinePoints() const;

	UFUNCTION(BlueprintCallable)
	void SetLinePoints(TArray<FLineSegmentPoint> InLinePoints);

public:
	UFUNCTION(BlueprintPure)
	TArray<FVector2D> GetPoints() const;

	UFUNCTION(BlueprintPure)
	TArray<FVector2D> GetPointsByAlpha(float Alpha) const;

	UFUNCTION(BlueprintPure)
	float GetLength() const;

protected:
	TSharedPtr<SLineSegment> MyLineSegment;
};
