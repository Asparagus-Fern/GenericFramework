// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "BPFunctions/BPFunctions_DateTimeUtilities.h"
#include "DateTimeWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UDateTimeWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateDateTimeNow();

	/* 获取格式化日期 */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FText GetFormatDate(int32 InYear, int32 InMouth, int32 InDay);

	/* 获取格式化时间 */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FText GetFormatTime(int32 InHour, int32 InMinute, int32 InSecond, int32 InMillisecond);

	/* 获取格式化星期 */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FText GetFormatDayOfWeek(EDayInWeek DayInWeek);

	/* 获取格式化月份 */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FText GetFormatMonthOfYear(EMonthInYear MonthInYear);

	UFUNCTION(BlueprintPure)
	bool GetIsMorning() const;

	UFUNCTION(BlueprintPure)
	bool GetIsAfternoon() const;

	UFUNCTION(BlueprintPure)
	bool GetIsLeapYear() const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUseHour12 = false;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Date;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Time;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_DayOfWeek;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_MonthOfYear;

protected:
	FDateTime DateTimeNow;
};
