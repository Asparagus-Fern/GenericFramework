// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "Style/GenericTextBlockStyle.h"

void UGenericTextBlockStyle::GetTextBlockStyle(FTextBlockStyle& OutTextBlockStyle) const
{
	OutTextBlockStyle
		.SetFont(Font)
		.SetColorAndOpacity(ColorAndOpacity)
		.SetShadowOffset(ShadowOffset)
		.SetShadowColorAndOpacity(ShadowColorAndOpacity)
		.SetSelectedBackgroundColor(SelectedBackgroundColor)
		.SetHighlightColor(HighlightColor)
		.SetHighlightShape(HighlightShape)
		.SetStrikeBrush(StrikeBrush)
		.SetUnderlineBrush(UnderlineBrush)
		.SetTransformPolicy(TransformPolicy)
		.SetOverflowPolicy(OverflowPolicy);
}
