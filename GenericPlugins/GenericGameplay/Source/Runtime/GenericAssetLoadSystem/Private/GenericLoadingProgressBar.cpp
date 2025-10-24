// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericLoadingProgressBar.h"

#include "GenericLoadingViewModel.h"
#include "LoadingType.h"
#include "WidgetType.h"
#include "Components/SpinBox.h"
#include "Components/TextBlock.h"
#include "Type/DebugType.h"

#define LOCTEXT_NAMESPACE "FGenericAssetLoadSystem"

void UGenericLoadingProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (SpinBox_Loading)
	{
		SpinBox_Loading->SetMinValue(0.f);
		SpinBox_Loading->SetMaxValue(1.f);
		SpinBox_Loading->SetMinSliderValue(0.f);
		SpinBox_Loading->SetMaxSliderValue(1.f);

		if (Text_Loading)
		{
			FText LoadingText;
			GetLoadingText(SpinBox_Loading->GetValue(), LoadingText);
			Text_Loading->SetText(LoadingText);
		}
	}
}

void UGenericLoadingProgressBar::UpdatePerformance()
{
	if (!LoadingViewModel)
	{
		GenericLOG(GenericLogLoadGame, Error, TEXT("LoadingViewModel Is InValid"))
		return;
	}

	if (SpinBox_Loading)
	{
		SpinBox_Loading->SetValue(LoadingViewModel->GetLoadingValue());
	}

	if (Text_Loading)
	{
		FText LoadingText;
		GetLoadingText(LoadingViewModel->GetLoadingValue(), LoadingText);
		Text_Loading->SetText(LoadingText);
	}
}

UGenericLoadingViewModel* UGenericLoadingProgressBar::GetLoadingViewModel()
{
	return LoadingViewModel;
}

void UGenericLoadingProgressBar::SetLoadingViewModel(UGenericLoadingViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(LoadingViewModel);
	LoadingViewModel = InViewModel;

	if (LoadingViewModel)
	{
		REGISTER_MVVM_PROPERTY(LoadingViewModel, CurrentLoadingNum, OnCurrentLoadingNumChanged, true);
		REGISTER_MVVM_PROPERTY(LoadingViewModel, TotalLoadingNum, OnTotalLoadingNumChanged, true);
	}
}

void UGenericLoadingProgressBar::OnCurrentLoadingNumChanged_Implementation(int32 InCurrentLoadingNum)
{
	UpdatePerformance();
}

void UGenericLoadingProgressBar::OnTotalLoadingNumChanged_Implementation(int32 InCurrentLoadingNum)
{
	UpdatePerformance();
}

void UGenericLoadingProgressBar::GetLoadingText_Implementation(const float InValue, FText& Result)
{
	FNumberFormattingOptions NumberFormattingOptions;
	NumberFormattingOptions.MinimumFractionalDigits = 2;
	NumberFormattingOptions.MaximumFractionalDigits = 2;
	NumberFormattingOptions.UseGrouping = false;

	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("Percentage"), FText::AsNumber(InValue * 100, &NumberFormattingOptions));
	Result = FText::Format(LOCTEXT("LoadingText", "{Percentage}%"), Arguments);
}

#undef LOCTEXT_NAMESPACE
