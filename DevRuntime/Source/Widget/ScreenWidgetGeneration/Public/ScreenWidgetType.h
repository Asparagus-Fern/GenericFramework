#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "ScreenWidgetType.generated.h"

class UCommonButtonEvent;
class UCommonButtonGroup;
class UMenuStyle;
class UMenuContainer;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_HUD);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Menu);

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

	/* 按钮事件 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonEvent*> Events;

public:
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
	FMenuGenerateInfo(UCommonButtonGroup* InCommonButtonGroup, FMenuContainerInfo InMenuContainerInfo);

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

public:
	UPROPERTY(BlueprintReadOnly)
	UCommonButtonGroup* CommonButtonGroup = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FMenuContainerInfo MenuContainerInfo;
};

/**
 * 
 */
struct SCREENWIDGETGENERATION_API FScreenWidgetDelegates
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FMenuDelegate, FMenuInfo)
	static FMenuDelegate OnMenuClicked;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FMenuSelectionDelegate, FMenuInfo, bool)
	static FMenuSelectionDelegate OnMenuSelectionChanged;
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
