// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadingInterface.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "LoadingProgressBar.generated.h"

class USizeBox;
class UImage;
class USpinBox;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API ULoadingProgressBar : public UUserWidgetBase, public ILoadingInterface
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	/* ILoadingInterface */
public:
	virtual void NativeOnLoadingBegin(int32 Num) override;
	virtual void NativeOnLoadingOnceFinish() override;
	virtual void NativeOnLoadingEnd() override;

protected:
	/* 当前以加载个数 */
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentLoadingNum = 0;

	/* 需加载总数 */
	UPROPERTY(BlueprintReadOnly)
	int32 LoadingNum = 0;

	/* 加载进度 0 ~ 1 */
	UPROPERTY(BlueprintReadOnly)
	float LoadingValue = 0.f;

	/* 加载进度百分比 0 ~ 100 */
	UPROPERTY(BlueprintReadOnly)
	float LoadingPercentage = 0.f;

public:
	UFUNCTION(BlueprintCallable)
	void Update(float InValue);

	/* 更新滑块位置 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateThumbPosition(float InValue);

	/* 更新文本 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateText(float InValue);

	/* 更新文本位置 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateTextPosition(float InValue);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USpinBox> SpinBox_LoadingBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UImage> Image_LoadingThumb;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Loading;
};
