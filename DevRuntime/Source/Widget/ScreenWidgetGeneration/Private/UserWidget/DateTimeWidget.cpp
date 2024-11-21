// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/DateTimeWidget.h"

#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "DateTimeWidget"

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

	return FText::Format(LOCTEXT("DateNow", "{Year}.{Mouth}.{Day}"), FText::AsNumber(InYear, &NumberFormattingOptions), FText::AsNumber(InMouth, &NumberFormattingOptions), FText::AsNumber(InDay, &NumberFormattingOptions));
}

FText UDateTimeWidget::GetFormatTime_Implementation(int32 InHour, int32 InMinute, int32 InSecond, int32 InMillisecond)
{
	FNumberFormattingOptions NumberFormattingOptions;
	NumberFormattingOptions.SetUseGrouping(false);
	NumberFormattingOptions.SetMinimumIntegralDigits(2);

	return FText::Format(LOCTEXT("TimeNow", "{Hour}:{Minute}:{Second}"), FText::AsNumber(InHour, &NumberFormattingOptions), FText::AsNumber(InMinute, &NumberFormattingOptions), FText::AsNumber(InSecond, &NumberFormattingOptions));
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
