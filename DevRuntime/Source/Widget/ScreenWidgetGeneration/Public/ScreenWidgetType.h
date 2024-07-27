#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Components/Widget.h"
#include "ScreenWidgetType.generated.h"

class UUserWidgetBase;
class UCommonButtonEvent;
class UCommonButtonGroup;
class UMenuStyle;
class UMenuContainer;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UMG);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_HUD);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Menu);

/**
 * 对特定的MenuTag进行特定的处理
 */
USTRUCT(BlueprintType)
struct FCommonButtonEventModify
{
	GENERATED_BODY()

public:
	/* 标签匹配是否使用Match */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bMatch = false;

	/* 需要修正的菜单标签 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Menu"))
	TArray<FGameplayTag> MenuTags;

	/* 修正处理 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonEvent*> ModifyEvent;

public:
	bool CanModify(bool bSelected);
};

/**
 * 表示一个按钮
 */
USTRUCT(BlueprintType)
struct FMenuInfo
{
	GENERATED_BODY()

public:
	FMenuInfo();
	FMenuInfo(FGameplayTag InMenuTag);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Menu"))
	FGameplayTag MenuTag;

	/* 主要名字 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuMainName;

	/* 次要名字 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuSubName;

	/* 提示 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuToolTip;

	/* 图标 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon = nullptr;

	/* 覆盖样式类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UMenuStyle* MenuStyleOverride = nullptr;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// bool bIsHidden = false;

	/* 按钮事件 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonEvent*> Events;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCommonButtonEventModify> ModifyPushEvents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCommonButtonEventModify> ModifyPopEvents;

public:
	bool operator==(const FMenuInfo InMenuInfo) const
	{
		return MenuTag == InMenuInfo.MenuTag;
	}

	bool operator==(const FGameplayTag InMenuTag) const
	{
		return MenuTag == InMenuTag;
	}
};

/**
 * 表示一个按钮组
 */
USTRUCT(BlueprintType)
struct FMenuContainerInfo
{
	GENERATED_BODY()

public:
	FMenuContainerInfo();
	FMenuContainerInfo(FGameplayTag InContainerTag);

public:
	/* Ex:如果有A.1和A.2，那么ContainerTag是A */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ContainerTag;

	/* 如果为true，表示这组按钮必须选中一个，将强制 bIsToggleable = false */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsSelectionRequired = false;

	/* 如果为true，表示这组按钮可以在选中时再次点击取消选中状态 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bIsSelectionRequired"))
	bool bIsToggleable = true;

	/* 当 bIsSelectionRequired = true 时，默认选中的Index */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bIsSelectionRequired"))
	int32 SelectionRequiredIndex = 0;

	/* 按钮的样式类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMenuStyle> MenuStyle = nullptr;

	/* 按钮的容器，覆盖MenuContainer的ConstructMenuStyle将按钮添加进控件 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UMenuContainer* MenuContainer = nullptr;

	/* 按钮信息 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "MenuTag"))
	TArray<FMenuInfo> MenuInfos;

public:
	bool operator==(const FGameplayTag InContainerTag) const
	{
		return ContainerTag == InContainerTag;
	}
};

/**
 * 表示一个按钮组的生成信息
 */
USTRUCT(BlueprintType)
struct FMenuGenerateInfo
{
	GENERATED_BODY()

public:
	FMenuGenerateInfo();
	FMenuGenerateInfo(UCommonButtonGroup* InCommonButtonGroup, const FMenuContainerInfo& InMenuContainerInfo);

public:
	bool operator==(FGameplayTag InContainerTag) const
	{
		return MenuContainerInfo.ContainerTag == InContainerTag;
	}

	bool operator==(const FMenuContainerInfo& InContainerInfo) const
	{
		return MenuContainerInfo.ContainerTag == InContainerInfo.ContainerTag;
	}

	bool operator==(const FMenuGenerateInfo InMenuGenerateInfo) const
	{
		return MenuContainerInfo.ContainerTag == InMenuGenerateInfo.MenuContainerInfo.ContainerTag;
	}

	bool HasMenuInfo(FGameplayTag InMenuTag);

	void SelectMenu(FGameplayTag InMenuTag);

	void DeselectMenu(FGameplayTag InMenuTag);

	UMenuStyle* GetMenuStyle(FGameplayTag InMenuTag);

public:
	UPROPERTY(BlueprintReadOnly)
	UCommonButtonGroup* CommonButtonGroup = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FMenuContainerInfo MenuContainerInfo;

	UPROPERTY(BlueprintReadOnly)
	TArray<UMenuStyle*> MenuStyles;

public:
};

/**
 * 
 */
struct SCREENWIDGETGENERATION_API FScreenWidgetDelegates
{
public:
	static FSimpleMulticastDelegate OnHUDCreated;

	static FSimpleMulticastDelegate OnMenuCleanup;
	static FSimpleMulticastDelegate OnMenuGenerated;

	DECLARE_MULTICAST_DELEGATE_OneParam(FUserWidgetDelegate, UUserWidgetBase*)
	static FUserWidgetDelegate OnWidgetOpen;
	static FUserWidgetDelegate OnWidgetClose;

	DECLARE_MULTICAST_DELEGATE_OneParam(FMenuDelegate, FMenuInfo)
	static FMenuDelegate OnMenuClicked;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FMenuSelectionDelegate, FMenuInfo, bool)
	static FMenuSelectionDelegate OnMenuSelectionChanged;

	DECLARE_MULTICAST_DELEGATE_OneParam(FWidgetAnimationDelegate, UWidget*)
	static FWidgetAnimationDelegate OnWidgetAnimationFinish;
};

/**
 * 表示按钮的激活条件
 */
UENUM(BlueprintType)
enum class ECommonButtonResponseEvent
{
	None,
	OnSelected,
	OnDeselected,
	OnClick,
	OnHovered,
	OnUnHovered,
	OnPressed,
	OnReleased
};
