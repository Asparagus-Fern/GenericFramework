// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "WidgetType.h"
#include "GenericWindowViewModel.generated.h"

class UGenericWindowStyle;

/**
 * 
 */
UCLASS()
class WINDOWGENERATION_API UGenericWindowViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	TSharedRef<SWindow> GetWindow();

public:
	/* Type of this window */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Basic")
	EWindowTypeBP WindowType = EWindowTypeBP::Normal;

	/* Style used to draw this window */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Basic")
	TSubclassOf<UGenericWindowStyle> WindowStyleClass = nullptr;

public:
	/* Should this window be focused immediately after it is shown? */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Focus")
	bool bFocusWhenFirstShown = true;

	/* When should this window be activated upon being shown? */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Focus")
	EWindowActivationPolicyBP ActivationPolicy = EWindowActivationPolicyBP::Always;

public:
	/* True if this should be a Modal window */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	bool IsModalWindow = false;

	/* True if this should be a 'pop-up' window */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	bool IsPopupWindow = false;

	/* True if this window should always be on top of all other windows */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	bool IsTopmostWindow = true;

	/* When true, the window can be dragged from anywhere */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	bool bDragAnywhere = false;

	/* If the initial ClientSize and ScreenPosition arguments should be automatically adjusted to account for DPI scale */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	bool bAdjustInitialSizeAndPositionForDPIScale = true;

	/* Use the default os look for the border of the window */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	bool bUseOSWindowBorder = false;

	/* If the window appears off screen or is too large to safely fit this flag will force realistic constraints on the window and bring it back into view*/
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	bool bSaneWindowPlacement = true;

	/* The padding around the edges of the window applied to it's content */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	FMargin LayoutBorder;

	/* The margin around the edges of the window that will be detected as places the user can grab to resize the window */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout")
	FMargin UserResizeBorder;

public:
	/* The windows auto-centering mode. If set to anything other than None, then the ScreenPosition value will be ignored*/
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout|Position")
	EAutoCenterBP AutoCenter = EAutoCenterBP::PreferredWorkArea;

	/* Screen-space position where the window should be initially located */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "AutoCenter == EAutoCenterBP::None"), Category="Layout|Position")
	FVector2D Position = FVector2D::ZeroVector;

public:
	/* The windows auto-centering mode. If set to anything other than None, then the ScreenPosition value will be ignored*/
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Layout|Size")
	ESizingRuleBP SizingRule = ESizingRuleBP::Autosized;

	/* How the window should be sized */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "SizingRule == ESizingRuleBP::UserSized"), Category="Layout|Size")
	FVector2D Size = FVector2D(512.f, 512.f);

	/* Is Clamp Min Width */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle), Category="Layout|Size")
	bool bClampMinWidth = false;

	/* The smallest width this window can be in Desktop Pixel Units */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bClampMinWidth"), Category="Layout|Size")
	float MinWidth = 0.f;

	/* Is Clamp Min Height */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle), Category="Layout|Size")
	bool bClampMinHeight = false;

	/* The smallest width this window can be in Desktop Pixel Units */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bClampMinHeight"), Category="Layout|Size")
	float MinHeight = 0.f;

	/* Is Clamp Min Width */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle), Category="Layout|Size")
	bool bClampMaxWidth = false;

	/* The smallest width this window can be in Desktop Pixel Units */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bClampMaxWidth"), Category="Layout|Size")
	float MaxWidth = 1920.f;

	/* Is Clamp Min Height */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle), Category="Layout|Size")
	bool bClampMaxHeight = false;

	/* The smallest width this window can be in Desktop Pixel Units */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bClampMaxHeight"), Category="Layout|Size")
	float MaxHeight = 1080.f;

public:
	/* Should this window support transparency */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="Opacity")
	EWindowTransparencyBP Transparency = EWindowTransparencyBP::None;

	/* The initial opacity of the window */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "Transparency != EWindowTransparencyBP::None"), Category="Opacity")
	float InitialOpacity = 1.f;

public:
	/*
	* True if we should initially create a traditional title bar area.
	* If false, the user must embed the title area content into the window manually, taking into account platform-specific considerations!
	* Has no effect for certain types of windows (popups, tool-tips, etc.)
	*/
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="TitleBar")
	bool bCreateTitleBar = true;

	/* Title of the window */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="TitleBar")
	FText WindowTitle = FText::FromString(TEXT("This Is a Title"));

public:
	/* Does this window have a close button? */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="TitleBar|Close")
	bool HasCloseButton = true;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "HasCloseButton"), Category="TitleBar|Close")
	FText CloseButtonToolTipText;

public:
	/* Can this window be minimized? */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="TitleBar|Minimize")
	bool bSupportsMinimize = true;

	/* Is the window initially minimized */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="TitleBar|Minimize")
	bool IsInitiallyMinimized = false;

	/* Can this window be maximized? */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="TitleBar|Maximize")
	bool bSupportsMaximize = true;

	/* Is the window initially maximized */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Category="TitleBar|Maximize")
	bool IsInitiallyMaximized = false;

private:
	UGenericWindowStyle* GetWindowStyleCDO() const;
	TSharedPtr<SWindow> WindowPtr = nullptr;
	FWindowStyle WindowStyle;
};
