// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESimpleTextBoxType:uint8
{
	Horizontal,
	Vertical,
	HorizontalReversal,
	VerticalReversal
};

/**
 * 
 */
class DEVSLATECORE_API SSimpleTextBox : public SCompoundWidget
{
	SLATE_DECLARE_WIDGET(SSimpleTextBox, SCompoundWidget)

public:
	SLATE_BEGIN_ARGS(SSimpleTextBox)
			: _Text(),
			  _TextColor(),
			  _TextFont(),
			  _TextStrikeBrush(),
			  _TextShadowOffset(),
			  _TextShadowColor(),
			  _HighlightText(),
			  _TextHighlightShape(),
			  _AutoWrapText(false),
			  _WrapTextAt(0.0f),
			  _WrappingPolicy(ETextWrappingPolicy::DefaultWrapping),
			  _TransformPolicy(),
			  _Justification(ETextJustify::Left),
			  _MinDesiredWidth(0.0f),
			  _LineHeightPercentage(1.0f),
			  _TextMargin(),
			  _OverflowPolicy(),
			  _Space(0.f),
			  _Image(FCoreStyle::Get().GetDefaultBrush()),
			  _ImageColor(FLinearColor::White),
			  _ImageMargin(),
			  _SimpleTextBoxType(ESimpleTextBoxType::Horizontal),
			  _TextHorizontalAlignment(HAlign_Center),
			  _TextVerticalAlignment(VAlign_Center),
			  _ImageHorizontalAlignment(HAlign_Center),
			  _ImageVerticalAlignment(VAlign_Center)
		{
		}

		SLATE_ATTRIBUTE(FText, Text)
		SLATE_ATTRIBUTE(FSlateColor, TextColor)
		SLATE_ATTRIBUTE(FSlateFontInfo, TextFont)
		SLATE_ATTRIBUTE(const FSlateBrush*, TextStrikeBrush)
		SLATE_ATTRIBUTE(FVector2D, TextShadowOffset)
		SLATE_ATTRIBUTE(FLinearColor, TextShadowColor)
		SLATE_ATTRIBUTE(FText, HighlightText)
		SLATE_ATTRIBUTE(const FSlateBrush*, TextHighlightShape)
		SLATE_ATTRIBUTE(bool, AutoWrapText)
		SLATE_ATTRIBUTE(float, WrapTextAt)
		SLATE_ATTRIBUTE(ETextWrappingPolicy, WrappingPolicy)
		SLATE_ATTRIBUTE(ETextTransformPolicy, TransformPolicy)
		SLATE_ATTRIBUTE(ETextJustify::Type, Justification)
		SLATE_ATTRIBUTE(float, MinDesiredWidth)
		SLATE_ATTRIBUTE(float, LineHeightPercentage)
		SLATE_ATTRIBUTE(FMargin, TextMargin)
		SLATE_ARGUMENT(TOptional<ETextOverflowPolicy>, OverflowPolicy)

		SLATE_ATTRIBUTE(float, Space)

		SLATE_ATTRIBUTE(const FSlateBrush*, Image)
		SLATE_ATTRIBUTE(FSlateColor, ImageColor)
		SLATE_ATTRIBUTE(FMargin, ImageMargin)

		SLATE_ATTRIBUTE(ESimpleTextBoxType, SimpleTextBoxType)
		SLATE_ATTRIBUTE(FMargin, Padding)
		SLATE_ATTRIBUTE(EHorizontalAlignment, TextHorizontalAlignment)
		SLATE_ATTRIBUTE(EVerticalAlignment, TextVerticalAlignment)
		SLATE_ATTRIBUTE(EHorizontalAlignment, ImageHorizontalAlignment)
		SLATE_ATTRIBUTE(EVerticalAlignment, ImageVerticalAlignment)

	SLATE_END_ARGS()

	SSimpleTextBox();
	void Construct(const FArguments& InArgs);
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;

protected:
	TSharedPtr<STextBlock> TextPtr;
	TSharedPtr<SSpacer> SpacerPtr;
	TSharedPtr<SImage> ImagePtr;

protected:
	TSlateAttribute<FMargin> ImageMarginAttribute;

protected:
	TSlateAttribute<ESimpleTextBoxType> SimpleTextBoxTypeAttribute;
	TSlateAttribute<FMargin> PaddingAttribute;
	TSlateAttribute<EHorizontalAlignment> TextHorizontalAlignmentAttribute;
	TSlateAttribute<EVerticalAlignment> TextVerticalAlignmentAttribute;
	TSlateAttribute<EHorizontalAlignment> ImageHorizontalAlignmentAttribute;
	TSlateAttribute<EVerticalAlignment> ImageVerticalAlignmentAttribute;

public:
	void SetText(const TAttribute<FText>& InText) const;
	void SetTextColor(const TAttribute<FSlateColor>& InTextColor) const;
	void SetTextFont(const TAttribute<FSlateFontInfo>& InTextFont) const;
	void SetTextStrikeBrush(const TAttribute<const FSlateBrush*>& InTextStrikeBrush) const;
	void SetTextShadowOffset(const TAttribute<FVector2D>& InTextShadowOffset) const;
	void SetTextShadowColor(const TAttribute<FLinearColor>& InTextShadowColor) const;
	void SetTextHighlightText(const TAttribute<FText>& InHighlightText) const;
	void SetTextHighlightShape(const TAttribute<const FSlateBrush*>& InTextHighlightShape) const;
	void SetAutoWrapText(const TAttribute<bool>& InAutoWrapText) const;
	void SetWrapTextAt(const TAttribute<float>& InWrapTextAt) const;
	void SetWrappingPolicy(const TAttribute<ETextWrappingPolicy>& InWrappingPolicy) const;
	void SetTransformPolicy(const TAttribute<ETextTransformPolicy>& InTransformPolicy) const;
	void SetJustification(const TAttribute<ETextJustify::Type>& InJustification) const;
	void SetMinDesiredWidth(const TAttribute<float>& InMinDesiredWidth) const;
	void SetLineHeightPercentage(const TAttribute<float>& InLineHeightPercentage) const;
	void SetTextMargin(const TAttribute<FMargin>& InTextMargin) const;
	void SetOverflowPolicy(const TOptional<ETextOverflowPolicy>& InOverflowPolicy) const;

public:
	void SetSpace(const TAttribute<float>& InSpace) const;

public:
	FMargin GetImageMargin() const { return ImageMarginAttribute.Get(); }
	EVisibility GetImageVisibility() const { return ImagePtr->GetVisibility(); }

	void SetImage(const TAttribute<const FSlateBrush*>& InImage) const;
	void SetImageColor(const TAttribute<FSlateColor>& InImageColor) const;
	void SetImageMargin(TAttribute<FMargin> InImageMargin);
	void SetImageVisibility(EVisibility InImageVisibility) const;

public:
	ESimpleTextBoxType GetSimpleTextBoxType() const { return SimpleTextBoxTypeAttribute.Get(); }
	FMargin GetPadding() const { return PaddingAttribute.Get(); }
	EHorizontalAlignment GetTextHorizontalAlignment() const { return TextHorizontalAlignmentAttribute.Get(); }
	EVerticalAlignment GetTextVerticalAlignment() const { return TextVerticalAlignmentAttribute.Get(); }
	EHorizontalAlignment GetImageHorizontalAlignment() const { return ImageHorizontalAlignmentAttribute.Get(); }
	EVerticalAlignment GetImageVerticalAlignment() const { return ImageVerticalAlignmentAttribute.Get(); }

	void SetSimpleTextBoxType(TAttribute<ESimpleTextBoxType> InSimpleTextBoxType);
	void SetPadding(TAttribute<FMargin> InPadding);
	void SetTextHorizontalAlignment(TAttribute<EHorizontalAlignment> InTextHorizontalAlignment);
	void SetTextVerticalAlignment(TAttribute<EVerticalAlignment> InTextVerticalAlignment);
	void SetImageHorizontalAlignment(TAttribute<EHorizontalAlignment> InImageHorizontalAlignment);
	void SetImageVerticalAlignment(TAttribute<EVerticalAlignment> InImageVerticalAlignment);

public:
	void UpdateSimpleTextLayout();
};
