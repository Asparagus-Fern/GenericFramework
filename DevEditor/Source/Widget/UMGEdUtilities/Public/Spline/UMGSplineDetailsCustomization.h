// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"

#include "IDetailCustomization.h"
#include "UMGSplineType.h"

class UUMGSpline;
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
	void OnSplineInfoValueChanged(const FUMGSplineInfo& NewSplineInfo);
	FOptionalSize GetSplineEditPanelHieght() const;

private:
	TWeakObjectPtr<UUMGSpline> SplineWidgetPtr;

	IDetailLayoutBuilder* MyDetailLayout;

	TSharedPtr<IPropertyHandle> PropertySplineInfo;
};
