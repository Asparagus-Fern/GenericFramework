// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/GenericDateTime.h"

#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "FWidgetApplicationModule"

void UGenericDateTime::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateDateTimeNow();
}

void UGenericDateTime::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer, FTimerDelegate::CreateUObject(this, &UGenericDateTime::UpdateDateTimeNow), UpdateDuration, true);
}

void UGenericDateTime::UpdateDateTimeNow()
{
	DateTimeNow = FDateTime::Now();

	if (Text_Date)
	{
		Text_Date->SetText(GetFormatDate(DateTimeNow.GetYear(), DateTimeNow.GetMonth(), DateTimeNow.GetDay()));
	}

	if (Text_Time)
	{
		Text_Time->SetText(GetFormatTime(bUseHour12 ? DateTimeNow.GetHour12() : DateTimeNow.GetHour(), DateTimeNow.GetMinute(), DateTimeNow.GetSecond(), DateTimeNow.GetMillisecond()));
	}

	if (Text_DayOfWeek)
	{
		Text_DayOfWeek->SetText(GetFormatDayOfWeek(ConvToDayInWeek(DateTimeNow.GetDayOfWeek())));
	}

	if (Text_MonthOfYear)
	{
		Text_MonthOfYear->SetText(GetFormatMonthOfYear(ConvToMonthInYear(DateTimeNow.GetMonthOfYear())));
	}
}

void UGenericDateTime::SetIsUseHour12(bool IsUseHour12)
{
	bUseHour12 = IsUseHour12;
	UpdateDateTimeNow();
}

void UGenericDateTime::SetUpdateDuration(float InUpdateDuration)
{
	UpdateTimer.Invalidate();
	UpdateDuration = InUpdateDuration;
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer, FTimerDelegate::CreateUObject(this, &UGenericDateTime::UpdateDateTimeNow), UpdateDuration, true);
}

FText UGenericDateTime::GetFormatDate_Implementation(int32 InYear, int32 InMouth, int32 InDay)
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

FText UGenericDateTime::GetFormatTime_Implementation(int32 InHour, int32 InMinute, int32 InSecond, int32 InMillisecond)
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

FText UGenericDateTime::GetFormatDayOfWeek_Implementation(EDayInWeek DayInWeek)
{
	return UEnum::GetDisplayValueAsText(DayInWeek);
}

FText UGenericDateTime::GetFormatMonthOfYear_Implementation(EMonthInYear MonthInYear)
{
	return UEnum::GetDisplayValueAsText(MonthInYear);
}

bool UGenericDateTime::GetIsMorning() const
{
	return DateTimeNow.IsMorning();
}

bool UGenericDateTime::GetIsAfternoon() const
{
	return DateTimeNow.IsAfternoon();
}

bool UGenericDateTime::GetIsLeapYear() const
{
	return DateTimeNow.IsLeapYear(DateTimeNow.GetYear());
}

#undef LOCTEXT_NAMESPACE
