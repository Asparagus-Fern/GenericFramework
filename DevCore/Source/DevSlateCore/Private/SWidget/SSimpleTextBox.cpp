// Fill out your copyright notice in the Description page of Project Settings.

#include "SWidget/SSimpleTextBox.h"

#include "SlateOptMacros.h"
#include "Layout/Visibility.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SBoxPanel.h"
#include "Fonts/SlateFontInfo.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SLATE_IMPLEMENT_WIDGET(SSimpleTextBox)

void SSimpleTextBox::PrivateRegisterAttributes(FSlateAttributeInitializer& AttributeInitializer)
{
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, ImageMarginAttribute, EInvalidateWidgetReason::Layout);

	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, SimpleTextBoxTypeAttribute, EInvalidateWidgetReason::Layout);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, PaddingAttribute, EInvalidateWidgetReason::Layout);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, TextHorizontalAlignmentAttribute, EInvalidateWidgetReason::Layout);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, TextVerticalAlignmentAttribute, EInvalidateWidgetReason::Layout);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, ImageHorizontalAlignmentAttribute, EInvalidateWidgetReason::Layout);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION(AttributeInitializer, ImageVerticalAlignmentAttribute, EInvalidateWidgetReason::Layout);
}

SSimpleTextBox::SSimpleTextBox()
	: ImageMarginAttribute(*this),
	  SimpleTextBoxTypeAttribute(*this),
	  PaddingAttribute(*this),
	  TextHorizontalAlignmentAttribute(*this),
	  TextVerticalAlignmentAttribute(*this),
	  ImageHorizontalAlignmentAttribute(*this),
	  ImageVerticalAlignmentAttribute(*this)
{
}

void SSimpleTextBox::Construct(const FArguments& InArgs)
{
	SpacerPtr = SNew(SSpacer)
		.Size(FVector2D(InArgs._Space.Get(), InArgs._Space.Get()));

	TextPtr = SNew(STextBlock)
		.Text(InArgs._Text)
		.ColorAndOpacity(InArgs._TextColor)
		.Font(InArgs._TextFont)
		.StrikeBrush(InArgs._TextStrikeBrush)
		.ShadowOffset(InArgs._TextShadowOffset)
		.ShadowColorAndOpacity(InArgs._TextShadowColor)
		.HighlightText(InArgs._HighlightText)
		.HighlightShape(InArgs._TextHighlightShape)
		.AutoWrapText(InArgs._AutoWrapText)
		.WrapTextAt(InArgs._WrapTextAt)
		.WrappingPolicy(InArgs._WrappingPolicy)
		.TransformPolicy(InArgs._TransformPolicy)
		.Justification(InArgs._Justification)
		.MinDesiredWidth(InArgs._MinDesiredWidth)
		.LineHeightPercentage(InArgs._LineHeightPercentage)
		.Margin(InArgs._TextMargin)
		.OverflowPolicy(InArgs._OverflowPolicy)
		.Visibility(EVisibility::SelfHitTestInvisible);

	ImagePtr = SNew(SImage)
		.Image(InArgs._Image)
		.ColorAndOpacity(InArgs._ImageColor)
		.Visibility_Raw(this, &SSimpleTextBox::GetImageVisibility);

	ImageMarginAttribute.Assign(*this, InArgs._ImageMargin);

	SimpleTextBoxTypeAttribute.Assign(*this, InArgs._SimpleTextBoxType);
	PaddingAttribute.Assign(*this, InArgs._Padding);
	TextHorizontalAlignmentAttribute.Assign(*this, InArgs._TextHorizontalAlignment);
	TextVerticalAlignmentAttribute.Assign(*this, InArgs._TextVerticalAlignment);
	ImageHorizontalAlignmentAttribute.Assign(*this, InArgs._ImageHorizontalAlignment);
	ImageVerticalAlignmentAttribute.Assign(*this, InArgs._ImageVerticalAlignment);

	UpdateSimpleTextLayout();
}

FVector2D SSimpleTextBox::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return SCompoundWidget::ComputeDesiredSize(LayoutScaleMultiplier);
}

void SSimpleTextBox::SetText(const TAttribute<FText>& InText) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetText(InText);
	}
}

void SSimpleTextBox::SetTextColor(const TAttribute<FSlateColor>& InTextColor) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetColorAndOpacity(InTextColor);
	}
}

void SSimpleTextBox::SetTextFont(const TAttribute<FSlateFontInfo>& InTextFont) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetFont(InTextFont);
	}
}

void SSimpleTextBox::SetTextStrikeBrush(const TAttribute<const FSlateBrush*>& InTextStrikeBrush) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetStrikeBrush(InTextStrikeBrush);
	}
}

void SSimpleTextBox::SetTextShadowOffset(const TAttribute<FVector2D>& InTextShadowOffset) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetShadowOffset(InTextShadowOffset);
	}
}

void SSimpleTextBox::SetTextShadowColor(const TAttribute<FLinearColor>& InTextShadowColor) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetShadowColorAndOpacity(InTextShadowColor);
	}
}

void SSimpleTextBox::SetTextHighlightText(const TAttribute<FText>& InHighlightText) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetHighlightText(InHighlightText);
	}
}

void SSimpleTextBox::SetTextHighlightShape(const TAttribute<const FSlateBrush*>& InTextHighlightShape) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetHighlightShape(InTextHighlightShape);
	}
}

void SSimpleTextBox::SetAutoWrapText(const TAttribute<bool>& InAutoWrapText) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetAutoWrapText(InAutoWrapText);
	}
}

void SSimpleTextBox::SetWrapTextAt(const TAttribute<float>& InWrapTextAt) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetWrapTextAt(InWrapTextAt);
	}
}

void SSimpleTextBox::SetWrappingPolicy(const TAttribute<ETextWrappingPolicy>& InWrappingPolicy) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetWrappingPolicy(InWrappingPolicy);
	}
}

void SSimpleTextBox::SetTransformPolicy(const TAttribute<ETextTransformPolicy>& InTransformPolicy) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetTransformPolicy(InTransformPolicy);
	}
}

void SSimpleTextBox::SetJustification(const TAttribute<ETextJustify::Type>& InJustification) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetJustification(InJustification);
	}
}

void SSimpleTextBox::SetMinDesiredWidth(const TAttribute<float>& InMinDesiredWidth) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetMinDesiredWidth(InMinDesiredWidth);
	}
}

void SSimpleTextBox::SetLineHeightPercentage(const TAttribute<float>& InLineHeightPercentage) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetLineHeightPercentage(InLineHeightPercentage);
	}
}

void SSimpleTextBox::SetTextMargin(const TAttribute<FMargin>& InTextMargin) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetMargin(InTextMargin);
	}
}

void SSimpleTextBox::SetOverflowPolicy(const TOptional<ETextOverflowPolicy>& InOverflowPolicy) const
{
	if (TextPtr.IsValid())
	{
		TextPtr->SetOverflowPolicy(InOverflowPolicy);
	}
}

void SSimpleTextBox::SetSpace(const TAttribute<float>& InSpace) const
{
	if (SpacerPtr.IsValid())
	{
		SpacerPtr->SetSize(FVector2D(InSpace.Get(), InSpace.Get()));
	}
}

void SSimpleTextBox::SetImage(const TAttribute<const FSlateBrush*>& InImage) const
{
	if (ImagePtr.IsValid())
	{
		ImagePtr->SetImage(InImage);
	}
}

void SSimpleTextBox::SetImageColor(const TAttribute<FSlateColor>& InImageColor) const
{
	if (ImagePtr.IsValid())
	{
		ImagePtr->SetColorAndOpacity(InImageColor);
	}
}

void SSimpleTextBox::SetImageMargin(TAttribute<FMargin> InImageMargin)
{
	ImageMarginAttribute.Assign(*this, MoveTemp(InImageMargin));
	UpdateSimpleTextLayout();
}

void SSimpleTextBox::SetImageVisibility(EVisibility InImageVisibility) const
{
	ImagePtr->SetVisibility(InImageVisibility);
}

void SSimpleTextBox::SetSimpleTextBoxType(TAttribute<ESimpleTextBoxType> InSimpleTextBoxType)
{
	SimpleTextBoxTypeAttribute.Assign(*this, MoveTemp(InSimpleTextBoxType));
	UpdateSimpleTextLayout();
}

void SSimpleTextBox::SetPadding(TAttribute<FMargin> InPadding)
{
	PaddingAttribute.Assign(*this, MoveTemp(InPadding));
	UpdateSimpleTextLayout();
}

void SSimpleTextBox::SetTextHorizontalAlignment(TAttribute<EHorizontalAlignment> InTextHorizontalAlignment)
{
	TextHorizontalAlignmentAttribute.Assign(*this, MoveTemp(InTextHorizontalAlignment));
	UpdateSimpleTextLayout();
}

void SSimpleTextBox::SetTextVerticalAlignment(TAttribute<EVerticalAlignment> InTextVerticalAlignment)
{
	TextVerticalAlignmentAttribute.Assign(*this, MoveTemp(InTextVerticalAlignment));
	UpdateSimpleTextLayout();
}

void SSimpleTextBox::SetImageHorizontalAlignment(TAttribute<EHorizontalAlignment> InImageHorizontalAlignment)
{
	ImageHorizontalAlignmentAttribute.Assign(*this, MoveTemp(InImageHorizontalAlignment));
	UpdateSimpleTextLayout();
}

void SSimpleTextBox::SetImageVerticalAlignment(TAttribute<EVerticalAlignment> InImageVerticalAlignment)
{
	ImageVerticalAlignmentAttribute.Assign(*this, MoveTemp(InImageVerticalAlignment));
	UpdateSimpleTextLayout();
}

void SSimpleTextBox::UpdateSimpleTextLayout()
{
	TSharedRef<SWidget> Panel = SNullWidget::NullWidget;

	switch (GetSimpleTextBoxType())
	{
	case ESimpleTextBoxType::Horizontal:
		Panel = SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(GetImageHorizontalAlignment())
			.VAlign(GetImageVerticalAlignment())
			.Padding(GetImageMargin())
			[
				ImagePtr.ToSharedRef()
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.f)
			[
				SpacerPtr.ToSharedRef()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(GetTextHorizontalAlignment())
			.VAlign(GetTextVerticalAlignment())
			[
				TextPtr.ToSharedRef()
			];
		break;

	case ESimpleTextBoxType::Vertical:
		Panel = SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(GetImageHorizontalAlignment())
			.VAlign(GetImageVerticalAlignment())
			.Padding(GetImageMargin())
			[
				ImagePtr.ToSharedRef()
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				SpacerPtr.ToSharedRef()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(GetTextHorizontalAlignment())
			.VAlign(GetTextVerticalAlignment())
			[
				TextPtr.ToSharedRef()
			];
		break;

	case ESimpleTextBoxType::HorizontalReversal:
		Panel = SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(GetTextHorizontalAlignment())
			.VAlign(GetTextVerticalAlignment())
			[
				TextPtr.ToSharedRef()
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.f)
			[
				SpacerPtr.ToSharedRef()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(GetImageHorizontalAlignment())
			.VAlign(GetImageVerticalAlignment())
			.Padding(GetImageMargin())
			[
				ImagePtr.ToSharedRef()
			];
		break;

	case ESimpleTextBoxType::VerticalReversal:
		Panel = SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(GetTextHorizontalAlignment())
			.VAlign(GetTextVerticalAlignment())
			[
				TextPtr.ToSharedRef()
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				SpacerPtr.ToSharedRef()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(GetImageHorizontalAlignment())
			.VAlign(GetImageVerticalAlignment())
			.Padding(GetImageMargin())
			[
				ImagePtr.ToSharedRef()
			];
		break;
	}

	ChildSlot
		.Padding(GetPadding())
		[
			Panel
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
