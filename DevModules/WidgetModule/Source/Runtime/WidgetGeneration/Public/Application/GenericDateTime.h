// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "Type/DateTimeType.h"
#include "GenericDateTime.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericDateTime : public UGenericWidget
{
	GENERATED_BODY()

public:
	WIDGETGENERATION_API virtual void NativePreConstruct() override;
	WIDGETGENERATION_API virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API void UpdateDateTimeNow();

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API void SetIsUseHour12(bool IsUseHour12);

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API void SetUpdateDuration(float InUpdateDuration);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	WIDGETGENERATION_API FText GetFormatDate(int32 InYear, int32 InMouth, int32 InDay);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	WIDGETGENERATION_API FText GetFormatTime(int32 InHour, int32 InMinute, int32 InSecond, int32 InMillisecond);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	WIDGETGENERATION_API FText GetFormatDayOfWeek(EDayInWeek DayInWeek);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	WIDGETGENERATION_API FText GetFormatMonthOfYear(EMonthInYear MonthInYear);

	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API bool GetIsMorning() const;

	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API bool GetIsAfternoon() const;

	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API bool GetIsLeapYear() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUseHour12 = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float UpdateDuration = 0.1f;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Date;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Time;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_DayOfWeek;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_MonthOfYear;

	FTimerHandle UpdateTimer;
	FDateTime DateTimeNow;
};
