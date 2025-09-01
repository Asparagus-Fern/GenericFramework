#pragma once

#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

UNREALMISC_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogDefault, Log, All);

extern UNREALMISC_API FColor DErrorColor;
extern UNREALMISC_API FColor DWarningColor;
extern UNREALMISC_API FColor DMessageColor;
extern UNREALMISC_API float DPrintDuration;
extern UNREALMISC_API float DNotifyFadeInDuration;
extern UNREALMISC_API float DNotifyFadeOutDuration;
extern UNREALMISC_API float DNotifyDuration;

#define GenericLOG(CategoryName, Verbosity, Format, ...) \
UE_LOG(CategoryName, Type::Verbosity, TEXT("[Line:%d %s] %s"), __LINE__, ANSI_TO_TCHAR(__FUNCTION__), *FString::Printf(Format, ##__VA_ARGS__))

#define GenericPRINT(Verbosity, Format, ...) \
if(IsValid(GEngine)){ \
	if (::ELogVerbosity::Verbosity == ::ELogVerbosity::Error) \
		GEngine->AddOnScreenDebugMessage(-1, DPrintDuration, DErrorColor, FString::Printf(Format, ##__VA_ARGS__)); \
	else if (::ELogVerbosity::Verbosity == ::ELogVerbosity::Warning) \
		GEngine->AddOnScreenDebugMessage(-1, DPrintDuration, DWarningColor, FString::Printf(Format, ##__VA_ARGS__)); \
	else \
		GEngine->AddOnScreenDebugMessage(-1, DPrintDuration, DMessageColor, FString::Printf(Format, ##__VA_ARGS__)); \
}

#define GenericNOTIFY(Format, ...) \
{ \
	FNotificationInfo NotificationInfo(FText::FromString(FString::Printf(TEXT("%s"),ANSI_TO_TCHAR(__FUNCTION__)))); \
	NotificationInfo.SubText = FText::FromString(FString::Printf(Format, ##__VA_ARGS__)); \
	NotificationInfo.FadeInDuration = DNotifyFadeInDuration; \
	NotificationInfo.FadeOutDuration = DNotifyFadeOutDuration; \
	NotificationInfo.ExpireDuration = DNotifyDuration; \
	FSlateNotificationManager::Get().AddNotification(NotificationInfo); \
}

#define GenericEnsureLOG(CategoryName, InExpression, ...) \
if (!ensure(InExpression)){ \
GenericLOG(CategoryName, Warning, TEXT("Expression : (%s) Result Is Fail"), #InExpression, ##__VA_ARGS__) \
return; \
}

#define GenericEnsureAlwaysLOG(CategoryName, InExpression, ...) \
if (!ensureAlways(InExpression)){ \
GenericLOG(CategoryName, Warning, TEXT("Expression : (%s) Result Is Fail, %s"), ##InExpression, ##__VA_ARGS__) \
return; \
}

/* FNotificationInfo :

	//如果设置，则使用此小部件覆盖通知的整个内容
	TSharedPtr＜INotificationWidget＞ContentWidget;

	//此通知中显示的文本。适用于短通知和标题
	TAttribute＜FText＞Text;

	//此通知中显示的可选子文本。子文本比默认文本字段小，更适合长描述
	TAttribute＜FText＞SubText;

	//通知按钮的设置信息
	TArray<FNotificationButtonInfo> ButtonDetails;

	//要显示在文本旁边的图标图像
	const FSlateBrush* Image;

	//此元素的淡入持续时间
	float FadeInDuration;
	
	//此元素的淡出持续时间
	float FadeOutDuration;
	
	//此元素淡出前的持续时间
	float ExpireDuration;
	
	//控制是否添加动画滑动
	bool bUseThrobber;
	
	//控制是否显示成功和失败图标
	bool bUseSuccessFailIcons;
	
	//如果为true，则将使用更大的粗体显示消息
	bool bUseLargeFont;
	
	//设置此选项时，强制框的宽度，用于在文本更改时停止调整大小
	FOptionalSize WidthOverride;
	
	//如果为true，则通知将在过期持续时间后自动超时。
	bool bFireAndForget;
	
	//设置后，将在通知上显示一个复选框；获取当前复选框状态的句柄
	TAttribute<ECheckBoxState> CheckBoxState;
	
	//设置后，将在通知上显示一个复选框；设置新复选框状态的句柄
	FOnCheckStateChanged CheckBoxStateChanged;
	
	//为复选框消息显示的文本
	TAttribute<FText> CheckBoxText;
	
	//设置后，将在通知的右侧显示为超链接
	FSimpleDelegate Hyperlink;
	
	//要为超链接消息显示的文本
	TAttribute<FText> HyperlinkText;
	
	//放置通知的特定窗口。如果为空，将使用应用程序的根窗口
	TSharedPtr<SWindow> ForWindow;
	
	//如果我们应该在通知转换且性能不佳时限制编辑器，以确保用户可以看到动画，则为True
	bool bAllowThrottleWhenFrameRateIsLow;
*/
