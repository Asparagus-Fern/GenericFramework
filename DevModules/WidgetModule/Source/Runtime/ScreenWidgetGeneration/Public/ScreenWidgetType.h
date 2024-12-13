#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Components/Widget.h"
#include "ScreenWidgetType.generated.h"

class UScreenWidgetManager;
class UShortcutWidgetHandle;
class UInputAction;
class UInteractableUserWidgetBase;
class UUserWidgetBase;
class UCommonButtonEvent;
class UCommonButtonGroup;
class UMenuStyle;
class UMenuContainer;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Menu);

/**
 * todo:替换成模板类
 * 一个在类和实例间切换的Widget容器
 */
USTRUCT(BlueprintType)
struct SCREENWIDGETGENERATION_API FWidgetContainer
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bInstance = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "!bInstance"))
	TSubclassOf<UUserWidgetBase> WidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta=(EditConditionHides, EditCondition = "bInstance"))
	UUserWidgetBase* Widget = nullptr;

public:
	bool IsContainerValid() const;
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
	bool operator==(const FMenuInfo& InMenuInfo) const;
	bool operator==(const FGameplayTag InMenuTag) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Menu"))
	FGameplayTag MenuTag = FGameplayTag::EmptyTag;

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

	/* 隐藏，完全不可视 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHidden = false;

	/* 可视，但是否无效化，当为false时，所有的交互将无效化 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bHidden"))
	bool bIsEnable = true;

	/* 可视，是否可被选择，当为false时，OnSelected/OnDeselected不再有效 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bHidden && bIsEnable"))
	bool bSelectable = true;

	/* 是否在选中时再次点击取消选中 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bHidden && bIsEnable && bSelectable"))
	bool bToggleable = false;

	/* 是否默认选中 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bHidden && bIsEnable && bSelectable"))
	bool bIsSelected = false;

	UPROPERTY()
	bool bUseStyleClass = true;

	/* 菜单样式类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bUseStyleClass"))
	TSubclassOf<UMenuStyle> StyleClass = nullptr;

	/* 菜单样式 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta=(EditConditionHides, EditCondition = "!bUseStyleClass"))
	UMenuStyle* Style = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonEvent*> ActivedEvents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonEvent*> InactivedEvents;

	/* true则为激活，表示在该条件下激活按钮 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECommonButtonResponseEvent, bool> ResponseState;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMenuContainerInfo
{
	GENERATED_BODY()

public:
	FMenuContainerInfo();
	FMenuContainerInfo(FGameplayTag InOwnerTag);
	bool operator==(const FMenuContainerInfo& OtherContainerInfo) const;
	bool operator==(const FMenuInfo& OtherMenuInfo) const;
	bool operator==(FGameplayTag OtherMenuTag) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Menu"))
	FGameplayTag OwnerTag = FGameplayTag::EmptyTag;

	UPROPERTY()
	bool bUseContainerClass = true;

	/* 菜单容器类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bUseContainerClass"))
	TSubclassOf<UMenuContainer> ContainerClass = nullptr;

	/* 菜单容器 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta=(EditConditionHides, EditCondition = "!bUseContainerClass"))
	UMenuContainer* Container = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Menu"))
	TArray<FGameplayTag> MenuTags;
};

/**
 * 表示一个按钮的生成信息
 */
USTRUCT(BlueprintType)
struct FMenuGenerateInfo
{
	GENERATED_BODY()

	friend UScreenWidgetManager;

public:
	FMenuGenerateInfo();
	FMenuGenerateInfo(const FMenuContainerInfo& InMenuContainerInfo, UMenuContainer* InMenuContainer);

public:
	bool operator==(const FMenuGenerateInfo& OtherGenerateInfo) const;
	bool operator==(const FMenuContainerInfo& OtherMenuContainerInfo) const;

public:
	UPROPERTY(BlueprintReadOnly, Transient)
	FMenuContainerInfo MenuContainerInfo;

	UPROPERTY(BlueprintReadOnly, Transient)
	UMenuContainer* MenuContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<UMenuStyle*> MenuStyles;

public:
	bool GetIsValid() const;
	UMenuStyle* GetMenuStyle(FGameplayTag MenuTag);
	void MarkMenuStyleAsGarbage(UMenuStyle* InMenuStyle);
	void ClearupGarbageMenuStyle();

protected:
	UPROPERTY(Transient)
	UMenuStyle* ActivedMenuStyle = nullptr;

	UPROPERTY(Transient)
	TArray<UMenuStyle*> GarbageMenuStyles;
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
 * 
 */
USTRUCT(BlueprintType)
struct FShortcutWidgetTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FShortcutWidgetTableRow();

public:
	/* 对UMG的快捷键处理类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UShortcutWidgetHandle> ShortcutWidgetHandleClass;

	/* 绑定的玩家下标 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PlayerIndex;

	/* 绑定的UMG类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidgetBase> WidgetClass;

	/* 绑定的快捷键 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InputAction;
};
