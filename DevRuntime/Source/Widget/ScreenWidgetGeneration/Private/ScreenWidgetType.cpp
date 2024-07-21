#include "ScreenWidgetType.h"

#include "ScreenWidgetManager.h"
#include "Group/CommonButtonGroup.h"
#include "Groups/CommonButtonGroupBase.h"
#include "Manager/ManagerGlobal.h"
#include "UserWidget/Menu/MenuStyle.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_UMG, "UMG");
UE_DEFINE_GAMEPLAY_TAG(TAG_HUD, "HUD");
UE_DEFINE_GAMEPLAY_TAG(TAG_Menu, "Menu");

FSimpleMulticastDelegate FScreenWidgetDelegates::OnHUDCreated;
FSimpleMulticastDelegate FScreenWidgetDelegates::OnMenuCleanup;
FSimpleMulticastDelegate FScreenWidgetDelegates::OnMenuGenerated;
FScreenWidgetDelegates::FUserWidgetDelegate FScreenWidgetDelegates::OnWidgetOpen;
FScreenWidgetDelegates::FUserWidgetDelegate FScreenWidgetDelegates::OnWidgetClose;
FScreenWidgetDelegates::FMenuDelegate FScreenWidgetDelegates::OnMenuClicked;
FScreenWidgetDelegates::FMenuSelectionDelegate FScreenWidgetDelegates::OnMenuSelectionChanged;
FScreenWidgetDelegates::FWidgetAnimationDelegate FScreenWidgetDelegates::OnWidgetAnimationFinish;

bool FCommonButtonEventModify::CanModify()
{
	if (bMatch)
	{
		for (auto& MenuTag : MenuTags)
		{
			if (GetManager<UScreenWidgetManager>()->GetLastActiveMenuTag().MatchesTag(MenuTag) || GetManager<UScreenWidgetManager>()->GetLastActiveMenuTag() == MenuTag)
			{
				return true;
			}
		}
	}
	else
	{
		if (MenuTags.Contains(GetManager<UScreenWidgetManager>()->GetLastActiveMenuTag()))
		{
			return true;
		}
	}

	return false;
}

FMenuInfo::FMenuInfo()
{
}

FMenuInfo::FMenuInfo(const FGameplayTag InMenuTag)
	: MenuTag(InMenuTag)
{
}

FMenuContainerInfo::FMenuContainerInfo()
{
}

FMenuContainerInfo::FMenuContainerInfo(const FGameplayTag InContainerTag)
	: ContainerTag(InContainerTag)
{
}

FMenuGenerateInfo::FMenuGenerateInfo()
{
}

FMenuGenerateInfo::FMenuGenerateInfo(UCommonButtonGroup* InCommonButtonGroup, const FMenuContainerInfo& InMenuContainerInfo)
	: CommonButtonGroup(InCommonButtonGroup),
	  MenuContainerInfo(InMenuContainerInfo)
{
}

bool FMenuGenerateInfo::HasMenuInfo(const FGameplayTag InMenuTag)
{
	for (const auto& MenuStyle : MenuStyles)
	{
		if (MenuStyle->GetMenuInfo() == InMenuTag)
		{
			return true;
		}
	}

	return false;
}

void FMenuGenerateInfo::SelectMenu(const FGameplayTag InMenuTag)
{
	if (IsValid(CommonButtonGroup) && HasMenuInfo(InMenuTag))
	{
		for (int32 Index = 0; Index != MenuStyles.Num(); ++Index)
		{
			if (MenuStyles[Index]->GetMenuInfo() == InMenuTag)
			{
				CommonButtonGroup->SelectButtonAtIndex(Index);
			}
		}
	}
}

void FMenuGenerateInfo::DeselectMenu(const FGameplayTag InMenuTag)
{
	if (IsValid(CommonButtonGroup) && HasMenuInfo(InMenuTag))
	{
		CommonButtonGroup->DeselectAll();
	}
}

UMenuStyle* FMenuGenerateInfo::GetMenuStyle(const FGameplayTag InMenuTag)
{
	if (HasMenuInfo(InMenuTag))
	{
		for (const auto& MenuStyle : MenuStyles)
		{
			if (MenuStyle->GetMenuInfo() == InMenuTag)
			{
				return MenuStyle;
			}
		}
	}

	return nullptr;
}
