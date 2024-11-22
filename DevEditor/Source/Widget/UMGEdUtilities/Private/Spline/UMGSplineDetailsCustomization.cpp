// Fill out your copyright notice in the Description page of Project Settings.

#include "Spline/UMGSplineDetailsCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "UMGEdUtilitiesSetting.h"
#include "Spline/UMGSplineEditPanel.h"
#include "UWidget/UMGSpline.h"


#define LOCTEXT_NAMESPACE "SplineWidgetDetails"

TSharedRef<IDetailCustomization> FUMGSplineDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FUMGSplineDetailsCustomization);
}

void FUMGSplineDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	const TArray<TWeakObjectPtr<UObject>>& SelectedObjects = DetailLayout.GetSelectedObjects();
	if (SelectedObjects.Num() != 1)
	{
		return;
	}

	UUMGSpline* SplineWidget = nullptr;
	for (int32 ObjectIndex = 0; ObjectIndex < SelectedObjects.Num(); ++ObjectIndex)
	{
		UObject* SelectObject = SelectedObjects[ObjectIndex].Get();
		if (UUMGSpline* TestSplineWidget = Cast<UUMGSpline>(SelectObject))
		{
			SplineWidget = TestSplineWidget;
			break;
		}
	}

	if (!SplineWidget)
	{
		return;
	}

	SplineWidgetPtr = SplineWidget;

	PropertySplineInfo = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUMGSpline, SplineInfo), UUMGSpline::StaticClass());
	check(PropertySplineInfo->IsValidHandle());
	 
	IDetailCategoryBuilder& EditSplineCategory = DetailLayout.EditCategory("EditSpline", FText::GetEmpty(), ECategoryPriority::TypeSpecific);

	FText SplineEditText = LOCTEXT("UMGSplineEditPanel", "Spline Edit Panel");
	EditSplineCategory.AddCustomRow(SplineEditText)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.HeightOverride(this, &FUMGSplineDetailsCustomization::GetSplineEditPanelHieght)
			[
				SNew(SUMGSplineEditPanel)
				.SplineInfo_UObject(SplineWidget, &UUMGSpline::GetSplineInfo)
				.Clipping(EWidgetClipping::ClipToBounds)
				.OnSplineInfoValueChanged(FOnSplineInfoValueChanged::CreateSP(this, &FUMGSplineDetailsCustomization::OnSplineInfoValueChanged))
			]
		]
	];


	MyDetailLayout = &DetailLayout;
}

void FUMGSplineDetailsCustomization::OnSplineInfoValueChanged(const FUMGSplineInfo& NewSplineInfo)
{
	FString TextValue;
	FUMGSplineInfo::StaticStruct()->ExportText(TextValue, &NewSplineInfo, &NewSplineInfo, nullptr, EPropertyPortFlags::PPF_None, nullptr);

	const FPropertyAccess::Result Result = PropertySplineInfo->SetValueFromFormattedString(TextValue, EPropertyValueSetFlags::NotTransactable);
	check(Result == FPropertyAccess::Success);
}

FOptionalSize FUMGSplineDetailsCustomization::GetSplineEditPanelHieght() const
{
	return UUMGEdUtilitiesSetting::Get()->PanelHeight;
}


#undef LOCTEXT_NAMESPACE
