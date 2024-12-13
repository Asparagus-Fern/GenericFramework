#include "ScreenWidgetType.h"

#include "ScreenWidgetManager.h"
#include "Shortcut/SWH_ToggleOpenWidget.h"
#include "UserWidget/Menu/MenuContainer.h"
#include "UserWidget/Menu/MenuStyle.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Menu, "UI.Menu");

FSimpleMulticastDelegate FScreenWidgetDelegates::OnHUDCreated;
FSimpleMulticastDelegate FScreenWidgetDelegates::OnMenuCleanup;
FSimpleMulticastDelegate FScreenWidgetDelegates::OnMenuGenerated;
FScreenWidgetDelegates::FUserWidgetDelegate FScreenWidgetDelegates::OnWidgetOpen;
FScreenWidgetDelegates::FUserWidgetDelegate FScreenWidgetDelegates::OnWidgetClose;
FScreenWidgetDelegates::FMenuDelegate FScreenWidgetDelegates::OnMenuClicked;
FScreenWidgetDelegates::FMenuSelectionDelegate FScreenWidgetDelegates::OnMenuSelectionChanged;
FScreenWidgetDelegates::FWidgetAnimationDelegate FScreenWidgetDelegates::OnWidgetAnimationFinish;

/* ==================== FWidgetContainer ==================== */

bool FWidgetContainer::IsContainerValid() const
{
	return bInstance ? IsValid(Widget) : IsValid(WidgetClass);
}

/* ==================== FMenuInfo ==================== */

FMenuInfo::FMenuInfo()
	: StyleClass(UMenuStyle::StaticClass())
{
	ResponseState.Add(ECommonButtonResponseEvent::OnSelected, true);
	ResponseState.Add(ECommonButtonResponseEvent::OnDeselected, false);
}

FMenuInfo::FMenuInfo(const FGameplayTag InMenuTag)
	: MenuTag(InMenuTag),
	  StyleClass(UMenuStyle::StaticClass())
{
	ResponseState.Add(ECommonButtonResponseEvent::OnSelected, true);
	ResponseState.Add(ECommonButtonResponseEvent::OnDeselected, false);
}

bool FMenuInfo::operator==(const FMenuInfo& InMenuInfo) const
{
	return MenuTag == InMenuInfo.MenuTag;
}

bool FMenuInfo::operator==(const FGameplayTag InMenuTag) const
{
	return MenuTag == InMenuTag;
}

/* ==================== FMenuContainerInfo ==================== */

FMenuContainerInfo::FMenuContainerInfo()
	: ContainerClass(UMenuContainer::StaticClass())
{
}

FMenuContainerInfo::FMenuContainerInfo(const FGameplayTag InOwnerTag)
	: OwnerTag(InOwnerTag),
	  ContainerClass(UMenuContainer::StaticClass())
{
}

bool FMenuContainerInfo::operator==(const FMenuContainerInfo& OtherContainerInfo) const
{
	const TSet<FGameplayTag> A(MenuTags);
	const TSet<FGameplayTag> B(OtherContainerInfo.MenuTags);
	const bool IsMenuTagsEqual = A.Union(B).Array().Num() == MenuTags.Num() && A.Intersect(B).Array().Num() == MenuTags.Num();

	return OwnerTag == OtherContainerInfo.OwnerTag && IsMenuTagsEqual;
}

bool FMenuContainerInfo::operator==(const FMenuInfo& OtherMenuInfo) const
{
	return OwnerTag == OtherMenuInfo.MenuTag.RequestDirectParent() && MenuTags.Contains(OtherMenuInfo.MenuTag);
}

bool FMenuContainerInfo::operator==(const FGameplayTag OtherMenuTag) const
{
	return OwnerTag == OtherMenuTag.RequestDirectParent() && MenuTags.Contains(OtherMenuTag);
}

/* ==================== FMenuGenerateInfo ==================== */

FMenuGenerateInfo::FMenuGenerateInfo()
{
}

FMenuGenerateInfo::FMenuGenerateInfo(const FMenuContainerInfo& InMenuContainerInfo, UMenuContainer* InMenuContainer)
	: MenuContainerInfo(InMenuContainerInfo),
	  MenuContainer(InMenuContainer)
{
}

bool FMenuGenerateInfo::operator==(const FMenuGenerateInfo& OtherGenerateInfo) const
{
	return MenuContainerInfo == OtherGenerateInfo.MenuContainerInfo;
}

bool FMenuGenerateInfo::operator==(const FMenuContainerInfo& OtherMenuContainerInfo) const
{
	return MenuContainerInfo == OtherMenuContainerInfo;
}

bool FMenuGenerateInfo::GetIsValid() const
{
	return IsValid(MenuContainer) && !MenuStyles.IsEmpty();
}

UMenuStyle* FMenuGenerateInfo::GetMenuStyle(const FGameplayTag MenuTag)
{
	for (const auto& MenuStyle : MenuStyles)
	{
		if (MenuStyle->GetMenuTag() == MenuTag)
		{
			return MenuStyle;
		}
	}
	return nullptr;
}

void FMenuGenerateInfo::MarkMenuStyleAsGarbage(UMenuStyle* InMenuStyle)
{
	if (MenuStyles.Contains(InMenuStyle))
	{
		GarbageMenuStyles.Add(InMenuStyle);
	}
}

void FMenuGenerateInfo::ClearupGarbageMenuStyle()
{
	TArray<UMenuStyle*> TempGarbageMenuStyles = GarbageMenuStyles;
	for (auto& GarbageMenuStyle : TempGarbageMenuStyles)
	{
		MenuContainer->NativeDestructMenuContainer(GarbageMenuStyle);

		MenuStyles.Remove(GarbageMenuStyle);
		GarbageMenuStyles.Remove(GarbageMenuStyle);
		GarbageMenuStyle->MarkAsGarbage();
	}
}

/* ==================== FShortcutWidgetTableRow ==================== */

FShortcutWidgetTableRow::FShortcutWidgetTableRow()
	: ShortcutWidgetHandleClass(USWH_ToggleOpenWidget::StaticClass()),
	  PlayerIndex(0),
	  WidgetClass(nullptr),
	  InputAction(nullptr)
{
}
