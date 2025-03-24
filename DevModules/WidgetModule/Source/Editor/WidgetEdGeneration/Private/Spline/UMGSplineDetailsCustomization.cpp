// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Spline/UMGSplineDetailsCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "WidgetEdGenerationSetting.h"
#include "Spline/UMGSplineEditPanel.h"
#include "UWidget/Spline2D.h"

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

	USpline2D* SplineWidget = nullptr;
	for (int32 ObjectIndex = 0; ObjectIndex < SelectedObjects.Num(); ++ObjectIndex)
	{
		UObject* SelectObject = SelectedObjects[ObjectIndex].Get();
		if (USpline2D* TestSplineWidget = Cast<USpline2D>(SelectObject))
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

	PropertySplineInfo = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(USpline2D, SplineInfo), USpline2D::StaticClass());
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
				.SplineInfo_UObject(SplineWidget, &USpline2D::GetSplineInfo)
				.Clipping(EWidgetClipping::ClipToBounds)
				.OnSplineInfoValueChanged(FOnSpline2DInfoChanged::CreateSP(this, &FUMGSplineDetailsCustomization::OnSplineInfoValueChanged))
			]
		]
	];


	MyDetailLayout = &DetailLayout;
}

void FUMGSplineDetailsCustomization::OnSplineInfoValueChanged(const FSpline2DInfo& NewSplineInfo)
{
	FString TextValue;
	FSpline2DInfo::StaticStruct()->ExportText(TextValue, &NewSplineInfo, &NewSplineInfo, nullptr, EPropertyPortFlags::PPF_None, nullptr);

	const FPropertyAccess::Result Result = PropertySplineInfo->SetValueFromFormattedString(TextValue, EPropertyValueSetFlags::NotTransactable);
	check(Result == FPropertyAccess::Success);
}

FOptionalSize FUMGSplineDetailsCustomization::GetSplineEditPanelHieght() const
{
	return UWidgetEdGenerationSetting::Get()->PanelHeight;
}


#undef LOCTEXT_NAMESPACE
