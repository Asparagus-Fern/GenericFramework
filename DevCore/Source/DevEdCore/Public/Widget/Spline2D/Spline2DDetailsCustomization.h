// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "IDetailCustomization.h"
#include "SWidget/Spline2D/Spline2DType.h"

class USpline2D;
class IDetailLayoutBuilder;

/**
 * 
 */
class FSpline2DDetailsCustomization final : public IDetailCustomization
{
public:
	FSpline2DDetailsCustomization() = default;
	virtual ~FSpline2DDetailsCustomization() override = default;

	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:
	void OnSplineInfoValueChanged(const FSpline2DInfo& NewSplineInfo);
	FOptionalSize GetSplineEditPanelHeight() const;

private:
	TWeakObjectPtr<USpline2D> SplineWidgetPtr;

	IDetailLayoutBuilder* MyDetailLayout;

	TSharedPtr<IPropertyHandle> PropertySplineInfo;
};
