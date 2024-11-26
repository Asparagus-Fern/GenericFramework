// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelSlot.h"
#include "SWidget/SSpline2D.h"
#include "Spline2DSlot.generated.h"

class SSpline2D;

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API USpline2DSlot : public UPanelSlot
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	void BuildSlot(TSharedRef<SSpline2D> InUMGSpline);

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetHorizontalAlignment", BlueprintSetter = "SetHorizontalAlignment", Category="Layout|UMG Spline Slot")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = EHorizontalAlignment::HAlign_Center;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetVerticalAlignment", BlueprintSetter = "SetVerticalAlignment", Category="Layout|UMG Spline Slot")
	TEnumAsByte<EVerticalAlignment> VerticalAlignment = EVerticalAlignment::VAlign_Center;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetOffset", BlueprintSetter = "SetOffset", Category = "Layout|UMG Spline Slot")
	FVector2D Offset = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetValue", BlueprintSetter = "SetValue", Category = "Layout|UMG Spline Slot", meta=(ClampMin = 0, UIMin = 0, ClampMax = 1, UIMax = 1))
	float Value = 0.f;

public:
	UFUNCTION(BlueprintPure, Category="Layout|UMG Spline Slot")
	EHorizontalAlignment GetHorizontalAlignment() const;

	UFUNCTION(BlueprintCallable, Category="Layout|UMG Spline Slot")
	void SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment);

	UFUNCTION(BlueprintPure, Category="Layout|UMG Spline Slot")
	EVerticalAlignment GetVerticalAlignment() const;

	UFUNCTION(BlueprintCallable, Category="Layout|UMG Spline Slot")
	void SetVerticalAlignment(EVerticalAlignment InVerticalAlignment);

	UFUNCTION(BlueprintPure, Category="Layout|UMG Spline Slot")
	FVector2D GetOffset() const;

	UFUNCTION(BlueprintCallable, Category="Layout|UMG Spline Slot")
	void SetOffset(FVector2D InOffset);

	UFUNCTION(BlueprintPure, Category="Layout|UMG Spline Slot")
	float GetValue() const;

	UFUNCTION(BlueprintCallable, Category="Layout|UMG Spline Slot")
	void SetValue(float InValue);

private:
	SSpline2D::FSpline2DSlot* Slot;
	TWeakPtr<SSpline2D> MySpline2D;
};
