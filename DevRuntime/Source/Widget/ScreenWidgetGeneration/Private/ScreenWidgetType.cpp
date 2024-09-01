#include "ScreenWidgetType.h"

#include "ScreenWidgetManager.h"
#include "Group/CommonButtonGroup.h"
#include "Groups/CommonButtonGroupBase.h"
#include "Manager/ManagerGlobal.h"
#include "UserWidget/Base/UserWidgetBase.h"
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

FMenuInfo::FMenuInfo()
{
	ResponseState.Add(ECommonButtonResponseEvent::OnSelected, true);
	ResponseState.Add(ECommonButtonResponseEvent::OnDeselected, false);
}

FMenuInfo::FMenuInfo(const FGameplayTag InMenuTag)
	: MenuTag(InMenuTag)
{
	ResponseState.Add(ECommonButtonResponseEvent::OnSelected, true);
	ResponseState.Add(ECommonButtonResponseEvent::OnDeselected, false);
}

FMenuGenerateInfo::FMenuGenerateInfo()
{
}

FMenuGenerateInfo::FMenuGenerateInfo(UMenuContainer* InMenuContainer)
	: MenuContainer(InMenuContainer)
{
}

bool FMenuGenerateInfo::operator==(const FMenuGenerateInfo& OtherGenerateInfo) const
{
	return MenuContainer == OtherGenerateInfo.MenuContainer;
}

bool FMenuGenerateInfo::operator==(const TSubclassOf<UMenuContainer> OtherMenuContainerClass) const
{
	return MenuContainer->GetClass() == OtherMenuContainerClass;
}

bool FMenuGenerateInfo::operator==(UMenuStyle* MenuStyle) const
{
	return MenuStyles.Contains(MenuStyle);
}

bool FMenuGenerateInfo::operator==(const FMenuInfo& MenuInfo) const
{
	for (auto& MenuStyle : MenuStyles)
	{
		if (MenuStyle->GetMenuInfo() == MenuInfo)
		{
			return true;
		}
	}
	return false;
}

bool FMenuGenerateInfo::operator==(const FGameplayTag MenuTag) const
{
	for (auto& MenuStyle : MenuStyles)
	{
		if (MenuStyle->GetMenuTag() == MenuTag)
		{
			return true;
		}
	}
	return false;
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
