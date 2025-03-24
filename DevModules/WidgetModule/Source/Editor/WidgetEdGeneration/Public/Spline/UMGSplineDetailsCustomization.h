// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"

#include "IDetailCustomization.h"
#include "Spline2DType.h"

class USpline2D;
class IDetailLayoutBuilder;

/**
 * 
 */
class FUMGSplineDetailsCustomization final : public IDetailCustomization
{
public:
	FUMGSplineDetailsCustomization() = default;
	virtual ~FUMGSplineDetailsCustomization() override = default;

	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

protected:
	void OnSplineInfoValueChanged(const FSpline2DInfo& NewSplineInfo);
	FOptionalSize GetSplineEditPanelHieght() const;

private:
	TWeakObjectPtr<USpline2D> SplineWidgetPtr;

	IDetailLayoutBuilder* MyDetailLayout;

	TSharedPtr<IPropertyHandle> PropertySplineInfo;
};
