// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LoadingInterface.h"
#include "Base/GenericWidget.h"
#include "LoadingProgressBar.generated.h"

class USizeBox;
class UImage;
class USpinBox;
class UTextBlock;

/**
 * 
 */
UCLASS(MinimalAPI)
class ULoadingProgressBar : public UGenericWidget, public ILoadingInterface
{
	GENERATED_BODY()

public:
	WIDGETAPPLICATION_API virtual void NativePreConstruct() override;
	WIDGETAPPLICATION_API virtual void NativeConstruct() override;

	/* ILoadingInterface */
public:
	WIDGETAPPLICATION_API virtual void NativeOnLoadingBegin(int32 Num) override;
	WIDGETAPPLICATION_API virtual void NativeOnLoadingOnceFinish() override;
	WIDGETAPPLICATION_API virtual void NativeOnLoadingEnd() override;

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
	WIDGETAPPLICATION_API void Update(float InValue);

	/* 更新滑块位置 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	WIDGETAPPLICATION_API void UpdateThumbPosition(float InValue);

	/* 更新文本 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	WIDGETAPPLICATION_API void UpdateText(float InValue);

	/* 更新文本位置 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	WIDGETAPPLICATION_API void UpdateTextPosition(float InValue);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USpinBox> SpinBox_LoadingBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UImage> Image_LoadingThumb;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Loading;
};
