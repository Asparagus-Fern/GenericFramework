// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Common/DateTimeWidget.h"

#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "FWidgetApplicationModule"

void UDateTimeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateDateTimeNow();
}

void UDateTimeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateDateTimeNow();
}

void UDateTimeWidget::UpdateDateTimeNow()
{
	DateTimeNow = FDateTime::Now();

	if (Text_Date)
	{
		Text_Date.Get()->SetText(GetFormatDate(DateTimeNow.GetYear(), DateTimeNow.GetMonth(), DateTimeNow.GetDay()));
	}

	if (Text_Time)
	{
		Text_Time.Get()->SetText(GetFormatTime(bUseHour12 ? DateTimeNow.GetHour12() : DateTimeNow.GetHour(), DateTimeNow.GetMinute(), DateTimeNow.GetSecond(), DateTimeNow.GetMillisecond()));
	}


	if (Text_DayOfWeek)
	{
		Text_DayOfWeek.Get()->SetText(GetFormatDayOfWeek(ConvToDayInWeek(DateTimeNow.GetDayOfWeek())));
	}

	if (Text_MonthOfYear)
	{
		Text_MonthOfYear.Get()->SetText(GetFormatMonthOfYear(ConvToMonthInYear(DateTimeNow.GetMonthOfYear())));
	}
}

FText UDateTimeWidget::GetFormatDate_Implementation(int32 InYear, int32 InMouth, int32 InDay)
{
	FNumberFormattingOptions NumberFormattingOptions;
	NumberFormattingOptions.SetUseGrouping(false);
	NumberFormattingOptions.SetMinimumIntegralDigits(2);

	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("Year"), FText::AsNumber(InYear, &NumberFormattingOptions));
	Arguments.Add(TEXT("Mouth"), FText::AsNumber(InMouth, &NumberFormattingOptions));
	Arguments.Add(TEXT("Day"), FText::AsNumber(InDay, &NumberFormattingOptions));

	return FText::Format(LOCTEXT("DateNow", "{Year}.{Mouth}.{Day}"), Arguments);
}

FText UDateTimeWidget::GetFormatTime_Implementation(int32 InHour, int32 InMinute, int32 InSecond, int32 InMillisecond)
{
	FNumberFormattingOptions NumberFormattingOptions;
	NumberFormattingOptions.SetUseGrouping(false);
	NumberFormattingOptions.SetMinimumIntegralDigits(2);

	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("Hour"), FText::AsNumber(InHour, &NumberFormattingOptions));
	Arguments.Add(TEXT("Minute"), FText::AsNumber(InMinute, &NumberFormattingOptions));
	Arguments.Add(TEXT("Second"), FText::AsNumber(InSecond, &NumberFormattingOptions));

	return FText::Format(LOCTEXT("TimeNow", "{Hour}:{Minute}:{Second}"), Arguments);
}

FText UDateTimeWidget::GetFormatDayOfWeek_Implementation(EDayInWeek DayInWeek)
{
	return UEnum::GetDisplayValueAsText(DayInWeek);
}

FText UDateTimeWidget::GetFormatMonthOfYear_Implementation(EMonthInYear MonthInYear)
{
	return UEnum::GetDisplayValueAsText(MonthInYear);
}

bool UDateTimeWidget::GetIsMorning() const
{
	return DateTimeNow.IsMorning();
}

bool UDateTimeWidget::GetIsAfternoon() const
{
	return DateTimeNow.IsAfternoon();
}

bool UDateTimeWidget::GetIsLeapYear() const
{
	return DateTimeNow.IsLeapYear(DateTimeNow.GetYear());
}

#undef LOCTEXT_NAMESPACE
