// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateWidgetType.h"
#include "Components/ContentWidget.h"
#include "Components/Widget.h"
#include "Line.generated.h"

class SLine;

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
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter= "GetAnchor", BlueprintSetter="SetAnchor")
	FVector2D Anchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter= "GetThickness", BlueprintSetter="SetThickness")
	float Thickness = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter= "GetLineColor", BlueprintSetter="SetLineColor")
	FLinearColor LineColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintGetter= "GetLinePoints", BlueprintSetter="SetLinePoints")
	TArray<FLinePoint> LinePoints;

public:
	UFUNCTION(BlueprintPure)
	FVector2D GetAnchor() const;

	UFUNCTION(BlueprintCallable)
	void SetAnchor(FVector2D InAnchor);

	UFUNCTION(BlueprintPure)
	float GetThickness() const;

	UFUNCTION(BlueprintCallable)
	void SetThickness(float InThickness);

	UFUNCTION(BlueprintPure)
	FLinearColor GetLineColor() const;

	UFUNCTION(BlueprintCallable)
	void SetLineColor(FLinearColor InLineColor);

	UFUNCTION(BlueprintPure)
	TArray<FLinePoint> GetLinePoints() const;

	UFUNCTION(BlueprintCallable)
	void SetLinePoints(TArray<FLinePoint> InLinePoints);

protected:
	TSharedPtr<SLine> MyLine;
};
