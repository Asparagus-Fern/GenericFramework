// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Loading/LoadingProgressBar.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "ULoadingProgressBar"

void ULoadingProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (SpinBox_LoadingBar)
	{
		SpinBox_LoadingBar->SetMinValue(0);
		SpinBox_LoadingBar->SetMinSliderValue(0);
		SpinBox_LoadingBar->SetMaxValue(1);
		SpinBox_LoadingBar->SetMaxSliderValue(1);

		SpinBox_LoadingBar->SetEnableSlider(false);

		UpdateThumbPosition(SpinBox_LoadingBar->GetValue());
	}
}

void ULoadingProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULoadingProgressBar::NativeOnLoadingBegin(int32 Num)
{
	ILoadingInterface::NativeOnLoadingBegin(Num);
	LoadingNum = Num;
	ILoadingInterface::Execute_OnLoadingBegin(this);
}

void ULoadingProgressBar::NativeOnLoadingOnceFinish()
{
	ILoadingInterface::NativeOnLoadingOnceFinish();

	CurrentLoadingNum++;
	LoadingValue = (float)CurrentLoadingNum / (float)LoadingNum;
	LoadingPercentage = LoadingValue * 100;
	Update(LoadingValue);

	ILoadingInterface::Execute_OnLoadingOnceFinish(this);
}

void ULoadingProgressBar::NativeOnLoadingEnd()
{
	ILoadingInterface::NativeOnLoadingEnd();
	ILoadingInterface::Execute_OnLoadingOnceFinish(this);
}

void ULoadingProgressBar::Update(float InValue)
{
	if (SpinBox_LoadingBar)
	{
		SpinBox_LoadingBar->SetValue(InValue);
	}

	UpdateThumbPosition(InValue);
	UpdateText(InValue);
	UpdateTextPosition(InValue);
}

void ULoadingProgressBar::UpdateText_Implementation(float InValue)
{
	if (Text_Loading)
	{
		FNumberFormattingOptions NumberFormattingOptions;
		NumberFormattingOptions.MaximumFractionalDigits = 2;

		FFormatNamedArguments FormatArgs;
		FormatArgs.Add(TEXT("Percentage"), FText::AsNumber(LoadingPercentage, &NumberFormattingOptions));

		Text_Loading->SetText(FText::Format(LOCTEXT("LoadingTextFormat", "{Percentage}%"), FormatArgs));
	}
}

void ULoadingProgressBar::UpdateThumbPosition_Implementation(float InValue)
{
	if (!SpinBox_LoadingBar || !Image_LoadingThumb)
	{
		return;
	}

	const FVector2D LoadingSize = SpinBox_LoadingBar->GetCachedGeometry().GetLocalSize();
	const FVector2D LoadingThumbSize = Image_LoadingThumb->GetCachedGeometry().GetLocalSize();

	const float BarValueXPosition = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 1.f), FVector2D(0.f, LoadingSize.X), InValue);

	Image_LoadingThumb->SetRenderTranslation(FVector2D(BarValueXPosition - LoadingThumbSize.X / 2, 0.f));
}

void ULoadingProgressBar::UpdateTextPosition_Implementation(float InValue)
{
	if (!SpinBox_LoadingBar || !Text_Loading)
	{
		return;
	}

	const FVector2D LoadingSize = SpinBox_LoadingBar->GetCachedGeometry().GetLocalSize();
	const FVector2D LoadingTextSize = Text_Loading->GetCachedGeometry().GetLocalSize();

	const float BarValueXPosition = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 1.f), FVector2D(0.f, LoadingSize.X), InValue);

	Text_Loading->SetRenderTranslation(FVector2D(BarValueXPosition - LoadingTextSize.X / 2, 0.f));
}

#undef LOCTEXT_NAMESPACE
