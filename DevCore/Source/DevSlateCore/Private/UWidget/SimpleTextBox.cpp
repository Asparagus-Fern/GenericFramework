// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UWidget/SimpleTextBox.h"

#include "Engine/Font.h"
#include "SWidget/SSimpleTextBox.h"
#include "UObject/ConstructorHelpers.h"
#include "Fonts/SlateFontInfo.h"

USimpleTextBox::USimpleTextBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Text = FText::FromString("SimpleTextBox");
	TextColor = FLinearColor::White;
	TextStrikeBrush = *FCoreStyle::Get().GetBrush("NoBorder");
	TextShadowOffset = FVector2D::Zero();
	TextShadowColor = FLinearColor::Transparent;
	HighlightText = FText::GetEmpty();
	TextHighlightShape = *FCoreStyle::Get().GetBrush("NoBorder");
	AutoWrapText = false;
	WrapTextAt = 0.f;
	WrappingPolicy = ETextWrappingPolicy::DefaultWrapping;
	TransformPolicy = ETextTransformPolicy::None;
	Justification = ETextJustify::Type::Left;
	MinDesiredWidth = 0.f;
	LineHeightPercentage = 1.f;
	TextMargin = FMargin(0.f);
	OverflowPolicy = ETextOverflowPolicy::Clip;

	Space = 0.f;

	ImageColor = FLinearColor::White;
	ImageMargin = FMargin(0.f);
	ImageVisibility = ESlateVisibility::SelfHitTestInvisible;

	SimpleTextBoxType = ESimpleTextBoxType::Horizontal;
	Padding = FMargin(0.f);
	TextHorizontalAlignment = HAlign_Center;
	TextVerticalAlignment = VAlign_Center;
	ImageHorizontalAlignment = HAlign_Center;
	ImageVerticalAlignment = VAlign_Center;

	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*GetDefaultFontName());
		TextFont = FSlateFontInfo(RobotoFontObj.Object, 16, FName("Light"));
	}
}

TSharedRef<SWidget> USimpleTextBox::RebuildWidget()
{
	MySimpleTextBox = SNew(SSimpleTextBox);
	return MySimpleTextBox.ToSharedRef();
}

void USimpleTextBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (MySimpleTextBox.IsValid())
	{
		SetText(Text);
		SetTextColor(TextColor);
		SetTextFont(TextFont);
		SetTextStrikeBrush(TextStrikeBrush);
		SetTextShadowOffset(TextShadowOffset);
		SetTextShadowColor(TextShadowColor);
		SetHighlightText(HighlightText);
		SetTextHighlightShape(TextHighlightShape);
		SetAutoWrapText(AutoWrapText);
		SetWrapTextAt(WrapTextAt);
		SetWrappingPolicy(WrappingPolicy);
		SetTransformPolicy(TransformPolicy);
		SetJustification(Justification);
		SetMinDesiredWidth(MinDesiredWidth);
		SetLineHeightPercentage(LineHeightPercentage);
		SetTextMargin(TextMargin);
		SetOverflowPolicy(OverflowPolicy);

		SetSpace(Space);

		SetImage(Image);
		SetImageColor(ImageColor);
		SetImageMargin(ImageMargin);
		SetImageVisibility(ImageVisibility);

		SetSimpleTextBoxType(SimpleTextBoxType);
		SetPadding(Padding);
		SetTextHorizontalAlignment(TextHorizontalAlignment);
		SetTextVerticalAlignment(TextVerticalAlignment);
		SetImageHorizontalAlignment(ImageHorizontalAlignment);
		SetImageVerticalAlignment(ImageVerticalAlignment);
	}
}

void USimpleTextBox::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MySimpleTextBox.Reset();
}

FText USimpleTextBox::GetText() const
{
	return Text;
}

void USimpleTextBox::SetText(FText InText)
{
	Text = InText;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetText(InText);
	}
}

FSlateColor USimpleTextBox::GetTextColor() const
{
	return TextColor;
}

void USimpleTextBox::SetTextColor(FSlateColor InTextColor)
{
	TextColor = InTextColor;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextColor(InTextColor);
	}
}

FSlateFontInfo USimpleTextBox::GetTextFont() const
{
	return TextFont;
}

void USimpleTextBox::SetTextFont(FSlateFontInfo InTextFont)
{
	TextFont = InTextFont;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextFont(InTextFont);
	}
}

FSlateBrush USimpleTextBox::GetTextStrikeBrush() const
{
	return TextStrikeBrush;
}

void USimpleTextBox::SetTextStrikeBrush(const FSlateBrush& InTextStrikeBrush)
{
	TextStrikeBrush = InTextStrikeBrush;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextStrikeBrush(&InTextStrikeBrush);
	}
}

FVector2D USimpleTextBox::GetTextShadowOffset() const
{
	return TextShadowOffset;
}

void USimpleTextBox::SetTextShadowOffset(FVector2D InTextShadowOffset)
{
	TextShadowOffset = InTextShadowOffset;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextShadowOffset(InTextShadowOffset);
	}
}

FLinearColor USimpleTextBox::GetTextShadowColor() const
{
	return TextShadowColor;
}

void USimpleTextBox::SetTextShadowColor(FLinearColor InTextShadowColor)
{
	TextShadowColor = InTextShadowColor;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextShadowColor(InTextShadowColor);
	}
}

FText USimpleTextBox::GetHighlightText() const
{
	return HighlightText;
}

void USimpleTextBox::SetHighlightText(FText InHighlightText)
{
	HighlightText = InHighlightText;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextHighlightText(InHighlightText);
	}
}

FSlateBrush USimpleTextBox::GetTextHighlightShape() const
{
	return TextHighlightShape;
}

void USimpleTextBox::SetTextHighlightShape(const FSlateBrush& InTextHighlightShape)
{
	TextHighlightShape = InTextHighlightShape;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextHighlightShape(&InTextHighlightShape);
	}
}

bool USimpleTextBox::GetAutoWrapText() const
{
	return AutoWrapText;
}

void USimpleTextBox::SetAutoWrapText(bool InAutoWrapText)
{
	AutoWrapText = InAutoWrapText;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetAutoWrapText(InAutoWrapText);
	}
}

float USimpleTextBox::GetWrapTextAt() const
{
	return WrapTextAt;
}

void USimpleTextBox::SetWrapTextAt(float InWrapTextAt)
{
	WrapTextAt = InWrapTextAt;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetWrapTextAt(InWrapTextAt);
	}
}

ETextWrappingPolicy USimpleTextBox::GetWrappingPolicy() const
{
	return WrappingPolicy;
}

void USimpleTextBox::SetWrappingPolicy(ETextWrappingPolicy InWrappingPolicy)
{
	WrappingPolicy = InWrappingPolicy;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetWrappingPolicy(InWrappingPolicy);
	}
}

ETextTransformPolicy USimpleTextBox::GetTransformPolicy() const
{
	return TransformPolicy;
}

void USimpleTextBox::SetTransformPolicy(ETextTransformPolicy InTransformPolicy)
{
	TransformPolicy = InTransformPolicy;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTransformPolicy(InTransformPolicy);
	}
}

ETextJustify::Type USimpleTextBox::GetJustification() const
{
	return Justification;
}

void USimpleTextBox::SetJustification(ETextJustify::Type InJustification)
{
	Justification = InJustification;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetJustification(InJustification);
	}
}

float USimpleTextBox::GetMinDesiredWidth() const
{
	return MinDesiredWidth;
}

void USimpleTextBox::SetMinDesiredWidth(float InMinDesiredWidth)
{
	MinDesiredWidth = InMinDesiredWidth;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetMinDesiredWidth(InMinDesiredWidth);
	}
}

float USimpleTextBox::GetLineHeightPercentage() const
{
	return LineHeightPercentage;
}

void USimpleTextBox::SetLineHeightPercentage(float InLineHeightPercentage)
{
	LineHeightPercentage = InLineHeightPercentage;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetLineHeightPercentage(InLineHeightPercentage);
	}
}

FMargin USimpleTextBox::GetTextMargin() const
{
	return TextMargin;
}

void USimpleTextBox::SetTextMargin(const FMargin& InTextMargin)
{
	TextMargin = InTextMargin;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextMargin(InTextMargin);
	}
}

ETextOverflowPolicy USimpleTextBox::GetOverflowPolicy() const
{
	return OverflowPolicy;
}

void USimpleTextBox::SetOverflowPolicy(ETextOverflowPolicy InOverflowPolicy)
{
	OverflowPolicy = InOverflowPolicy;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetOverflowPolicy(InOverflowPolicy);
	}
}

float USimpleTextBox::GetSpace() const
{
	return Space;
}

void USimpleTextBox::SetSpace(float InSpace)
{
	Space = InSpace;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetSpace(InSpace);
	}
}

FSlateBrush USimpleTextBox::GetImage() const
{
	return Image;
}

void USimpleTextBox::SetImage(const FSlateBrush& InImage)
{
	Image = InImage;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetImage(&InImage);
	}
}

FSlateColor USimpleTextBox::GetImageColor() const
{
	return ImageColor;
}

void USimpleTextBox::SetImageColor(const FSlateColor& InImageColor)
{
	ImageColor = InImageColor;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetImageColor(InImageColor);
	}
}

FMargin USimpleTextBox::GetImageMargin() const
{
	return ImageMargin;
}

void USimpleTextBox::SetImageMargin(const FMargin& InImageMargin)
{
	ImageMargin = InImageMargin;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetImageMargin(InImageMargin);
	}
}

ESlateVisibility USimpleTextBox::GetImageVisibility() const
{
	return ImageVisibility;
}

void USimpleTextBox::SetImageVisibility(ESlateVisibility InImageVisibility)
{
	ImageVisibility = InImageVisibility;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetImageVisibility(ConvertVisibility(InImageVisibility));
	}
}

ESimpleTextBoxType USimpleTextBox::GetSimpleTextBoxType() const
{
	return SimpleTextBoxType;
}

void USimpleTextBox::SetSimpleTextBoxType(ESimpleTextBoxType InSimpleTextBoxType)
{
	SimpleTextBoxType = InSimpleTextBoxType;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetSimpleTextBoxType(InSimpleTextBoxType);
	}
}

FMargin USimpleTextBox::GetPadding() const
{
	return Padding;
}

void USimpleTextBox::SetPadding(const FMargin& InPadding)
{
	Padding = InPadding;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetPadding(InPadding);
	}
}

EHorizontalAlignment USimpleTextBox::GetTextHorizontalAlignment() const
{
	return TextHorizontalAlignment;
}

void USimpleTextBox::SetTextHorizontalAlignment(EHorizontalAlignment InTextHorizontalAlignment)
{
	TextHorizontalAlignment = InTextHorizontalAlignment;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextHorizontalAlignment(InTextHorizontalAlignment);
	}
}

EVerticalAlignment USimpleTextBox::GetTextVerticalAlignment() const
{
	return TextVerticalAlignment;
}

void USimpleTextBox::SetTextVerticalAlignment(EVerticalAlignment InTextVerticalAlignment)
{
	TextVerticalAlignment = InTextVerticalAlignment;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetTextVerticalAlignment(InTextVerticalAlignment);
	}
}

EHorizontalAlignment USimpleTextBox::GetImageHorizontalAlignment() const
{
	return ImageHorizontalAlignment;
}

void USimpleTextBox::SetImageHorizontalAlignment(EHorizontalAlignment InImageHorizontalAlignment)
{
	ImageHorizontalAlignment = InImageHorizontalAlignment;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetImageHorizontalAlignment(InImageHorizontalAlignment);
	}
}

EVerticalAlignment USimpleTextBox::GetImageVerticalAlignment() const
{
	return ImageVerticalAlignment;
}

void USimpleTextBox::SetImageVerticalAlignment(EVerticalAlignment InImageVerticalAlignment)
{
	InImageVerticalAlignment = InImageVerticalAlignment;
	if (MySimpleTextBox.IsValid())
	{
		MySimpleTextBox->SetImageVerticalAlignment(InImageVerticalAlignment);
	}
}
