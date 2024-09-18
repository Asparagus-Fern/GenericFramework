// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Components/Widget.h"
#include "SimpleTextBox.generated.h"

class SSimpleTextBox;

/**
 * 简单的Icon-Text类型的包装，不支持富文本以及输入框格式的Text
 */
UCLASS()
class DEVSLATECORE_API USimpleTextBox : public UWidget
{
	GENERATED_UCLASS_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetText", BlueprintSetter="SetText", meta = (MultiLine = "true"), Category="SimpleTextBox|Text")
	FText Text;

	/* 文本顏色 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextColor", BlueprintSetter="SetTextColor", Category="SimpleTextBox|Text")
	FSlateColor TextColor;

	/* 文本字体 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextFont", BlueprintSetter="SetTextFont", Category="SimpleTextBox|Text")
	FSlateFontInfo TextFont;

	/* 表示文本删除的样式 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextStrikeBrush", BlueprintSetter="SetTextStrikeBrush", Category="SimpleTextBox|Text")
	FSlateBrush TextStrikeBrush;

	/* 文本阴影的偏移 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextShadowOffset", BlueprintSetter="SetTextShadowOffset", Category="SimpleTextBox|Text")
	FVector2D TextShadowOffset;

	/* 文本阴影颜色 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextShadowColor", BlueprintSetter="SetTextShadowColor", Category="SimpleTextBox|Text")
	FLinearColor TextShadowColor;

	/* 高亮文本 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetHighlightText", BlueprintSetter="SetHighlightText", meta = (MultiLine = "true"), Category="SimpleTextBox|Text")
	FText HighlightText;

	/* 高亮文本块背景样式 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextHighlightShape", BlueprintSetter="SetTextHighlightShape", Category="SimpleTextBox|Text")
	FSlateBrush TextHighlightShape;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetAutoWrapText", BlueprintSetter="SetAutoWrapText", Category="SimpleTextBox|Text")
	bool AutoWrapText;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetWrapTextAt", BlueprintSetter="SetWrapTextAt", Category="SimpleTextBox|Text")
	float WrapTextAt;

	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetWrappingPolicy", BlueprintSetter="SetWrappingPolicy", Category="SimpleTextBox|Text")
	ETextWrappingPolicy WrappingPolicy;

	/* 文本的大小写 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTransformPolicy", BlueprintSetter="SetTransformPolicy", Category="SimpleTextBox|Text")
	ETextTransformPolicy TransformPolicy;

	/* 文本的对齐方式 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetJustification", BlueprintSetter="SetJustification", Category="SimpleTextBox|Text")
	TEnumAsByte<ETextJustify::Type> Justification;

	/* 限定最小宽度 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetMinDesiredWidth", BlueprintSetter="SetMinDesiredWidth", Category="SimpleTextBox|Text")
	float MinDesiredWidth;

	/* 行高 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetLineHeightPercentage", BlueprintSetter="SetLineHeightPercentage", Category="SimpleTextBox|Text")
	float LineHeightPercentage;

	/* 文本内边距 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextMargin", BlueprintSetter="SetTextMargin", Category="SimpleTextBox|Text")
	FMargin TextMargin;

	/* 文本溢出的表示 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetOverflowPolicy", BlueprintSetter="SetOverflowPolicy", Category="SimpleTextBox|Text")
	ETextOverflowPolicy OverflowPolicy;

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetSpace", BlueprintSetter="SetSpace", Category="SimpleTextBox|Space")
	float Space;

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetImage", BlueprintSetter="SetImage", Category="SimpleTextBox|Image")
	FSlateBrush Image;

	/* 图片颜色 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetImageColor", BlueprintSetter="SetImageColor", Category="SimpleTextBox|Image")
	FSlateColor ImageColor;

	/* 图片内边距 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetImageMargin", BlueprintSetter="SetImageMargin", Category="SimpleTextBox|Image")
	FMargin ImageMargin;

	/* 图片可视性 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetImageVisibility", BlueprintSetter="SetImageVisibility", Category="SimpleTextBox|Image")
	ESlateVisibility ImageVisibility;

public:
	/* 排列方式 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetSimpleTextBoxType", BlueprintSetter="SetSimpleTextBoxType", Category="SimpleTextBox|Layout")
	ESimpleTextBoxType SimpleTextBoxType;

	/* 整体的外边距 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetPadding", BlueprintSetter="SetPadding", Category="SimpleTextBox|Layout")
	FMargin Padding;

	/* 文本的水平对齐方式 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextHorizontalAlignment", BlueprintSetter="SetTextHorizontalAlignment", Category="SimpleTextBox|Layout")
	TEnumAsByte<EHorizontalAlignment> TextHorizontalAlignment;

	/* 文本的垂直对齐方式 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetTextVerticalAlignment", BlueprintSetter="SetTextVerticalAlignment", Category="SimpleTextBox|Layout")
	TEnumAsByte<EVerticalAlignment> TextVerticalAlignment;

	/* 图片的水平对齐方式 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetImageHorizontalAlignment", BlueprintSetter="SetImageHorizontalAlignment", Category="SimpleTextBox|Layout")
	TEnumAsByte<EHorizontalAlignment> ImageHorizontalAlignment;

	/* 图片的垂直对齐方式 */
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetImageVerticalAlignment", BlueprintSetter="SetImageVerticalAlignment", Category="SimpleTextBox|Layout")
	TEnumAsByte<EVerticalAlignment> ImageVerticalAlignment;

	/* Text */
public:
	UFUNCTION(BlueprintPure)
	FText GetText() const;

	UFUNCTION(BlueprintCallable)
	void SetText(FText InText);

	UFUNCTION(BlueprintPure)
	FSlateColor GetTextColor() const;

	UFUNCTION(BlueprintCallable)
	void SetTextColor(FSlateColor InTextColor);

	UFUNCTION(BlueprintPure)
	FSlateFontInfo GetTextFont() const;

	UFUNCTION(BlueprintCallable)
	void SetTextFont(FSlateFontInfo InTextFont);

	UFUNCTION(BlueprintPure)
	FSlateBrush GetTextStrikeBrush() const;

	UFUNCTION(BlueprintCallable)
	void SetTextStrikeBrush(const FSlateBrush& InTextStrikeBrush);

	UFUNCTION(BlueprintPure)
	FVector2D GetTextShadowOffset() const;

	UFUNCTION(BlueprintCallable)
	void SetTextShadowOffset(FVector2D InTextShadowOffset);

	UFUNCTION(BlueprintPure)
	FLinearColor GetTextShadowColor() const;

	UFUNCTION(BlueprintCallable)
	void SetTextShadowColor(FLinearColor InTextShadowColor);

	UFUNCTION(BlueprintPure)
	FText GetHighlightText() const;

	UFUNCTION(BlueprintCallable)
	void SetHighlightText(FText InHighlightText);

	UFUNCTION(BlueprintPure)
	FSlateBrush GetTextHighlightShape() const;

	UFUNCTION(BlueprintCallable)
	void SetTextHighlightShape(const FSlateBrush& InTextHighlightShape);

	UFUNCTION(BlueprintPure)
	bool GetAutoWrapText() const;

	UFUNCTION(BlueprintCallable)
	void SetAutoWrapText(bool InAutoWrapText);

	UFUNCTION(BlueprintPure)
	float GetWrapTextAt() const;

	UFUNCTION(BlueprintCallable)
	void SetWrapTextAt(float InWrapTextAt);

	UFUNCTION(BlueprintPure)
	ETextWrappingPolicy GetWrappingPolicy() const;

	UFUNCTION(BlueprintCallable)
	void SetWrappingPolicy(ETextWrappingPolicy InWrappingPolicy);

	UFUNCTION(BlueprintPure)
	ETextTransformPolicy GetTransformPolicy() const;

	UFUNCTION(BlueprintCallable)
	void SetTransformPolicy(ETextTransformPolicy InTransformPolicy);

	UFUNCTION(BlueprintPure)
	ETextJustify::Type GetJustification() const;

	UFUNCTION(BlueprintCallable)
	void SetJustification(ETextJustify::Type InJustification);

	UFUNCTION(BlueprintPure)
	float GetMinDesiredWidth() const;

	UFUNCTION(BlueprintCallable)
	void SetMinDesiredWidth(float InMinDesiredWidth);

	UFUNCTION(BlueprintPure)
	float GetLineHeightPercentage() const;

	UFUNCTION(BlueprintCallable)
	void SetLineHeightPercentage(float InLineHeightPercentage);

	UFUNCTION(BlueprintPure)
	FMargin GetTextMargin() const;

	UFUNCTION(BlueprintCallable)
	void SetTextMargin(const FMargin& InTextMargin);

	UFUNCTION(BlueprintPure)
	ETextOverflowPolicy GetOverflowPolicy() const;

	UFUNCTION(BlueprintCallable)
	void SetOverflowPolicy(ETextOverflowPolicy InOverflowPolicy);

	/* Spacer */
public:
	UFUNCTION(BlueprintPure)
	float GetSpace() const;

	UFUNCTION(BlueprintCallable)
	void SetSpace(float InSpace);
	
	/* Image */
public:
	UFUNCTION(BlueprintPure)
	FSlateBrush GetImage() const;

	UFUNCTION(BlueprintCallable)
	void SetImage(const FSlateBrush& InImage);

	UFUNCTION(BlueprintPure)
	FSlateColor GetImageColor() const;

	UFUNCTION(BlueprintCallable)
	void SetImageColor(const FSlateColor& InImageColor);

	UFUNCTION(BlueprintPure)
	FMargin GetImageMargin() const;

	UFUNCTION(BlueprintCallable)
	void SetImageMargin(const FMargin& InImageMargin);

	UFUNCTION(BlueprintPure)
	ESlateVisibility GetImageVisibility() const;

	UFUNCTION(BlueprintCallable)
	void SetImageVisibility(ESlateVisibility InImageVisibility);

	/* Layout */
	UFUNCTION(BlueprintPure)
	ESimpleTextBoxType GetSimpleTextBoxType() const;

	UFUNCTION(BlueprintCallable)
	void SetSimpleTextBoxType(ESimpleTextBoxType InSimpleTextBoxType);

	UFUNCTION(BlueprintPure)
	FMargin GetPadding() const;

	UFUNCTION(BlueprintCallable)
	void SetPadding(const FMargin& InPadding);

	UFUNCTION(BlueprintPure)
	EHorizontalAlignment GetTextHorizontalAlignment() const;

	UFUNCTION(BlueprintCallable)
	void SetTextHorizontalAlignment(EHorizontalAlignment InTextHorizontalAlignment);

	UFUNCTION(BlueprintPure)
	EVerticalAlignment GetTextVerticalAlignment() const;

	UFUNCTION(BlueprintCallable)
	void SetTextVerticalAlignment(EVerticalAlignment InTextVerticalAlignment);

	UFUNCTION(BlueprintPure)
	EHorizontalAlignment GetImageHorizontalAlignment() const;

	UFUNCTION(BlueprintCallable)
	void SetImageHorizontalAlignment(EHorizontalAlignment InImageHorizontalAlignment);

	UFUNCTION(BlueprintPure)
	EVerticalAlignment GetImageVerticalAlignment() const;

	UFUNCTION(BlueprintCallable)
	void SetImageVerticalAlignment(EVerticalAlignment InImageVerticalAlignment);

protected:
	TSharedPtr<SSimpleTextBox> MySimpleTextBox;
};
