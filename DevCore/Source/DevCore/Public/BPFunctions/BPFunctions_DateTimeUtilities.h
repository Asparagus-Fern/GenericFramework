// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_DateTimeUtilities.generated.h"

UENUM(BlueprintType)
enum class EDayInWeek : uint8
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

static EDayOfWeek ConvToDayOfWeek(EDayInWeek DayInWeek)
{
	switch (DayInWeek)
	{
	case EDayInWeek::Monday:
		return EDayOfWeek::Monday;
	case EDayInWeek::Tuesday:
		return EDayOfWeek::Tuesday;
	case EDayInWeek::Wednesday:
		return EDayOfWeek::Wednesday;
	case EDayInWeek::Thursday:
		return EDayOfWeek::Thursday;
	case EDayInWeek::Friday:
		return EDayOfWeek::Friday;
	case EDayInWeek::Saturday:
		return EDayOfWeek::Saturday;
	case EDayInWeek::Sunday:
		return EDayOfWeek::Sunday;
	}

	return EDayOfWeek::Monday;
}

static EDayInWeek ConvToDayInWeek(EDayOfWeek DayOfWeek)
{
	switch (DayOfWeek)
	{
	case EDayOfWeek::Monday:
		return EDayInWeek::Monday;
	case EDayOfWeek::Tuesday:
		return EDayInWeek::Tuesday;
	case EDayOfWeek::Wednesday:
		return EDayInWeek::Wednesday;
	case EDayOfWeek::Thursday:
		return EDayInWeek::Thursday;
	case EDayOfWeek::Friday:
		return EDayInWeek::Friday;
	case EDayOfWeek::Saturday:
		return EDayInWeek::Saturday;
	case EDayOfWeek::Sunday:
		return EDayInWeek::Sunday;
	}

	return EDayInWeek::Monday;
}

UENUM(BlueprintType)
enum class EMonthInYear : uint8
{
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

static EMonthOfYear ConvToMonthOfYear(EMonthInYear MonthInYear)
{
	switch (MonthInYear)
	{
	case EMonthInYear::January:
		return EMonthOfYear::January;
	case EMonthInYear::February:
		return EMonthOfYear::February;
	case EMonthInYear::March:
		return EMonthOfYear::March;
	case EMonthInYear::April:
		return EMonthOfYear::April;
	case EMonthInYear::May:
		return EMonthOfYear::May;
	case EMonthInYear::June:
		return EMonthOfYear::June;
	case EMonthInYear::July:
		return EMonthOfYear::July;
	case EMonthInYear::August:
		return EMonthOfYear::August;
	case EMonthInYear::September:
		return EMonthOfYear::September;
	case EMonthInYear::October:
		return EMonthOfYear::October;
	case EMonthInYear::November:
		return EMonthOfYear::November;
	case EMonthInYear::December:
		return EMonthOfYear::December;
	}

	return EMonthOfYear::January;
}

static EMonthInYear ConvToMonthInYear(EMonthOfYear MonthOfYear)
{
	switch (MonthOfYear)
	{
	case EMonthOfYear::January:
		return EMonthInYear::January;
	case EMonthOfYear::February:
		return EMonthInYear::February;
	case EMonthOfYear::March:
		return EMonthInYear::March;
	case EMonthOfYear::April:
		return EMonthInYear::April;
	case EMonthOfYear::May:
		return EMonthInYear::May;
	case EMonthOfYear::June:
		return EMonthInYear::June;
	case EMonthOfYear::July:
		return EMonthInYear::July;
	case EMonthOfYear::August:
		return EMonthInYear::August;
	case EMonthOfYear::September:
		return EMonthInYear::September;
	case EMonthOfYear::October:
		return EMonthInYear::October;
	case EMonthOfYear::November:
		return EMonthInYear::November;
	case EMonthOfYear::December:
		return EMonthInYear::December;
	}

	return EMonthInYear::January;
}

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_DateTimeUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
};
